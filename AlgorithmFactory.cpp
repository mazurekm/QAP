#include <stdexcept>

#include "AlgorithmFactory.h"
#include <Algorithms/Random/Random.h>
#include <Algorithms/LocalSearch/Greedy.h>
#include <Algorithms/LocalSearch/Steepest.h>
#include <Algorithms/LocalSearch/_3_Opt.h>

IStrategy *CAlgorithmFactory::create(const std::string &name, 
				     const Matrix &flow, 
				     const Matrix &distance,
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

	throw std::runtime_error("Incorrect algorithm");
}
