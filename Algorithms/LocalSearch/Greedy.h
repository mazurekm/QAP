#ifndef GREEDY
#define GREEDY

#include "LocalSearch.h"

class CGreedy : public ILocalSearch
{
public:
	CGreedy(const Matrix &flow, const Matrix &distance);
	void perform();
};

#endif