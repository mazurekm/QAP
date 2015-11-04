#ifndef LOCAL_SEARCH
#define LOCAL_SEARCH

#include <Algorithms/Strategy/Strategy.h>

class ILocalSearch : public IStrategy
{
public:
	ILocalSearch(const Matrix &flow, const Matrix &distance);
	virtual void perform();
    double getMeanSteps() const;
    double getMeanReviewedSolutions() const;
protected:
    virtual void performWithin() = 0;
	std::vector<int> initPermutation(unsigned N);
    long m_steps, m_reviewedSolutions;
};

#endif