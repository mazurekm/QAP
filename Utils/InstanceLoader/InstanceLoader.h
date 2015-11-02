#ifndef INSTANCE_LOADER_H
#define INSTANCE_LOADER_H

#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>


typedef std::vector<std::vector<int> > Matrix;

struct Instance {

    int dimensionSize;
    Matrix distances;
    Matrix flows;
    double optimalSolution;
    std::vector<int> optimalPermutation;
};


class DataFileNotFoundException : public std::runtime_error
{
public:
    DataFileNotFoundException() : std::runtime_error("Could not find requested data file")  
    {

    }
};

class InstanceLoader {
    std::ifstream inputStream;
    std::ifstream solutionStream;
    Instance instance;
    void loadMatrixIntoContainer(std::vector<std::vector<int>> &);
    void loadDimensionSizeIntoInstance();
    void loadDistancesIntoInstance();
    void loadFlowsIntoInstance();
    void loadOptimalSolution();

public:
    InstanceLoader(const std::string &, const std::string &);
    ~InstanceLoader();
    Instance load();
    static Instance loadInstanceFromFile(const std::string &, const std::string &);
};

#endif