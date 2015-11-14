#ifndef LOCAL_SEARCH
#define LOCAL_SEARCH

#include <Algorithms/Strategy/Strategy.h>
#include <Utils/StatisticsCalculator/StatisticsCalculator.h>
#include <vector>

class ILocalSearch : public IStrategy
{
public:
	ILocalSearch(const Matrix &flow, const Matrix &distance, bool gatherCost = false);
	virtual void perform();
    CStatisticsCalculator getStepsStatsCalculator() const;
    CStatisticsCalculator getReviewedSolutionsStatsCalculator() const;
    
    std::vector<long> getFirstSolutionList() const;
    std::vector<long> getFinalSolutionList() const;

protected:
    virtual void performWithin() = 0;
    void updateStats();

    long m_steps, m_reviewedSolutions;
    CStatisticsCalculator m_stepsStatsCalculator, m_reviewedSolutionsStatsCalculator;
    bool m_gatherCost;

    std::vector<long> m_beginSolutions;
    std::vector<long> m_endSolutions;
};

#endif