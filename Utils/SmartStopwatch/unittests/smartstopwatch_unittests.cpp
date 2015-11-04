#define BOOST_TEST_MODULE Utils

#include <memory>
#include <unistd.h>
#include <boost/test/unit_test.hpp>
#include <Utils/SmartStopwatch/SmartStopwatch.h>
#include <Algorithms/Strategy/Strategy.h>

const double IterationTime = 0.15;

class MockStrategy : public IStrategy  {
public:
    MockStrategy(const Matrix & flow, const Matrix & distance) : IStrategy(flow, distance) {}
    void perform(); 
};

void MockStrategy::perform() {
    usleep(1000000 * IterationTime);
}

BOOST_AUTO_TEST_CASE(test_measure) {
    std::shared_ptr<IStrategy> mockStrategyPtr(new MockStrategy(Matrix(), Matrix())); 
    std::shared_ptr<IStopwatch> stopwatchPtr(new SmartStopwatch());
    double expectedTimeElapsed = ceil(10 * IterationTime);

    stopwatchPtr->measureExecutionTime(mockStrategyPtr, expectedTimeElapsed);

    BOOST_CHECK(stopwatchPtr->getTimeElapsed().count() >= expectedTimeElapsed);
    BOOST_CHECK_CLOSE(IterationTime, stopwatchPtr->getMeanTimePerIteration(), 1);
}

BOOST_AUTO_TEST_CASE(test_measure_iterations) {
    std::shared_ptr<IStrategy> mockStrategyPtr(new MockStrategy(Matrix(), Matrix())); 
    std::shared_ptr<IStopwatch> stopwatchPtr(new SmartStopwatch());
    long expectedIterations = 8;

    stopwatchPtr->measureExecutionTime(mockStrategyPtr, expectedIterations);

    BOOST_CHECK_CLOSE(expectedIterations * IterationTime, stopwatchPtr->getTimeElapsed().count(), 1);
}
