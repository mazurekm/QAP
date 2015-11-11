#define BOOST_TEST_MODULE Utils

#include <memory>
#include <unistd.h>
#include <boost/test/unit_test.hpp>
#include <Utils/SmartStopwatch/SmartStopwatch.h>
#include <Algorithms/Strategy/Strategy.h>
#include <iostream>

using std::chrono::high_resolution_clock;

const double IterationTime = 0.15;

class MockStrategy : public IStrategy  {
    int periodNumber;
public:
    static int actionType;
    MockStrategy(const Matrix & flow, const Matrix & distance) : IStrategy(flow, distance), periodNumber(0) {}
    void perform(); 
};

int MockStrategy::actionType;

void MockStrategy::perform() {
    if (0 == actionType) {
        usleep(1000000 * IterationTime);
    }
    else if (1 == actionType) {
        usleep(100000 * periodNumber); 
        ++periodNumber;
    }
}

BOOST_AUTO_TEST_CASE(test_measure) {
    std::shared_ptr<IStrategy> mockStrategyPtr(new MockStrategy(Matrix(), Matrix())); 
    std::shared_ptr<IStopwatch> stopwatchPtr(new SmartStopwatch());
    double expectedTimeElapsed = ceil(10 * IterationTime);
    MockStrategy::actionType = 0;

    stopwatchPtr->measureExecutionTime(mockStrategyPtr, expectedTimeElapsed);

    auto timeStatsCalculator = stopwatchPtr->getTimeStatsCalculator();
    BOOST_CHECK_CLOSE(IterationTime, timeStatsCalculator.getMean(), 1);
    BOOST_CHECK(timeStatsCalculator.getStdDev() < 0.001);
}

BOOST_AUTO_TEST_CASE(test_measure_iterations) {
    std::shared_ptr<IStrategy> mockStrategyPtr(new MockStrategy(Matrix(), Matrix())); 
    std::shared_ptr<IStopwatch> stopwatchPtr(new SmartStopwatch());
    long expectedIterations = 8;
    MockStrategy::actionType = 0;

    high_resolution_clock::time_point startTimePoint = high_resolution_clock::now();
    stopwatchPtr->measureExecutionTime(mockStrategyPtr, expectedIterations);
    auto timeElapsed = high_resolution_clock::now() - startTimePoint; 

    BOOST_CHECK_CLOSE(expectedIterations * IterationTime, timeElapsed.count(), 1);
}

BOOST_AUTO_TEST_CASE(test_stddev) {
    std::shared_ptr<IStrategy> mockStrategyPtr(new MockStrategy(Matrix(), Matrix())); 
    std::shared_ptr<IStopwatch> stopwatchPtr(new SmartStopwatch());
    MockStrategy::actionType = 1;
    double timeLimit = 2.1; // 7 runs
    double expectedMean = 0.3;
    double expectedStdDev = (0 - expectedMean)*(0 - expectedMean) + (0.1 - expectedMean)*(0.1 - expectedMean) + (0.2 - expectedMean)*(0.2 - expectedMean);
    expectedStdDev += (0.3 - expectedMean)*(0.3 - expectedMean) + (0.4 - expectedMean)*(0.4 - expectedMean) + (0.5 - expectedMean)*(0.5 - expectedMean) + (0.6 - expectedMean)*(0.6 - expectedMean);
    expectedStdDev = std::sqrt(expectedStdDev / 7);

    stopwatchPtr->measureExecutionTime(mockStrategyPtr, timeLimit);
    auto timeStatsCalculator = stopwatchPtr->getTimeStatsCalculator();
    BOOST_CHECK_CLOSE(timeStatsCalculator.getStdDev(), expectedStdDev, 1);
}
