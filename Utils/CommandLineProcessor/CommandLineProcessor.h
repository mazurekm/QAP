#ifndef COMMAND_LINE_PROCESSOR
#define COMMAND_LINE_PROCESSOR

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>

namespace po = boost::program_options;


class IncorrectArgumentException : public std::runtime_error
{
public:
    IncorrectArgumentException() : 
        std::runtime_error("Invalid command line argument")
    {

    }   
};

class CCommandLineProcessor {
    std::unique_ptr<po::options_description> description;
    po::variables_map variablesMap;
public:
    CCommandLineProcessor(int, char **, std::unique_ptr<po::options_description> &);
    std::unique_ptr<po::options_description> & getOptionsDescription();
    void validateConfigFile();
    bool validateHelp();
};

#endif