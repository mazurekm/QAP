#ifndef ALGORITHM_FACTORY
#define ALGORITHM_FACTORY

#include <string>
#include <unordered_map>

#include <Algorithms/Strategy/Strategy.h>
#include <Utils/ConfManager/Setting.h>

class CAlgorithmFactory
{
public:
	IStrategy *create(const std::string &name, 
					  const Matrix &flow, 
					  const Matrix &distance, 
                      const std::unordered_map<std::string, Setting> &,
					  bool gatherCost = false);
    IStrategy *create(const std::string &name, 
                      const Matrix &flow, 
                      const Matrix &distance, 
                      bool gatherCost = false);
};

#endif