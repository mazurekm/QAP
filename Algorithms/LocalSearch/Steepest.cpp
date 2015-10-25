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
	double currentCost = 0;
	auto swapedIdxs = std::make_pair(0,0);

	while(true)
	{
		for(unsigned i = 0; i<m_result.size(); ++i)
		{
			for(unsigned j = i+1; j<m_result.size(); ++j)
			{
				currentCost = m_cost;
				std::swap(m_result[i], m_result[j]);
				computeCost();
				if(m_cost < currentCost)
				{
					swapedIdxs = std::make_pair(i,j);
				}
				else
				{
					m_cost = currentCost;
				}
				std::swap(m_result[i], m_result[j]);

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
