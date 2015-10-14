#include "Strategy.h"
#include <stdexcept>

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
	for(unsigned idx = 0; idx<m_result.size()-1; ++idx)
	{
		try
		{
			m_cost += m_distance.at(idx).at(idx+1) * m_flow.at(idx).at(idx+1);
		}
		catch(std::out_of_range &ex)		
		{
			m_cost = -1;		
			return;
		}
	}
}