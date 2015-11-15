#include "TimeMode.h"
#include <Algorithms/LocalSearch/LocalSearch.h>

#include <boost/algorithm/string.hpp>

#include <iostream>
#include <iterator>

CTimeMode::CTimeMode()
{

}

void CTimeMode::perform()
{
	for(auto & strategy : CConfManager::getInstance().getStrategies())
	{
		m_csv.add("Size", "Time", "TimeDeviation", "BestCost", "MeanCost","CostDeviation", "CostOptDist", 
				"MeanCostOptDist", "MeanSteps", "StepsDeviation", "MeanNumSolutions", "NumSolutionsDeviation");
		std::clog << "--------------- " << strategy << " ---------------" << std::endl;
		auto algSettings = CConfManager::getInstance().getAlgParameters(strategy);
		for(auto & instance : instanceMap) 
		{
			std::shared_ptr<IStrategy> currentAlgorithm (
		    	m_algorithmFactory.create(strategy, 
		    							instance.second.flows, 
		    							instance.second.distances,
		    							algSettings
		    	)
			);

			m_stopWatch.measureExecutionTime(currentAlgorithm, 
											 CConfManager::getInstance().getTimeLimit());
			auto cost = currentAlgorithm->getCost();
			setStatsCalculators(currentAlgorithm);

			std::clog << "Instance " <<instance.first <<": " << statsCalculatorMap.at("timeStats").getMean() << " " << cost << std::endl;
			std::ostream_iterator<int> beginIter(std::clog, " ");
			auto result = currentAlgorithm->getResult();
			std::clog << "Found solution: "; 
			std::copy(result.begin(), result.end(), beginIter);
			std::clog << std::endl;

			m_csv.add(instance.second.dimensionSize,
				    statsCalculatorMap.at("timeStats").getMean(),
				    statsCalculatorMap.at("timeStats").getStdDev(), cost,
				    statsCalculatorMap.at("costStats").getMean(),
				    statsCalculatorMap.at("costStats").getStdDev(), 
				    cost - instance.second.optimalSolution,
				    statsCalculatorMap.at("costStats").getMean() - instance.second.optimalSolution,
				    statsCalculatorMap.at("stepsStats").getMean(),
				    statsCalculatorMap.at("stepsStats").getStdDev(),
				    statsCalculatorMap.at("reviewedSolutionsStats").getMean(),
				    statsCalculatorMap.at("reviewedSolutionsStats").getStdDev()
				    );
		}
		m_csv.toFile(strategy+".csv");
		m_csv.clear();
	}
}

void CTimeMode::setStatsCalculators(const std::shared_ptr<IStrategy> & currentAlgorithm) {
	auto costStatsCalculator = currentAlgorithm->getCostStatsCalculator();
	auto timeStatsCalculator = m_stopWatch.getTimeStatsCalculator();
	statsCalculatorMap = {
		{"costStats", costStatsCalculator},
		{"timeStats", timeStatsCalculator},
		{"stepsStats", CStatisticsCalculator()},
		{"reviewedSolutionsStats", CStatisticsCalculator()}
	};

	auto ptr = std::dynamic_pointer_cast<ILocalSearch>(currentAlgorithm);
	if (nullptr != ptr)
	{
		statsCalculatorMap.at("stepsStats") = ptr->getStepsStatsCalculator();
		statsCalculatorMap.at("reviewedSolutionsStats") = ptr->getReviewedSolutionsStatsCalculator();
	}
}