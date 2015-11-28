#ifndef TABU_SEARCH
#define TABU_SEARCH

#include <Algorithms/EnhancedLocalSearch/EnhancedLocalSearch.h>
#include <Algorithms/EnhancedLocalSearch/TabuSearchHelpers/TabuListController.h>
#include <string>
#include <queue>

struct Candidate {
    std::pair<int, int> move;
    long cost;
    bool operator <(const Candidate & other) {return this->cost < other.cost;}
};

class CTabuSearch : public IEnhancedLocalSearch {

    Candidate m_bestCandidate;
    CTabuListController m_tabuListController;
    unsigned m_candidateCostThreshold;

    std::vector<int> m_bestResultWithinIteration;
    long m_bestCostWithinIteration;
    Matrix m_frequencyMatrix;

    void insertMoveAsCandidateIfFitEnough(const std::pair<int, int> &);
    long computeMoveCost(const std::pair<int, int> &);
    void performWithin();
    void setCandidateMaxCostAsThreshold();
    void updateResultAndCost(); 
    
public:
    CTabuSearch(const Matrix &, const Matrix &, const CTabuListController &,
                const std::string &, const double, const double, bool);
protected:
    unsigned m_solutionsToReview;
    unsigned m_targetSizeOfCandidatesList;
    std::vector<Candidate> m_candidateList;
    void constructCandidateListIfCostIncreasedTooMuch();
    void setBestCandidate();
};

#endif