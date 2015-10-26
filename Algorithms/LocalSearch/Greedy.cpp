#include "Greedy.h"
#include <algorithm>
#include <utility>

CGreedy::CGreedy(const Matrix &flow, const Matrix &distance) :
	ILocalSearch(flow, distance)
{

}

void CGreedy::perform()
{
	m_result = initPermutation(m_distance.size());
	computeCost();
	bool foundBetter;
	auto swapedIdxs = std::make_pair(0,0);
	
	do
	{
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
				if(m_cost > currentCost)
				{
					m_cost = currentCost;
				}
				else
				{
					std::swap(m_result[i], m_result[j]);
					foundBetter = true;
					break;
				}
			}
		}
	}
	while(true == foundBetter);
}