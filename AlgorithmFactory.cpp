#include <stdexcept>

#include "AlgorithmFactory.h"
#include <Algorithms/Random/Random.h>
#include <Algorithms/LocalSearch/Greedy.h>
#include <Algorithms/LocalSearch/Steepest.h>
#include <Algorithms/LocalSearch/_3_Opt.h>

IStrategy *CAlgorithmFactory::create(const std::string &name, 
				     const Matrix &flow, 
				     const Matrix &distance)
{
	if("Random" == name)
	{
		return new CRandom(flow, distance);
	}
	else if("Greedy" == name)
	{
		return new CGreedy(flow, distance);
	}
	else if("Steepest" == name)
	{
		return new CSteepest(flow, distance);	
	}
	else if("3_Opt" == name)
	{
		return new C_3_Opt(flow, distance);
	}

	throw std::runtime_error("Incorrect algorithm");
}
