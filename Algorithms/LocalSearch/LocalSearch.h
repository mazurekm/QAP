#ifndef LOCAL_SEARCH
#define LOCAL_SEARCH

#include <Algorithms/Strategy/Strategy.h>

class ILocalSearch : public IStrategy
{
public:
	ILocalSearch(const Matrix &flow, const Matrix &distance);
	virtual void perform() = 0;
protected:
	void computeCost(); 
	std::vector<int> initPermutation(unsigned N);
};

#endif