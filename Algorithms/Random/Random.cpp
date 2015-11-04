#include "Random.h"
#include <algorithm>
#include <iterator>
#include <random>
#include <iostream>

CRandom::CRandom(const Matrix &flow, const Matrix &distance) : 
	IStrategy(flow, distance)
{
	int current = 0;
	std::generate_n(
			std::back_inserter(m_result), 
			m_distance.size(), 
			[&]()->int{ return current++; }
	);
}

void CRandom::perform()
{
	savePreviousResult();
	permute();
	computeCost();
	updateMeasureParams();
	restorePreviousResultIfItWasBetter();
}

void CRandom::permute() {
	std::random_device rd;
    std::mt19937 randomGen(rd());
	std::shuffle(m_result.begin(), m_result.end(), randomGen);
}
