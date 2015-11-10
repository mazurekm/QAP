#ifndef LOCAL_SEARCH
#define LOCAL_SEARCH

#include <Algorithms/Strategy/Strategy.h>
#include <vector>

class ILocalSearch : public IStrategy
{
public:
	ILocalSearch(const Matrix &flow, const Matrix &distance, bool gatherCost = false);
	virtual void perform();
    double getMeanSteps() const;
    double getMeanReviewedSolutions() const;
    
    std::vector<long> getFirstSolutionList() const;
    std::vector<long> getFinalSolutionList() const;

protected:
    virtual void performWithin() = 0;
    long m_steps, m_reviewedSolutions;
    bool m_gatherCost;

    std::vector<long> m_beginSolutions;
    std::vector<long> m_endSolutions;
};

#endif