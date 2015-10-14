#ifndef INSTANCE_LOADER_H
#define INSTANCE_LOADER_H

#include <string>
#include <fstream>
#include <Utils/Instance/Instance.h>

class InstanceLoader {
    std::ifstream inputStream;
    Instance instance;
    void loadMatrixIntoContainer(std::vector<std::vector<int>> &);
    void loadDimensionSizeIntoInstance();
    void loadDistancesIntoInstance();
    void loadFlowsIntoInstance();

public:
    InstanceLoader(const std::string &);
    ~InstanceLoader();
    Instance load();
    static Instance loadInstanceFromFile(const std::string &);
};

#endif