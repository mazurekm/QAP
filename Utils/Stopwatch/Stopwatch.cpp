#include <Utils/Stopwatch/Stopwatch.h>
#include <cmath>

IStopwatch::IStopwatch() {
}

CStatisticsCalculator IStopwatch::getTimeStatsCalculator() const {
    return timeStatsCalculator;
}