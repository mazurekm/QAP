#include <Utils/CommandLineProcessor/CommandLineProcessor.h>
#include <iostream>
#include <string>
#include <memory>

CCommandLineProcessor::CCommandLineProcessor(int argc, char **argv, std::unique_ptr<po::options_description> & desc) {
    description = std::move(desc);
    po::store(po::parse_command_line(argc, argv, *description), variablesMap);
    po::notify(variablesMap);
}

std::unique_ptr<po::options_description> & CCommandLineProcessor::getOptionsDescription() {
    return description;
}

void CCommandLineProcessor::validateHelp() {
    if(true == variablesMap.count("help")) {
        std::clog << *description << std::endl;
        throw 1;
    }
}

void CCommandLineProcessor::validateInputFile() {
    if(false == variablesMap.count("input_file")) {
        std::cerr << "You must specify input file!" << std::endl;
        throw -1; 
    }
    
    //move to data parser
    boost::filesystem::path path(variablesMap["input_file"].as<std::string>().c_str());
    if(false == boost::filesystem::is_regular_file(path)) {
        std::cerr << "Cant find file: " << path << std::endl;
        throw -1;
    }
}

void CCommandLineProcessor::validateIterations() {
     
    if (false == variablesMap.count("iterations")) {
        std::cerr << "You mest specify iterations!" << std::endl;
        throw -1;
    }
}