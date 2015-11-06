#include <Utils/Stopwatch/Stopwatch.h>
#include <cmath>

IStopwatch::IStopwatch() {
}

double IStopwatch::getTimeElapsedTotal() const {
    return timeElapsedTotal;
}

double IStopwatch::getMeanTimePerIteration() const {
    return timeElapsedTotal / iterations;
}

double IStopwatch::getMeanTimeStdDev() const {
    double mean = getMeanTimePerIteration();
    return std::sqrt(timeElapsedSquareTotal/iterations - mean*mean);
}