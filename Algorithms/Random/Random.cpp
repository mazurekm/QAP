#include "Random.h"
#include <algorithm>
#include <iterator>
#include <random>

CRandom::CRandom(const Matrix &flow, const Matrix &distance) : 
	IStrategy(flow, distance)
{

}

void CRandom::perform()
{
	int current = 0;
	std::generate_n(
			std::back_inserter(m_result), 
			m_distance.size(), 
			[&]()->int{ return ++current; }
	);

	std::random_device rd;
    std::mt19937 randomGen(rd());
	std::shuffle(m_result.begin(), m_result.end(), randomGen);

	computeCost();
}
