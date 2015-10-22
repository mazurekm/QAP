#include <stdexcept>

#include "AlgorithmFactory.h"
#include <Algorithms/Random/Random.h>
#include <Algorithms/LocalSearch/Greedy.h>
#include <Algorithms/LocalSearch/Steepest.h>

IStrategy *CAlgorithmFactory::create(const std::string &name, 
									 const Matrix &flow, 
									 const Matrix &distance)
{
	if("Random" == name)
	{
		return new CRandom(flow, distance);
	}
	else if("Greedy")
	{
		return new CGreedy(flow, distance);
	}
	else if("CSteepest")
	{
		return new CSteepest(flow, distance);	
	}

	throw std::runtime_error("Incorrect algorithm");
}