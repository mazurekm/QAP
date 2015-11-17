#include "EnhancedLocalSearch.h"

IEnhancedLocalSearch::IEnhancedLocalSearch(const Matrix &flow, const Matrix &distance) :
    IStrategy(flow, distance) {

}

void IEnhancedLocalSearch::perform() {
	savePreviousResult();
	m_result = initPermutation(m_distance.size());
	computeCost();
	m_reviewedSolutions = 0;
	m_steps = 0;

	performWithin();
	updateStats();
	restorePreviousResultIfItWasBetter();
}


CStatisticsCalculator IEnhancedLocalSearch::getStepsStatsCalculator() const {
	return m_stepsStatsCalculator;
}

CStatisticsCalculator IEnhancedLocalSearch::getReviewedSolutionsStatsCalculator() const {
	return m_reviewedSolutionsStatsCalculator;
}


void IEnhancedLocalSearch::updateStats() {
	m_costStatsCalculator.update(m_cost);
	m_reviewedSolutionsStatsCalculator.update(m_reviewedSolutions);
	m_stepsStatsCalculator.update(m_steps);
}