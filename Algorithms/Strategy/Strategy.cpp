#include "Strategy.h"
#include <stdexcept>
#include <iostream>

IStrategy::IStrategy(const Matrix &flow, const Matrix &distance):
	m_flow(flow),
	m_distance(distance)
{

}

std::vector<int> IStrategy::getResult() const
{
	return m_result;
}

double IStrategy::getCost() const
{
	return m_cost;
}

void IStrategy::computeCost()
{
	for(unsigned i = 0; i<m_result.size(); ++i) 
	{
		for(unsigned j = 0; j<m_result.size(); ++j)
		{
			try
			{
				m_cost += m_distance.at(i).at(j) * m_flow.at(m_result[i]).at(m_result[j]);
			}
			catch(std::out_of_range & ex)
			{
				std::clog << ex.what() << std::endl;
				return;
			}
		}
	}
}