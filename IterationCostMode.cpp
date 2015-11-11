#include "IterationCostMode.h"
#include <boost/algorithm/string.hpp>
#include <iostream>


CIterationCostMode::CIterationCostMode()
{

}

void CIterationCostMode::perform()
{
	for(auto & strategy : CConfManager::getInstance().getStrategies())
	{
		std::clog << "--------------- " << strategy << " ---------------" << std::endl;
		for(auto & instance : instanceMap) 
		{
			std::shared_ptr<IStrategy> currentAlgorithm (
		    	m_algorithmFactory.create(strategy, 
		    							instance.second.flows, 
		    							instance.second.distances
		    	)
			);

			m_csv.add("iterations", "bestCost", "meanCost", "deviation");
			for(unsigned idx = 50; idx <= 400; idx+=50 )
			{
				m_stopWatch.measureExecutionTime(currentAlgorithm, static_cast<long>(idx));
				auto cost = currentAlgorithm->getCost();
				auto costStatsCalculator = currentAlgorithm->getCostStatsCalculator();
				m_csv.add(idx, cost, costStatsCalculator.getMean(), costStatsCalculator.getStdDev());
			}

			std::vector<std::string> splitted; 
			boost::split(splitted,instance.first, boost::is_any_of("/"));
			std::string filename = strategy+"_"+splitted[splitted.size()-1]+"_cost_.csv";
			std::clog << filename << std::endl;
			m_csv.toFile(filename);
			m_csv.clear();
		}
	}
}