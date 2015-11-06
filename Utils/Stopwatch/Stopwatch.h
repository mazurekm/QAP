#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <memory>
#include <Algorithms/Strategy/Strategy.h>

class IStopwatch {
protected:
    std::chrono::duration<double> timeElapsedDuringPerform;
    double timeElapsedTotal, timeElapsedSquareTotal;
    long iterations, stepSum, solutionsReviewedSum;
public:
    IStopwatch();
    virtual void measureExecutionTime(std::shared_ptr<IStrategy> const &, double) = 0;
    virtual void measureExecutionTime(std::shared_ptr<IStrategy> const &, long) = 0;
    double getTimeElapsedTotal() const;
    double getMeanTimePerIteration() const;
    double getMeanTimeStdDev() const;
protected:
    virtual void measure(std::shared_ptr<IStrategy> const &) = 0;
};

#endif