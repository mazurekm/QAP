#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>

#include <iostream>
#include <string>
#include <memory>

#include <AlgorithmFactory.h>

namespace po = boost::program_options;

int main(int argc, char **argv)
{
	std::string algName;
	std::string inputFile;

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("alg_name", po::value<std::string>(&algName)->default_value("Random"), "set algorithm")
		("input_file", po::value<std::string>(&inputFile), "set input file name");

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if(true == vm.count("help"))
	{
		std::clog << desc << std::endl;
    	return 1;
	}

	if(false == vm.count("input_file"))
	{
		std::cerr << "You must specify input file!" << std::endl;
		return -1; 
	}
	
	//move to data parser
	boost::filesystem::path path(inputFile.c_str());
	if(false == boost::filesystem::is_regular_file(path))
	{
  		std::cerr << "Cant find file: " << path << std::endl;
  		return -1;
	}

	CAlgorithmFactory factory;
	std::unique_ptr<IStrategy> algPtr( factory.create(algName, Matrix(), Matrix() ) );

	return 0;
}