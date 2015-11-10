#include "LocalSearch.h"

ILocalSearch::ILocalSearch(const Matrix &flow, const Matrix &distance, bool gatherCost) : 
	IStrategy(flow, distance), m_steps(0), m_reviewedSolutions(0), m_gatherCost(gatherCost)
{
}


void ILocalSearch::perform() {
	savePreviousResult();
	m_result = initPermutation(m_distance.size());
	computeCost();

	if(true == m_gatherCost)
	{
		m_beginSolutions.push_back(m_cost);
	}

	performWithin();
	
	if(true == m_gatherCost)
	{
		m_endSolutions.push_back(m_cost);
	}

	updateMeasureParams();
	restorePreviousResultIfItWasBetter();
}

double ILocalSearch::getMeanSteps() const {
	return m_steps / double(m_performNumber);
}

double ILocalSearch::getMeanReviewedSolutions() const {
	return m_reviewedSolutions / double(m_performNumber);
}

std::vector<long> ILocalSearch::getFirstSolutionList() const
{
	return m_beginSolutions;
}

std::vector<long> ILocalSearch::getFinalSolutionList() const
{
	return m_endSolutions;
}