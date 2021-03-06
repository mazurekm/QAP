#include <stdexcept>

#include "AlgorithmFactory.h"
#include <Algorithms/Random/Random.h>
#include <Algorithms/LocalSearch/Greedy.h>
#include <Algorithms/LocalSearch/Steepest.h>
#include <Algorithms/LocalSearch/_3_Opt.h>
#include <Algorithms/EnhancedLocalSearch/Metropolis.h>
#include <Algorithms/EnhancedLocalSearch/TabuSearch.h>
#include <boost/variant/get.hpp>
#include <iostream>

IStrategy *CAlgorithmFactory::create(const std::string &name, 
				     const Matrix &flow, 
				     const Matrix &distance,
				     const std::unordered_map<std::string, Setting> & algSettings,
				     bool gatherCost)
{
	if("Random" == name)
	{
		return new CRandom(flow, distance);
	}
	else if("Greedy" == name)
	{
		return new CGreedy(flow, distance, gatherCost);
	}
	else if("Steepest" == name)
	{
		return new CSteepest(flow, distance, gatherCost);	
	}
	else if("3_Opt" == name)
	{
		return new C_3_Opt(flow, distance, gatherCost);
	}
	else if("Metropolis" == name)
	{

		auto metropolis = new CMetropolis(
						flow, distance,
						boost::get<double>(algSettings.at("Samples")),
						boost::get<double>(algSettings.at("Alfa"))
		);

		return metropolis;
	}
	else if ("TabuSearch" == name) {
        CTabuListController tabuListController(
            flow.size(),
            boost::get<double>(algSettings.at("RatioOfTabuPeriodToSizeOfInstance")),
            unsigned(boost::get<double>(algSettings.at("AspirationThreshold")))
        );
        return new CTabuSearch(flow, distance, tabuListController,
                               boost::get<std::string>(algSettings.at("CandidateListMainQuantity")),
                               boost::get<double>(algSettings.at("RatioOfReviewedSolutionsForCandidatesList")),
                               boost::get<double>(algSettings.at("RatioOfCandidates")),
                               gatherCost
                              );
    }

	throw std::runtime_error("Incorrect algorithm");
}

IStrategy *CAlgorithmFactory::create(const std::string &name, 
				     const Matrix &flow, 
				     const Matrix &distance,
				     bool gatherCost) {
	std::unordered_map<std::string, Setting> emptyAlgSettings;
	return create(name, flow, distance, emptyAlgSettings, gatherCost);
}
