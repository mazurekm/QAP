#ifndef RANDOM
#define RANDOM

#include <Algorithms/Strategy/Strategy.h>

class CRandom : public IStrategy
{
    void permute();
public:
	CRandom(const Matrix &flow, const Matrix &distance);
	void perform(); 
};

#endif
