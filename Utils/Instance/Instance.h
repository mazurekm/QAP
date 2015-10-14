#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>

class Instance {
    
public:
    int dimensionSize;
    std::vector<std::vector<int>> distances;
    std::vector<std::vector<int>> flows;
};

#endif