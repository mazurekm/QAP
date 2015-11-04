#ifndef SMARTSTOPWATCH_H
#define SMARTSTOPWATCH_H

#include <Utils/Stopwatch/Stopwatch.h>

class SmartStopwatch : public IStopwatch {
    void prepareForMeasure();
public:
    void measureExecutionTime(std::unique_ptr<IStrategy> const &, double);
    void measureExecutionTime(std::unique_ptr<IStrategy> const &, long);
};

#endif