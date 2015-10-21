#include <thread>
#include <Utils/Stopwatch/Stopwatch.h>

IStopwatch::IStopwatch() {
}

std::chrono::duration<double> IStopwatch::getTimeElapsed() const {
    return timeElapsed;
}

double IStopwatch::getMeanTimePerIteration() const {
    return timeElapsed.count() / iterations;
}