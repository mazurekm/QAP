#include <Utils/InstanceLoader/InstanceLoader.h>
#include <boost/lexical_cast.hpp>
#include <regex>
#include <iostream>
#include <iterator>
#include <algorithm>

InstanceLoader::InstanceLoader(const std::string & fileName, const std::string & solution) : 
    inputStream(fileName, std::ifstream::in),
    solutionStream(solution, std::ifstream::in) 
{
    if ( inputStream.fail() || solutionStream.fail() ) 
    {
        throw DataFileNotFoundException();
    }
}

Instance InstanceLoader::loadInstanceFromFile (
                        const std::string &fileName, 
                        const std::string & solution
                    ) 
{
    InstanceLoader instanceLoader(fileName, solution);
    auto retVal = instanceLoader.load();
    return retVal;
}

Instance InstanceLoader::load() {
    loadDimensionSizeIntoInstance();
    loadDistancesIntoInstance();
    loadFlowsIntoInstance();
    loadOptimalSolution();
    return instance;
}

void InstanceLoader::loadDimensionSizeIntoInstance() {
    inputStream >> instance.dimensionSize;
}

void InstanceLoader::loadDistancesIntoInstance() {
   loadMatrixIntoContainer(instance.distances); 
}

void InstanceLoader::loadFlowsIntoInstance() {
    loadMatrixIntoContainer(instance.flows);
}

void InstanceLoader::loadMatrixIntoContainer(std::vector<std::vector<int>> & container) {
    for (int i = 0; i < instance.dimensionSize; ++i) {
        container.push_back(std::vector<int>());
        for (int j = 0; j < instance.dimensionSize; ++j) {
            int value;
            inputStream >> value;
            container.back().push_back(value);
        }
    }
}

InstanceLoader::~InstanceLoader() {
    inputStream.close();
    solutionStream.close();
}

void InstanceLoader::loadOptimalSolution()
{
    std::regex rg("[0-9]+");
    std::string line; 
   
    std::getline(solutionStream, line);
    auto wordsBegin = std::sregex_iterator(line.begin(), line.end(), rg);
    instance.optimalSolution = boost::lexical_cast<double>((++wordsBegin)->str());

    std::getline(solutionStream, line);
    wordsBegin = std::sregex_iterator(line.begin(), line.end(), rg);
    auto wordsEnd = std::sregex_iterator();
    std::for_each(wordsBegin, wordsEnd, [&](const std::smatch & el) {
                instance.optimalPermutation.push_back(boost::lexical_cast<int>(el.str()));
            }
    );
}
