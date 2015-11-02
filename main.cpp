#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <algorithm>

#include <AlgorithmFactory.h>
#include <Utils/CommandLineProcessor/CommandLineProcessor.h>
#include <Utils/SmartStopwatch/SmartStopwatch.h>
#include <Utils/ConfManager/ConfManager.h>
#include <Utils/InstanceLoader/InstanceLoader.h>
#include <Utils/CsvHelper/CsvHelper.h>

void processAllAlgorithms(CAlgorithmFactory & algorithmFactory, std::unique_ptr<CConfManager> const & confManager) {
	
	std::unique_ptr<IStopwatch> stopWatchPtr(new SmartStopwatch());
	CCsvHelper csvHelper;
	std::map<std::string, Instance> instanceMap;

	for(auto & instanceFilename : confManager->getInputData())
	{
		instanceMap[instanceFilename.first] = InstanceLoader::loadInstanceFromFile(
									instanceFilename.first, instanceFilename.second
								);
	}

	for(auto & strategy : confManager->getStrategies())
	{
		std::clog << "--------------- " << strategy << " ---------------" << std::endl;
		for(auto & instance : instanceMap) 
		{
			std::unique_ptr<IStrategy> currentAlgorithm (
		    	algorithmFactory.create(strategy, 
		    							instance.second.flows, 
		    							instance.second.distances
		    	)
			);

			stopWatchPtr->measureExecutionTime(currentAlgorithm, confManager->getTimeLimit());
			double cost = currentAlgorithm->getCost();
			double time = stopWatchPtr->getTimeElapsed().count();

			std::clog << "Instance " <<instance.first <<": " <<time << " " << cost << std::endl;

			csvHelper.add(time, cost);
		}
	}
}

int main(int argc, char **argv)
{

	std::unique_ptr<po::options_description> description(
		new po::options_description("Allowed option")
	);

	std::string configPath;
	description->add_options()
		("help", "produce help message")
		("config_file", po::value<std::string>(&configPath) ,"path to json config file");


	CCommandLineProcessor cmdLineProcessor(argc, argv, description);	
	
	if(true == cmdLineProcessor.validateHelp() )
	{
		return -1;
	}
	
	try 
	{
		cmdLineProcessor.validateConfigFile();
	}
	catch (const IncorrectArgumentException &ex) 
	{
		std::clog << ex.what() << std::endl;
		return -1;
	}

	std::unique_ptr<CConfManager> confManager;

	try
	{
		confManager.reset(new CConfManager(configPath));
	}
	catch(const JsonNotFoundException &ex)
	{
		return -1;
	}
	catch(const JsonParseException &ex)
	{
		return -1;	
	}

	CAlgorithmFactory factory;
	
	try
	{
		processAllAlgorithms(factory, confManager);
	}
	catch(const DataFileNotFoundException & ex)
	{
		std::cerr << ex.what() << std::endl;
		return -1;
	}	

	std::clog << "Done :)" << std::endl;
	return 0;
}