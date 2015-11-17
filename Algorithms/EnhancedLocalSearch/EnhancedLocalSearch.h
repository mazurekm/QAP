#ifndef ENHANCED_LOCAL_SEARCH
#define ENHANCED_LOCAL_SEARCH

#include <Algorithms/Strategy/Strategy.h>
#include <Utils/StatisticsCalculator/StatisticsCalculator.h>

class IEnhancedLocalSearch : public IStrategy {
    
public:
    IEnhancedLocalSearch(const Matrix &flow, const Matrix &distance);
    virtual void perform();
    CStatisticsCalculator getStepsStatsCalculator() const;
    CStatisticsCalculator getReviewedSolutionsStatsCalculator() const;

protected:      
	virtual void performWithin() = 0;
	void updateStats();
	long m_steps, m_reviewedSolutions; 
	CStatisticsCalculator m_stepsStatsCalculator, m_reviewedSolutionsStatsCalculator;
};

#endif