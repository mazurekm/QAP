#include <Utils/SmartStopwatch/SmartStopwatch.h>
#include <iostream>

using namespace std::chrono;

void SmartStopwatch::measureExecutionTime(std::shared_ptr<IStrategy> const & algPtr, double timeLimit) {
    iterations = 0;
    timeElapsedTotal = 0;
    timeElapsedSquareTotal = 0;
    do {
        measure(algPtr);       
    } while (timeElapsedTotal < timeLimit);
}

void SmartStopwatch::measureExecutionTime(std::shared_ptr<IStrategy> const & algPtr, long iterationLimit) {
    iterations = 0;
    timeElapsedTotal = 0;
    timeElapsedSquareTotal = 0;
    do {
        measure(algPtr); 
    } while (iterations < iterationLimit);
}

void SmartStopwatch::measure(std::shared_ptr<IStrategy> const & algPtr) {
    high_resolution_clock::time_point startTimePoint = high_resolution_clock::now();
    algPtr->perform();
    timeElapsedDuringPerform = high_resolution_clock::now() - startTimePoint; 
    timeElapsedTotal += timeElapsedDuringPerform.count();
    timeElapsedSquareTotal += timeElapsedDuringPerform.count() * timeElapsedDuringPerform.count();
    ++iterations;
}