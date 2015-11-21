#include "Metropolis.h"
#include <utility>
#include <random>
#include <cmath>
#include <iostream>

CMetropolis::CMetropolis(const Matrix &flow, const Matrix &distance, 
						 unsigned samples, double alfa) :
	IEnhancedLocalSearch(flow, distance), 
	m_temperature(0), 
	m_alfa(alfa),
	m_samplesNum(samples)
{

	if(alfa < 1 && alfa > 0)
	{
		m_alfa = alfa;	 
	}

	computeInitTemp();
}

double CMetropolis::getTemperature() const
{
	return m_temperature;
}

void CMetropolis::performWithin()
{
	unsigned K = 0;
	auto currentCost = m_cost;
	auto bestLocalCost = m_cost;
	double currentTemp = 0;
	auto swapedIdxs = std::make_pair(0,0);

	do
	{
		currentTemp = std::pow(m_alfa, K) * m_temperature;
		++m_steps;
		unsigned L = K+1;
		for(size_t idx = 0; idx<L; ++idx)
		{
			int i = 0;
			int j = 0;

			while(i == j)
			{
				i = getRandomInt(0, m_distance.size()-1);
				j = getRandomInt(0, m_distance.size()-1);
			}

			swapedIdxs = std::make_pair(i, j);
			computeCost(swapedIdxs);
			++m_reviewedSolutions;

			if(m_cost < currentCost)
			{
				std::swap(m_result[i], m_result[j]);
				currentCost = m_cost;

				if(m_cost < bestLocalCost)
				{
					bestLocalCost = m_cost;
				}
			}
			else 
			{
				auto accept = std::exp(-(m_cost - currentCost)/currentTemp);

				if(accept > getRandomReal(0,1))
				{
					std::swap(m_result[i], m_result[j]);
					currentCost = m_cost;
				} 
				else
				{
					m_cost = currentCost;
				}
			}
		}

		++K;
	}
	while(currentTemp > 0.5);

	if(bestLocalCost < m_cost)
	{
		m_cost = bestLocalCost;
	}
}

void CMetropolis::computeInitTemp()
{
	for(unsigned idx = 0; idx<m_samplesNum; ++idx)
	{
		auto sol = initPermutation(m_distance.size());
		auto neigh = sol;

		int i = 0;
		int j = 0;

		while(i == j)
		{
			i = getRandomInt(0, m_distance.size()-1);
			j = getRandomInt(0, m_distance.size()-1);
		}

		std::swap(neigh[i], neigh[j]);

		auto e1 = computeCost(sol);
		auto e2 = computeCost(neigh);

		if(m_temperature < std::abs(e1-e2))
		{
			m_temperature = std::abs(e1-e2);
		}

	}
}

int CMetropolis::getRandomInt(int lhs, int rhs)
{
	std::random_device rd;
    std::mt19937 randomGen(rd());
    std::uniform_int_distribution<int> intDist(lhs, rhs);
    return intDist(randomGen);
}

double CMetropolis::getRandomReal(double lhs, double rhs)
{
	std::random_device rd;
    std::mt19937 randomGen(rd());
    std::uniform_real_distribution<double> realDist(lhs, rhs);
    return realDist(randomGen);
}