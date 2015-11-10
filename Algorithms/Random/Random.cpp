#include "Random.h"
#include <algorithm>
#include <iterator>
#include <random>
#include <iostream>

CRandom::CRandom(const Matrix &flow, const Matrix &distance) : 
	IStrategy(flow, distance)
{
	
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
	m_result = initPermutation(m_distance.size());
}
