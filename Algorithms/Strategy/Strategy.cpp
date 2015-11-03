#include "Strategy.h"
#include <stdexcept>
#include <iostream>
#include <utility>
#include <climits>

IStrategy::IStrategy(const Matrix &flow, const Matrix &distance):
	m_flow(flow),
	m_distance(distance),
	m_cost(LONG_MAX)
{

}

std::vector<int> IStrategy::getResult() const
{
	return m_result;
}

long IStrategy::getCost() const
{
	return m_cost;
}

void IStrategy::computeCost() {
	m_cost = 0;
	for (size_t i = 0; i<m_result.size(); ++i) 
	{
		for (size_t j = 0; j<m_result.size(); ++j)
		{
			try
			{
				m_cost += m_distance.at(m_result[i]).at(m_result[j]) * m_flow.at(i).at(j);
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
void IStrategy::computeCost(const std::pair<int, int> & swapIndicesPair) {
	substractFromCostAllArcsBoundWithPair(swapIndicesPair);
	std::swap(m_result[swapIndicesPair.first], m_result[swapIndicesPair.second]);
	addToCostAllArcsBoundWithPair(swapIndicesPair);	
	std::swap(m_result[swapIndicesPair.first], m_result[swapIndicesPair.second]);
}

void IStrategy::substractFromCostAllArcsBoundWithPair(const std::pair<int, int> & swapIndicesPair) {
	for (size_t i = 0; i < m_result.size(); ++i) {
		m_cost -= m_distance.at(m_result[swapIndicesPair.first]).at(m_result[i]) * m_flow.at(swapIndicesPair.first).at(i);
		m_cost -= m_distance.at(m_result[i]).at(m_result[swapIndicesPair.first]) * m_flow.at(i).at(swapIndicesPair.first);
	}
	for (size_t i = 0; i < m_result.size(); ++i) {
		m_cost -= m_distance.at(m_result[swapIndicesPair.second]).at(m_result[i]) * m_flow.at(swapIndicesPair.second).at(i);
		m_cost -= m_distance.at(m_result[i]).at(m_result[swapIndicesPair.second]) * m_flow.at(i).at(swapIndicesPair.second);
	}
}

void IStrategy::addToCostAllArcsBoundWithPair(const std::pair<int, int> & swapIndicesPair) {
	for (size_t i = 0; i < m_result.size(); ++i) {
		m_cost += m_distance.at(m_result[swapIndicesPair.first]).at(m_result[i]) * m_flow.at(swapIndicesPair.first).at(i);
		m_cost += m_distance.at(m_result[i]).at(m_result[swapIndicesPair.first]) * m_flow.at(i).at(swapIndicesPair.first);	}
	for (size_t i = 0; i < m_result.size(); ++i) {
		m_cost += m_distance.at(m_result[swapIndicesPair.second]).at(m_result[i]) * m_flow.at(swapIndicesPair.second).at(i);
		m_cost += m_distance.at(m_result[i]).at(m_result[swapIndicesPair.second]) * m_flow.at(i).at(swapIndicesPair.second);
	}
}

void IStrategy::savePreviousResult() {
	m_prevResult = m_result;
	m_prevCost = m_cost;
}

void IStrategy::restorePreviousResultIfItWasBetter() {
	if (m_prevCost < m_cost) {
		m_result = m_prevResult;
		m_cost = m_prevCost;
	}
}
