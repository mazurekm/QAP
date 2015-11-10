#include "Metropolis.h"
#include <utility>
#include <random>
#include <cmath>

CMetropolis::CMetropolis(const Matrix &flow, const Matrix &distance) :
	IStrategy(flow, distance)
{

}

void CMetropolis::setParameters(double temperature, double alfa)
{
	m_temperature = temperature;
	if(alfa < 1 && alfa > 0)
	{
		m_alfa = alfa;	 
	}
}

void CMetropolis::perfom()
{
	m_result = initPermutation(m_distance.size());
	computeCost();

	auto L = m_distance.size() * m_distance.size() * 0.5;
	auto k = 1;
	bool foundBetter = true;
	auto currentCost = m_cost;
	double currentTemp = 0;
	auto swapedIdxs = std::make_pair(0,0);

	std::random_device rd;
    std::mt19937 randomGen(rd());
    std::uniform_int_distribution<int> intDist(0, m_distance.size()-1);
    std::uniform_real_distribution<double> realDist(0.0, 1.0);

	do
	{
		foundBetter = false;
		currentTemp = std::pow(m_alfa, k) * m_temperature;

		for(size_t idx = 0; idx<L; ++idx)
		{
			int i = 0;
			int j = 0;

			while(i == j)
			{
				i = intDist(randomGen);
				j = intDist(randomGen);
			}

			swapedIdxs = std::make_pair(i, j);
			computeCost(swapedIdxs);

			auto probValue = std::exp(-(m_cost - currentCost)/currentTemp);
			if(probValue > realDist(randomGen))
			{
				std::swap(m_result[i], m_result[j]);
				currentCost = m_cost;
				foundBetter = true;
			} 
		}

	}
	while(true == foundBetter);

}