#include "Steepest.h"
#include <algorithm>
#include <utility>
#include <iostream>
#include <iterator>

CSteepest::CSteepest(const Matrix &flow, const Matrix &distance) :
	ILocalSearch(flow, distance)
{

}

void CSteepest::perform()
{
	m_result = initPermutation(m_distance.size());
	computeCost();
	long currentCost = 0;
	auto swapedIdxs = std::make_pair(0,0);

	while(true)
	{
		for (size_t i = 0; i<m_result.size(); ++i)
		{
			for (size_t j = i+1; j<m_result.size(); ++j)
			{
				swapedIdxs = std::make_pair(i, j);
				currentCost = m_cost;
				computeCost(swapedIdxs);
				if(m_cost < currentCost)
				{
					swapedIdxs = std::make_pair(i,j);
				}
				else
				{
					m_cost = currentCost;
				}

			}
			
		}

		if(swapedIdxs.first == swapedIdxs.second)
		{
			break;
		}
		std::swap(m_result[swapedIdxs.first], m_result[swapedIdxs.second]);
		swapedIdxs = std::make_pair(0,0);
	}
}
