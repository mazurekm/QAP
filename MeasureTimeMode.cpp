#include "MeasureTimeMode.h"
#include <Algorithms/LocalSearch/LocalSearch.h>

#include <boost/algorithm/string.hpp>

#include <iostream>
#include <iterator>

CMeasureTimeMode::CMeasureTimeMode()
{

}

void CMeasureTimeMode::perform()
{
	for(auto & strategy : CConfManager::getInstance().getStrategies())
	{
		m_csv.add("Size", "Time", "BestCost", "MeanCost","CostDeviation", "CostOptDist", 
				"MeanCostOptDist", "MeanSteps", "MeanNumSolutions");
		std::clog << "--------------- " << strategy << " ---------------" << std::endl;
		for(auto & instance : instanceMap) 
		{
			std::shared_ptr<IStrategy> currentAlgorithm (
		    	m_algorithmFactory.create(strategy, 
		    							instance.second.flows, 
		    							instance.second.distances
		    	)
			);

			m_stopWatch.measureExecutionTime(currentAlgorithm, 
											 CConfManager::getInstance().getTimeLimit());
			auto cost = currentAlgorithm->getCost();
			auto time = m_stopWatch.getMeanTimePerIteration();
			auto meanCost = currentAlgorithm->getMeanCost();
			auto costDeviation = currentAlgorithm->getStdDevCost();

			double meanSteps = -1;
			double meanSol = -1;
			auto ptr = std::dynamic_pointer_cast<ILocalSearch>(currentAlgorithm);

			if(ptr != nullptr)
			{
				meanSteps = ptr->getMeanSteps();
				meanSol = ptr->getMeanReviewedSolutions();
			}

			std::clog << "Instance " <<instance.first <<": " <<time << " " << cost << std::endl;
			std::ostream_iterator<int> beginIter(std::clog, " ");
			auto result = currentAlgorithm->getResult();
			std::clog << "Found solution: "; 
			std::copy(result.begin(), result.end(), beginIter);
			std::clog << std::endl;

			m_csv.add(instance.second.dimensionSize,
				    time, cost, meanCost, costDeviation, 
				    cost - instance.second.optimalSolution,
				    meanCost - instance.second.optimalSolution,
				    meanSteps, meanSol
				    );
		}
		m_csv.toFile(strategy+".csv");
		m_csv.clear();
	}
}