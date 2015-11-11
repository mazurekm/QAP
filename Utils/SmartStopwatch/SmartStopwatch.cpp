#include <Utils/SmartStopwatch/SmartStopwatch.h>
#include <iostream>

using namespace std::chrono;

void SmartStopwatch::measureExecutionTime(std::shared_ptr<IStrategy> const & algPtr, double timeLimit) {
    timeStatsCalculator.reset();
    iterations = 0;
    do {
        measure(algPtr);
    } while (timeStatsCalculator.getQuantitySum() < timeLimit);
}

void SmartStopwatch::measureExecutionTime(std::shared_ptr<IStrategy> const & algPtr, long iterationLimit) {
    timeStatsCalculator.reset();
    iterations = 0;
    do {
        measure(algPtr); 
    } while (iterations < iterationLimit);
}

void SmartStopwatch::measure(std::shared_ptr<IStrategy> const & algPtr) {
    high_resolution_clock::time_point startTimePoint = high_resolution_clock::now();
    algPtr->perform();
    timeElapsedDuringPerform = high_resolution_clock::now() - startTimePoint; 
    timeStatsCalculator.update(timeElapsedDuringPerform.count());
    ++iterations;
}