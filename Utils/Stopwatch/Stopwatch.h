#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <memory>
#include <Algorithms/Strategy/Strategy.h>

class IStopwatch {
protected:
    std::chrono::duration<double> timeElapsed;
    long iterations, stepSum, solutionsReviewedSum;
public:
    IStopwatch();
    virtual void measureExecutionTime(std::shared_ptr<IStrategy> const &, double) = 0;
    virtual void measureExecutionTime(std::shared_ptr<IStrategy> const &, long) = 0;
    std::chrono::duration<double> getTimeElapsed() const;
    double getMeanTimePerIteration() const;
};

#endif