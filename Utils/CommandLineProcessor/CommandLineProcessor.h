#ifndef COMMAND_LINE_PROCESSOR
#define COMMAND_LINE_PROCESSOR

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/filesystem.hpp>

namespace po = boost::program_options;

class CCommandLineProcessor {
    std::unique_ptr<po::options_description> description;
    po::variables_map variablesMap;
public:
    CCommandLineProcessor(int, char **, std::unique_ptr<po::options_description> &);
    std::unique_ptr<po::options_description> & getOptionsDescription();
    void validateHelp();
    void validateInputFile();
};

#endif