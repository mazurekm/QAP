#include "Metropolis.h"
#include <utility>
#include <random>
#include <cmath>

CMetropolis::CMetropolis(const Matrix &flow, const Matrix &distance, 
						 double temperature, double alfa) :
	IEnhancedLocalSearch(flow, distance), 
	m_temperature(temperature), 
	m_alfa(0.95)
{

	if(alfa < 1 && alfa > 0)
	{
		m_alfa = alfa;	 
	}
}

double CMetropolis::getTemperature() const
{
	return m_temperature;
}

void CMetropolis::performWithin()
{
	unsigned K = 0;
	auto currentCost = m_cost;
	double currentTemp = 0;
	auto swapedIdxs = std::make_pair(0,0);
	auto adaptiveTemp = m_temperature;

	std::random_device rd;
    std::mt19937 randomGen(rd());
    std::uniform_int_distribution<int> intDist(0, m_distance.size()-1);
    std::uniform_real_distribution<double> realDist(0.0, 0.999);

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
				i = intDist(randomGen);
				j = intDist(randomGen);
			}

			swapedIdxs = std::make_pair(i, j);
			computeCost(swapedIdxs);
			++m_reviewedSolutions;

			if(m_cost < currentCost)
			{
				std::swap(m_result[i], m_result[j]);
				currentCost = m_cost;
				adaptiveTemp = currentTemp;
			}
			else 
			{
				auto accept = std::exp(-(m_cost - currentCost)/currentTemp);

				if(accept > realDist(randomGen))
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
	m_temperature = adaptiveTemp;
}
