#include "Steepest.h"
#include <algorithm>
#include <utility>

CSteepest::CSteepest(const Matrix &flow, const Matrix &distance) :
	ILocalSearch(flow, distance)
{

}

void CSteepest::perform()
{
	m_result = initPermutation(m_distance.size());
	std::vector<int> currentSolution;
	while(true)
	{
		for(unsigned i = 0; i<m_result.size(); ++i)
		{
			for(unsigned j = i+1; j<m_result.size(); ++j)
			{
				double currentCost = m_cost;
				std::swap(m_result[i], m_result[j]);
				computeCost();
				if(m_cost < currentCost)
				{
					currentSolution = m_result;	
				}
				std::swap(m_result[i], m_result[j]);	
			}
			
		}

		if(m_result == currentSolution)
		{
			break;
		}
		
		m_result = currentSolution;
	}
}
