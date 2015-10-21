#include <iostream>
#include <string>
#include <memory>

#include <AlgorithmFactory.h>
#include <Utils/CommandLineProcessor/CommandLineProcessor.h>
#include <Utils/SmartStopwatch/SmartStopwatch.h>

int main(int argc, char **argv)
{
	std::string algName;
	std::string inputFile;
	long iterations;
	// we'll be in config file
	double timeLimit = 10.0;

	std::unique_ptr<po::options_description> description(new po::options_description("Allowed option"));
	description->add_options()
		("help", "produce help message")
		("alg_name", po::value<std::string>(&algName)->default_value("Random"), "set algorithm")
		("input_file", po::value<std::string>(&inputFile), "set input file name")
		("iterations", po::value<long>(&iterations)->default_value(1000000), "set iterations");
	CCommandLineProcessor cmdLineProcessor(argc, argv, description);	
		
	try {
		cmdLineProcessor.validateHelp();
		cmdLineProcessor.validateInputFile();
		cmdLineProcessor.validateIterations();
	}
	catch (int errorCode) {
		return errorCode;
	}

	CAlgorithmFactory factory;
	std::unique_ptr<IStrategy> algPtr( factory.create(algName, Matrix(), Matrix() ) );
	std::unique_ptr<IStopwatch> stopWatchPtr(new SmartStopwatch());
	stopWatchPtr->measureExecutionTime(algPtr, timeLimit);
	return 0;
}