#ifndef RANDOM
#define RANDOM

#include <Algorithms/Strategy/Strategy.h>

class CRandom : public IStrategy
{
public:
	CRandom(const Matrix &flow, const Matrix &distance);
	void perform(std::vector<int> &result, int &cost, double &time); 
};

#endif
