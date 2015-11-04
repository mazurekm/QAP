#include "Mode.h"
#include <Algorithms/LocalSearch/LocalSearch.h>

#include <iostream>


IMode::IMode()
{

}

void IMode::loadInstances()
{
	for(auto & instanceFilename : CConfManager::getInstance().getInputData())
	{
		std::clog << "Reading ";
		std::clog << instanceFilename.first << " " << instanceFilename.second << std::endl;
		instanceMap[instanceFilename.first] = InstanceLoader::loadInstanceFromFile(
									instanceFilename.first, instanceFilename.second
								);
	}
}

void IMode::operator()()
{
	loadInstances();
	perform();
}
