#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <Algorithms/Strategy/Strategy.h>

class IStopWatch {

public:
    std::chrono::duration<double> measureExecutionTime(IStrategy &);
};

#endif