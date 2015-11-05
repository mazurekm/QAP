#include "Greedy.h"
#include <algorithm>
#include <utility>

CGreedy::CGreedy(const Matrix &flow, const Matrix &distance, bool gatherCost) :
	ILocalSearch(flow, distance, gatherCost)
{

}

void CGreedy::performWithin()
{
	bool foundBetter;
	auto swapedIdxs = std::make_pair(0,0);
	do
	{
		++m_steps;
		foundBetter = false;
		for (size_t i = 0; i<m_result.size(); ++i)
		{
			if(true == foundBetter)
			{
				break;
			}

			for (size_t j = i+1; j<m_result.size(); ++j)
			{
				long currentCost = m_cost;
				swapedIdxs = std::make_pair(i, j);
				computeCost(swapedIdxs);
				++m_reviewedSolutions;
				if(m_cost < currentCost)
				{
					std::swap(m_result[i], m_result[j]);
					foundBetter = true;
					break;
				}
				else
				{
					m_cost = currentCost;
				}
			}
		}
	}
	while(true == foundBetter);
}