#include "LocalSearch.h"

ILocalSearch::ILocalSearch(const Matrix &flow, const Matrix &distance, bool gatherCost) : 
	IStrategy(flow, distance), m_gatherCost(gatherCost)
{
}


void ILocalSearch::perform() {
	savePreviousResult();
	m_result = initPermutation(m_distance.size());
	computeCost();
	m_reviewedSolutions = 0;
	m_steps = 0;

	if(true == m_gatherCost)
	{
		m_beginSolutions.push_back(m_cost);
	}

	performWithin();
	
	if(true == m_gatherCost)
	{
		m_endSolutions.push_back(m_cost);
	}

	updateStats();
	restorePreviousResultIfItWasBetter();
}

CStatisticsCalculator ILocalSearch::getStepsStatsCalculator() const {
	return m_stepsStatsCalculator;
}

CStatisticsCalculator ILocalSearch::getReviewedSolutionsStatsCalculator() const {
	return m_reviewedSolutionsStatsCalculator;
}

std::vector<long> ILocalSearch::getFirstSolutionList() const
{
	return m_beginSolutions;
}

std::vector<long> ILocalSearch::getFinalSolutionList() const
{
	return m_endSolutions;
}

void ILocalSearch::updateStats() {
	m_costStatsCalculator.update(m_cost);
	m_reviewedSolutionsStatsCalculator.update(m_reviewedSolutions);
	m_stepsStatsCalculator.update(m_steps);
}