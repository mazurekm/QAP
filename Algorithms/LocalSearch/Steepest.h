#ifndef STEEPEST
#define STEEPEST

#include "LocalSearch.h"

class CSteepest : public ILocalSearch
{
    void performWithin();
public:
	CSteepest(const Matrix &flow, const Matrix &distance, bool gatherCost = false);
};

#endif