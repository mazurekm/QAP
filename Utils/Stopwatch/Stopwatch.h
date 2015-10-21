#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <memory>
#include <Algorithms/Strategy/Strategy.h>

class IStopwatch {
protected:
    std::chrono::duration<double> timeElapsed;
    long iterations;
public:
    IStopwatch();
    virtual void measureExecutionTime(std::unique_ptr<IStrategy> const &, double) = 0;
    std::chrono::duration<double> getTimeElapsed() const;
    double getMeanTimePerIteration() const;
};

#endif