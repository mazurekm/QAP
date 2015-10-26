#include "Strategy.h"
#include <stdexcept>
#include <iostream>
#include <utility>

IStrategy::IStrategy(const Matrix &flow, const Matrix &distance):
	m_flow(flow),
	m_distance(distance),
	m_cost(0)
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

void IStrategy::computeCost() {
	for (size_t i = 0; i<m_result.size(); ++i) 
	{
		for (size_t j = i; j<m_result.size(); ++j)
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

// computeCost should be called before swap
void IStrategy::computeCost(std::pair<int, int> & swapIndicesPair) {
	substractFromCostAllArcsBoundWithPair(swapIndicesPair);
	std::swap(m_result[swapIndicesPair.first], m_result[swapIndicesPair.second]);
	addToCostAllArcsBoundWithPair(swapIndicesPair);	
	std::swap(m_result[swapIndicesPair.first], m_result[swapIndicesPair.second]);
}

void IStrategy::substractFromCostAllArcsBoundWithPair(std::pair<int, int> & swapIndicesPair) {
	for (size_t i = 0; i < m_result.size(); ++i) {
		m_cost -= m_distance.at(swapIndicesPair.first).at(i) * m_flow.at(m_result[swapIndicesPair.first]).at(m_result[i]);
	}
	for (size_t i = 0; i < m_result.size(); ++i) {
		m_cost -= m_distance.at(swapIndicesPair.second).at(i) * m_flow.at(m_result[swapIndicesPair.second]).at(m_result[i]);
	}
	m_cost += m_distance.at(swapIndicesPair.first).at(swapIndicesPair.second)
			  * m_flow.at(m_result[swapIndicesPair.first]).at(m_result[swapIndicesPair.second]);
}

void IStrategy::addToCostAllArcsBoundWithPair(std::pair<int, int> & swapIndicesPair) {
	for (size_t i = 0; i < m_result.size(); ++i) {
		m_cost += m_distance.at(swapIndicesPair.first).at(i) * m_flow.at(m_result[swapIndicesPair.first]).at(m_result[i]);
	}
	for (size_t i = 0; i < m_result.size(); ++i) {
		m_cost += m_distance.at(swapIndicesPair.second).at(i) * m_flow.at(m_result[swapIndicesPair.second]).at(m_result[i]);
	}
	m_cost -= m_distance.at(swapIndicesPair.first).at(swapIndicesPair.second)
			  * m_flow.at(m_result[swapIndicesPair.first]).at(m_result[swapIndicesPair.second]);
}
