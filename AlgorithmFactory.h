#ifndef ALGORITHM_FACTORY
#define ALGORITHM_FACTORY

#include <string>

#include <Algorithms/Strategy/Strategy.h>

class CAlgorithmFactory
{
public:
	IStrategy *create(const std::string &name, 
					  const Matrix &flow, 
					  const Matrix &distance,
					  bool gatherCost = false);
};

#endif