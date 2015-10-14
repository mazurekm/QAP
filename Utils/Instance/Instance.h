#ifndef INSTANCE_H
#define INSTANCE_H

#include <vector>

typedef std::vector<std::vector<int> > Matrix;

class Instance {
    
public:
    int dimensionSize;
    Matrix distances;
    Matrix flows;
};

#endif