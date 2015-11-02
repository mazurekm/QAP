#ifndef _3_OPT
#define _3_OPT

#include <Algorithms/LocalSearch/LocalSearch.h>

class C_3_Opt : public ILocalSearch {
    void performWithin();
public:
    C_3_Opt(const Matrix &flow, const Matrix &distance);
};

#endif