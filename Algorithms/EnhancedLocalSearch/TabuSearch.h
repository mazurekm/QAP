#ifndef TABU_SEARCH
#define TABU_SEARCH

#include <Algorithms/EnhancedLocalSearch/EnhancedLocalSearch.h>
#include <string>

class CTabuSearch : public IEnhancedLocalSearch {

    std::string m_candidateListMainQuantity;
    unsigned m_reviewedSolutionsForCandidatesList;
    double m_ratioOfCandidates, m_ratioOfCandidatesUsedToCalculateMean, m_ratioOfTabuListLengthToSizeOfInstance;
    unsigned m_aspirationThreshold;
    
public:
    CTabuSearch(const Matrix &, const Matrix &, const std::string &,
                const unsigned, const double, const double, const double, unsigned);
};

#endif