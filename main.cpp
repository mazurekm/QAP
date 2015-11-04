#include <iostream>
#include <string>
#include <memory>

#include "ModeFactory.h"
#include <Utils/CommandLineProcessor/CommandLineProcessor.h>

	

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

	try
	{
		CConfManager::getInstance().loadConfiguration(configPath);
	}
	catch(const JsonNotFoundException &ex)
	{
		std::clog << ex.what() << std::endl;
		return -1;
	}
	catch(const JsonParseException &ex)
	{
		std::clog << ex.what() << std::endl;
		return -1;	
	}
	
	CModeFactory factory;

	try
	{
		for(auto & mode : CConfManager::getInstance().getModes())
		{
			std::unique_ptr<IMode> ptr ( factory.create(mode) );
			(*ptr)();
		}
	}
	catch(const DataFileNotFoundException & ex)
	{
		std::cerr << ex.what() << std::endl;
		return -1;
	}	

	std::clog << "Done :)" << std::endl;
	return 0;
}