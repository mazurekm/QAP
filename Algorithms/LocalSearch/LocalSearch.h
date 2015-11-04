#ifndef LOCAL_SEARCH
#define LOCAL_SEARCH

#include <Algorithms/Strategy/Strategy.h>
#include <vector>

class ILocalSearch : public IStrategy
{
public:
	ILocalSearch(const Matrix &flow, const Matrix &distance);
	virtual void perform();
    double getMeanSteps() const;
    double getMeanReviewedSolutions() const;
    std::vector<long> m_beginSolutions;
    std::vector<long> m_endSolutions;
protected:
    virtual void performWithin() = 0;
	std::vector<int> initPermutation(unsigned N);
    long m_steps, m_reviewedSolutions;
};

#endif