#include <Utils/SmartStopwatch/SmartStopwatch.h>
#include <iostream>

using namespace std::chrono;

void SmartStopwatch::measureExecutionTime(std::unique_ptr<IStrategy> const & algPtr, double timeLimit) {
    iterations = 0;
    const high_resolution_clock::time_point startTimePoint = high_resolution_clock::now();
    do {
       algPtr->perform();
       timeElapsed = high_resolution_clock::now() - startTimePoint; 
       ++iterations;
    } while (timeElapsed.count() < timeLimit);
}

void SmartStopwatch::measureExecutionTime(std::unique_ptr<IStrategy> const & algPtr, long iterationLimit) {
    iterations = 0;
    const high_resolution_clock::time_point startTimePoint = high_resolution_clock::now();
    do {
       algPtr->perform();
       timeElapsed = high_resolution_clock::now() - startTimePoint; 
       ++iterations;
    } while (iterations < iterationLimit);
}