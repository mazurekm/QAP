#include "TabuSearch.h"
#include <iostream>

CTabuSearch::CTabuSearch(const Matrix &flow, const Matrix &distance, const std::string & candidateListMainQuantity,
                         const unsigned reviewedSolutionsForCandidatesList, const double ratioOfCandidates,
                         const double ratioOfCandidatesUsedToCalculateMean, const double ratioOfTabuListLengthToSizeOfInstance,
                         const unsigned aspirationThreshold) :
    IEnhancedLocalSearch(flow, distance),
    m_candidateListMainQuantity(candidateListMainQuantity),
    m_reviewedSolutionsForCandidatesList(reviewedSolutionsForCandidatesList),
    m_ratioOfCandidates(ratioOfCandidates),
    m_ratioOfCandidatesUsedToCalculateMean(ratioOfCandidatesUsedToCalculateMean),
    m_ratioOfTabuListLengthToSizeOfInstance(ratioOfTabuListLengthToSizeOfInstance),
    m_aspirationThreshold(aspirationThreshold) {
    std::cout << m_candidateListMainQuantity << std::endl;
    std::cout << m_reviewedSolutionsForCandidatesList << std::endl;
    std::cout << m_ratioOfCandidates << std::endl;
    std::cout << m_ratioOfCandidatesUsedToCalculateMean << std::endl;
    std::cout << m_ratioOfTabuListLengthToSizeOfInstance << std::endl;
    std::cout << m_aspirationThreshold << std::endl;
}