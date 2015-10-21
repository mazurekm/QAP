#ifndef SMARTSTOPWATCH_H
#define SMARTSTOPWATCH_H

#include <Utils/Stopwatch/Stopwatch.h>

class SmartStopwatch : public IStopwatch {
public:
    void measureExecutionTime(std::unique_ptr<IStrategy> const &, double);
};

#endif