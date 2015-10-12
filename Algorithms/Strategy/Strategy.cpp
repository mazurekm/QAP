#include "Strategy.h"

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

}