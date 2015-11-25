#include "TabuSearch.h"
#include <iostream>
#include <algorithm>
#include <climits>
#include <iterator>

CTabuSearch::CTabuSearch(const Matrix &flow, const Matrix &distance, const CTabuListController & tabuListController,
                         const std::string & candidateListMainQuantity, const double ratioOfReviewedSolutionsForCandidatesList,
                         const double ratioOfCandidates, bool gatherCost) :
        IEnhancedLocalSearch(flow, distance),
        m_tabuListController(tabuListController)
{
    m_solutionsToReview = unsigned((m_distance.size() * (m_distance.size() - 1)) / 2) * ratioOfReviewedSolutionsForCandidatesList;
    if ("SizeOfInstance" == candidateListMainQuantity) {
        m_targetSizeOfCandidatesList = ratioOfCandidates * m_distance.size();
    }
    else if ("NumberOfReviewedSolutions" == candidateListMainQuantity) {
        m_targetSizeOfCandidatesList = ratioOfCandidates * m_solutionsToReview;
    }
    m_frequencyMatrix.resize(m_distance.size());
    for (auto & row : m_frequencyMatrix) {
        row.resize(m_frequencyMatrix.size(), 0);
    }
}

void CTabuSearch::performWithin() {
    size_t stepsWithoutImprovement = 0;
    m_candidateCostThreshold = 0;
    m_tabuListController.reset();
    updateResultAndCost();
    setBestCandidate();
    for (auto & row : m_frequencyMatrix) {
        std::fill(row.begin(), row.end(), 0);
    }

    while (stepsWithoutImprovement < 100) {
        constructCandidateListIfCostIncreasedTooMuch();
        setBestCandidate();
        if (InvalidIndex == m_bestCandidate.move.first) {
            break;
        }

        m_cost = m_bestCandidate.cost;

        std::swap(m_result[m_bestCandidate.move.first], m_result[m_bestCandidate.move.second]);
        m_tabuListController.updateTabuOnStep(m_bestCandidate.move);
        if (m_cost < m_bestCostWithinIteration) {
            updateResultAndCost();
            stepsWithoutImprovement = 0;
        }
        else {
            ++m_frequencyMatrix.at(m_bestCandidate.move.first).at(m_bestCandidate.move.second);
            ++stepsWithoutImprovement;
        }
    }
    m_result = m_bestResultWithinIteration;
    m_cost = m_bestCostWithinIteration;
}

void CTabuSearch::setBestCandidate() {
    m_bestCandidate = {std::pair<int, int>(InvalidIndex, InvalidIndex), LONG_MAX};
    for (auto & candidate : m_candidateList) {
        candidate.cost = computeMoveCost(candidate.move);
        if (m_tabuListController.isMoveTabu(candidate.move)
            && false == m_tabuListController.isMoveSatisfyingAspirationCriteria(m_cost, candidate.cost)) {
            continue;
        }
        if (m_bestCandidate.cost > candidate.cost) {
            m_bestCandidate = candidate;
        }
    }
}

void CTabuSearch::constructCandidateListIfCostIncreasedTooMuch() {
    if (m_bestCandidate.cost <= m_candidateCostThreshold) {
        return;
    }
    size_t solutionsReviewed = 0;
    m_candidateList.clear();
    for (size_t i = 0; i<m_result.size(); ++i) {
        for (size_t j = i+1; j<m_result.size(); ++j) {
            if (solutionsReviewed == m_solutionsToReview) {
                return;
            }
            std::pair<int, int> move(i, j);
            insertMoveAsCandidateIfFitEnough(move);
            ++solutionsReviewed;
        }
    }
    setCandidateMinCostAsThreshold();
}

void CTabuSearch::insertMoveAsCandidateIfFitEnough(const std::pair<int, int> & move) {
    long cost = computeMoveCost(move) + m_frequencyMatrix.at(move.first).at(move.second);
    if (m_candidateList.size() < m_targetSizeOfCandidatesList) {
        Candidate candidate = {move, cost};
        m_candidateList.push_back(candidate);
        std::push_heap(m_candidateList.begin(), m_candidateList.end());
    } 
    else if (cost < m_candidateList.front().cost) {
        Candidate candidate = {move, cost};
        std::pop_heap(m_candidateList.begin(), m_candidateList.end());
        m_candidateList.back() = candidate;
        std::push_heap(m_candidateList.begin(), m_candidateList.end());
    }
}

long CTabuSearch::computeMoveCost(const std::pair<int, int> & move) {
    long initialCost = m_cost;
    computeCost(move);
    long moveCost = m_cost;
    m_cost = initialCost;
    return moveCost;
}

void CTabuSearch::setCandidateMinCostAsThreshold() {
    long maxCost = 0;
    std::for_each(m_candidateList.begin(), m_candidateList.end(), [&](const Candidate cand) {
        if (maxCost < cand.cost) {
            maxCost = cand.cost;
        }
    });
    m_candidateCostThreshold = maxCost;
}

void CTabuSearch::updateResultAndCost() {
    m_bestResultWithinIteration = m_result;
    m_bestCostWithinIteration = m_cost;
}