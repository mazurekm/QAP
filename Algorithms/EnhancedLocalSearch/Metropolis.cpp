#include "Metropolis.h"
#include <utility>
#include <random>
#include <cmath>

CMetropolis::CMetropolis(const Matrix &flow, const Matrix &distance) :
	IEnhancedLocalSearch(flow, distance), m_temperature(8000), m_alfa(0.95)
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
    std::uniform_real_distribution<double> realDist(0.0, 1.0);
    //auto maxGradient = std::log(m_alfa) * m_temperature * m_temperature; 
	
	do
	{
		currentTemp = std::pow(m_alfa, K) * m_temperature;
		++m_steps;
		//unsigned L = std::log( maxGradient / ( currentTemp * std::pow(m_alfa, K) * std::log(m_alfa) * m_temperature) );
		for(size_t idx = 0; idx<m_distance.size()*m_distance.size()/2; ++idx)
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

			auto accept = std::exp(-(m_cost - currentCost)/currentTemp);
			if(accept > realDist(randomGen))
			{
				std::swap(m_result[i], m_result[j]);
				currentCost = m_cost;
				adaptiveTemp = currentTemp;
			} 
			else
			{
				m_cost = currentCost;
			}
		}

		++K;
	}
	while(currentTemp > 1);
	m_temperature = adaptiveTemp;
}
