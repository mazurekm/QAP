#include <iostream>
#include <string>
#include <memory>

#include <AlgorithmFactory.h>
#include <Utils/CommandLineProcessor/CommandLineProcessor.h>

int main(int argc, char **argv)
{
	std::string algName;
	std::string inputFile;

	std::unique_ptr<po::options_description> description(new po::options_description("Allowed option"));
	description->add_options()
		("help", "produce help message")
		("alg_name", po::value<std::string>(&algName)->default_value("Random"), "set algorithm")
		("input_file", po::value<std::string>(&inputFile), "set input file name");
	CCommandLineProcessor cmdLineProcessor(argc, argv, description);	
		
	try {
		cmdLineProcessor.validateHelp();
		cmdLineProcessor.validateInputFile();
	}
	catch (int errorCode) {
		return errorCode;
	}


	CAlgorithmFactory factory;
	std::unique_ptr<IStrategy> algPtr( factory.create(algName, Matrix(), Matrix() ) );

	return 0;
}