#include "StartEndCostMode.h"
#include <Algorithms/LocalSearch/LocalSearch.h>

#include <boost/algorithm/string.hpp>
#include <iostream>

CStartEndCostMode::CStartEndCostMode()
{

}

void CStartEndCostMode::perform()
{
	for(auto & strategy : CConfManager::getInstance().getStrategies())
	{
		std::clog << "--------------- " << strategy << " ---------------" << std::endl;
		for(auto & instance : instanceMap) 
		{
			std::shared_ptr<IStrategy> currentAlgorithm (
		    	m_algorithmFactory.create(strategy, 
		    							instance.second.flows, 
		    							instance.second.distances, 
		    							true
		    	)
			);

			auto iterLimit = CConfManager::getInstance().getIterationLimit();

			m_stopWatch.measureExecutionTime(currentAlgorithm, static_cast<long>(iterLimit));
			auto ptr = std::dynamic_pointer_cast<ILocalSearch>(currentAlgorithm);

			m_csv.add("Iteration", "BeginSolution", "EndSolution");
			auto firstCostVec = ptr->getFirstSolutionList();
			auto finalCostVec = ptr->getFinalSolutionList();

			if(ptr != nullptr)
			{
				for(int i=1; i<=iterLimit; ++i)
				{
					m_csv.add(i, firstCostVec[i-1], finalCostVec[i-1]);
				}
			}

			std::vector<std::string> splitted; 
			boost::split(splitted,instance.first, boost::is_any_of("/"));

			std::string filename = strategy+"_"+splitted[splitted.size()-1]+"_.csv";

			std::clog << filename << std::endl;
			m_csv.toFile(filename);
			m_csv.clear();

		}
	}
}