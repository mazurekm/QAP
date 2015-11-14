#include "Metropolis.h"
#include <utility>
#include <random>
#include <cmath>

CMetropolis::CMetropolis(const Matrix &flow, const Matrix &distance) :
	IEnhancedLocalSearch(flow, distance), m_temperature(1200), m_alfa(0.95)
{

}

void CMetropolis::setParameters(double temperature, double alfa)
{
	m_temperature = temperature;
	m_adaptiveTemp = temperature;
	if(alfa < 1 && alfa > 0)
	{
		m_alfa = alfa;	 
	}
}

double CMetropolis::getAdaptiveTemp() const
{
	return m_adaptiveTemp;
}

double CMetropolis::getTemperature() const
{
	return m_temperature;
}

void CMetropolis::perform()
{
	m_result = initPermutation(m_distance.size());
	computeCost();

	unsigned K = 1;
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
		currentTemp = std::pow(m_alfa, K) * m_adaptiveTemp;

		for(size_t idx = 0; idx<K; ++idx)
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

			auto accept = std::exp(-(m_cost - currentCost)/currentTemp);
			if(accept > realDist(randomGen))
			{
				std::swap(m_result[i], m_result[j]);
				currentCost = m_cost;
				m_adaptiveTemp = currentTemp;
				foundBetter = true;
			} 
		}

	}
	while(true == foundBetter);
}
