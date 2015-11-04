#include "_3_Opt.h"
#include <iostream>

C_3_Opt::C_3_Opt(const Matrix &flow, const Matrix &distance) :
    ILocalSearch(flow, distance)
{
}

void C_3_Opt::performWithin() {
    computeCost();
    long initialCost = m_cost;
    std::vector<std::pair<int, int>> bestSwapIdxPairs;
    do {
        auto idxPermutation = initPermutation(m_result.size());
        minimalCostWithinIteration = m_cost;
        bestSwapIdxPairs.clear();

        setFirstAndSecondAsSwappedPair(idxPermutation);
        updateBestSwapCollectionIfNecessary(initialCost, bestSwapIdxPairs);

        setFirstAndThirdAsSwappedPair(idxPermutation);
        updateBestSwapCollectionIfNecessary(initialCost, bestSwapIdxPairs);

        setSecondAndThirdAsSwappedPair(idxPermutation);
        updateBestSwapCollectionIfNecessary(initialCost, bestSwapIdxPairs);

        setFirstAndSecondThenSecondAndThirdAsSwappedPairs(idxPermutation);
        updateBestSwapCollectionIfNecessary(initialCost, bestSwapIdxPairs);

        setSecondAndThirdThenFirstAndSecondAsSwappedPairs(idxPermutation);
        updateBestSwapCollectionIfNecessary(initialCost, bestSwapIdxPairs);

        for (auto & swapIdxsPair : bestSwapIdxPairs) {
            std::swap(m_result[swapIdxsPair.first], m_result[swapIdxsPair.second]);
        }
        m_cost = minimalCostWithinIteration;
        initialCost = m_cost;
    } while (false == bestSwapIdxPairs.empty());
}

void C_3_Opt::updateBestSwapCollectionIfNecessary(const long & initialCost,
                                                  std::vector<std::pair<int, int>> & bestSwapIdxPairs) {
    computeCost(swapIdxsPairs.at(0));
    if (2 == swapIdxsPairs.size()) {
       auto & firstSwapIdxsPair = swapIdxsPairs.at(0);
       std::swap(m_result[firstSwapIdxsPair.first], m_result[firstSwapIdxsPair.second]);
       computeCost(swapIdxsPairs.at(1));
       std::swap(m_result[firstSwapIdxsPair.first], m_result[firstSwapIdxsPair.second]);
    }
    if (m_cost < minimalCostWithinIteration) {
        bestSwapIdxPairs = swapIdxsPairs;
        minimalCostWithinIteration = m_cost;
    }
    m_cost = initialCost;
}

void C_3_Opt::setFirstAndSecondAsSwappedPair(std::vector<int> & idxPermutation) {
    swapIdxsPairs.clear();
    swapIdxsPairs.push_back(std::pair<int, int>(idxPermutation[0], idxPermutation[1]));
}

void C_3_Opt::setFirstAndThirdAsSwappedPair(std::vector<int> & idxPermutation) {
    swapIdxsPairs.clear();
    swapIdxsPairs.push_back(std::pair<int, int>(idxPermutation[0], idxPermutation[2]));
}

void C_3_Opt::setSecondAndThirdAsSwappedPair(std::vector<int> & idxPermutation) {
    swapIdxsPairs.clear();
    swapIdxsPairs.push_back(std::pair<int, int>(idxPermutation[1], idxPermutation[2]));
}

void C_3_Opt::setFirstAndSecondThenSecondAndThirdAsSwappedPairs(std::vector<int> & idxPermutation) {
    swapIdxsPairs.clear();
    swapIdxsPairs.push_back(std::pair<int, int>(idxPermutation[0], idxPermutation[1]));
    swapIdxsPairs.push_back(std::pair<int, int>(idxPermutation[1], idxPermutation[2]));
}

void C_3_Opt::setSecondAndThirdThenFirstAndSecondAsSwappedPairs(std::vector<int> & idxPermutation) {
    swapIdxsPairs.clear();
    swapIdxsPairs.push_back(std::pair<int, int>(idxPermutation[1], idxPermutation[2]));
    swapIdxsPairs.push_back(std::pair<int, int>(idxPermutation[0], idxPermutation[1]));
}