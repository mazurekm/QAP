#include <stdexcept>

#include "AlgorithmFactory.h"
#include <Algorithms/Random/Random.h>

IStrategy *CAlgorithmFactory::create(const std::string &name, 
									 const Matrix &flow, 
									 const Matrix &distance)
{
	if("Random" == name)
	{
		return new CRandom(flow, distance);
	}

	throw std::runtime_error("Incorrect algorithm");
}