#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <memory>
#include <Algorithms/Strategy/Strategy.h>
#include <Utils/StatisticsCalculator/StatisticsCalculator.h>

class IStopwatch {
protected:
    std::chrono::duration<double> timeElapsedDuringPerform;
    long iterations, stepSum, solutionsReviewedSum;
    CStatisticsCalculator timeStatsCalculator;
public:
    IStopwatch();
    virtual void measureExecutionTime(std::shared_ptr<IStrategy> const &, double) = 0;
    virtual void measureExecutionTime(std::shared_ptr<IStrategy> const &, long) = 0;
    CStatisticsCalculator getTimeStatsCalculator() const;
protected:
    virtual void measure(std::shared_ptr<IStrategy> const &) = 0;
};

#endif