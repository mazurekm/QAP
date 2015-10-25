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
	
	do
	{
		foundBetter = false;
		for(unsigned i = 0; i<m_result.size(); ++i)
		{
			if(true == foundBetter)
			{
				break;
			}

			for(unsigned j = i+1; j<m_result.size(); ++j)
			{
				double currentCost = m_cost;
				std::swap(m_result[i], m_result[j]);
				computeCost();
				if(m_cost > currentCost)
				{
					std::swap(m_result[i], m_result[j]);
					m_cost = currentCost;
				}
				else
				{
					foundBetter = true;
					break;
				}
			}
		}
	}
	while(true == foundBetter);
}