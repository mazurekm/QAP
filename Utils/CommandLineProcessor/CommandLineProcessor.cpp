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

bool CCommandLineProcessor::validateHelp() {
    if(true == variablesMap.count("help")) {
        std::clog << *description << std::endl;
        return true;
    }
    return false;
}

void CCommandLineProcessor::validateConfigFile()
{
    if(false == variablesMap.count("config_file")) {
        std::cerr << "You must specify input file!" << std::endl;
        throw IncorrectArgumentException(); 
    }
    
    //move to data parser
    boost::filesystem::path path(variablesMap["config_file"].as<std::string>().c_str());
    if(false == boost::filesystem::is_regular_file(path)) {
        std::cerr << "Cant find file: " << path << std::endl;
        throw IncorrectArgumentException();
    }
}