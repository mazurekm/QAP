#include "LocalSearch.h"
#include <algorithm>
#include <iterator>
#include <random>

ILocalSearch::ILocalSearch(const Matrix &flow, const Matrix &distance) : 
	IStrategy(flow, distance), m_steps(0), m_reviewedSolutions(0)
{
}

std::vector<int> ILocalSearch::initPermutation(unsigned N)
{
	std::vector<int> result;
	int current = 0;
	std::generate_n(
			std::back_inserter(result), 
			N, 
			[&]()->int{ return current++; }
	);

	std::random_device rd;
    std::mt19937 randomGen(rd());
	std::shuffle(result.begin(), result.end(), randomGen);
	
	return result;
}

void ILocalSearch::perform() {
	savePreviousResult();
	m_result = initPermutation(m_distance.size());
	computeCost();
	m_beginSolutions.push_back(m_cost);
	performWithin();
	m_endSolutions.push_back(m_cost);
	updateMeasureParams();
	restorePreviousResultIfItWasBetter();
}

double ILocalSearch::getMeanSteps() const {
	return m_steps / double(m_performNumber);
}

double ILocalSearch::getMeanReviewedSolutions() const {
	return m_reviewedSolutions / double(m_performNumber);
}
