#ifndef STEEPEST
#define STEEPEST

#include "LocalSearch.h"

class CSteepest : public ILocalSearch
{
public:
	CSteepest(const Matrix &flow, const Matrix &distance);
	void perform();
};

#endif