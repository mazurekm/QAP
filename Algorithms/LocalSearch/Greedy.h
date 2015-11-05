#ifndef GREEDY
#define GREEDY

#include "LocalSearch.h"

class CGreedy : public ILocalSearch
{
    void performWithin();
public:
	CGreedy(const Matrix &flow, const Matrix &distance, bool gatherCost = false);
};

#endif