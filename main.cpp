#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <algorithm>

#include <AlgorithmFactory.h>
#include <Utils/CommandLineProcessor/CommandLineProcessor.h>
#include <Utils/SmartStopwatch/SmartStopwatch.h>
#include <Utils/ConfManager/ConfManager.h>
#include <Utils/InstanceLoader/InstanceLoader.h>

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
	std::unique_ptr<IStopwatch> stopWatchPtr(new SmartStopwatch());
	std::list<std::unique_ptr<IStrategy> > strategyList;

	for(auto & instance : confManager->getInputData())
	{
		for(auto & strategy : confManager->getStrategies())
		{
			strategyList.push_back(
				std::unique_ptr<IStrategy>(
					factory.create(strategy, Matrix(), Matrix())
				)
			);
		}
	}

	std::clog << "Done :)" << std::endl;
	return 0;
}