#include "Steepest.h"
#include <algorithm>
#include <utility>
#include <iterator>

CSteepest::CSteepest(const Matrix &flow, const Matrix &distance, bool gatherCost) :
	ILocalSearch(flow, distance, gatherCost)
{
}

void CSteepest::performWithin()
{
	auto swapedIdxs = std::make_pair(0,0);
	long oldCost = m_cost;
	long currentCost = m_cost;
	
	while(true)
	{
		++m_steps;
		for (size_t i = 0; i<m_result.size(); ++i)
		{
			for (size_t j = i+1; j<m_result.size(); ++j)
			{
				computeCost(std::make_pair(i,j));
				++m_reviewedSolutions;
				if(m_cost < currentCost)
				{
					swapedIdxs = std::make_pair(i, j);
					currentCost = m_cost;
				}
				m_cost = oldCost;
			}
		}

		if(swapedIdxs.first == swapedIdxs.second)
		{
			break;
		}

		m_cost = currentCost;
		oldCost = currentCost;
		std::swap(m_result[swapedIdxs.first], m_result[swapedIdxs.second]);
		swapedIdxs = std::make_pair(0,0);
	}
}
