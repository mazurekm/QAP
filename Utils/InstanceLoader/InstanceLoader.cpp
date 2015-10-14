#include <Utils/InstanceLoader/InstanceLoader.h>

InstanceLoader::InstanceLoader(const std::string & fileName) : inputStream(fileName) {
}

Instance InstanceLoader::loadInstanceFromFile(const std::string &fileName) {
    return InstanceLoader(fileName).load();
}

Instance InstanceLoader::load() {
    loadDimensionSizeIntoInstance();
    loadDistancesIntoInstance();
    loadFlowsIntoInstance();
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
}