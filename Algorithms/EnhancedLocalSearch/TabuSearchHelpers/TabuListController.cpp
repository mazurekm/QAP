#include "TabuListController.h"
#include <cstddef>

CTabuListController::CTabuListController(const unsigned instanceSize,
                                       const double ratioOfTabuPeriodToSizeOfInstance,
                                       const unsigned aspirationThreshold) :
                                      m_instanceSize(instanceSize),
                                      m_aspirationThreshold(aspirationThreshold) {
    m_tabuPeriod = unsigned(ratioOfTabuPeriodToSizeOfInstance * instanceSize);
    m_tabuMatrix.resize(m_instanceSize);
    for (auto & row : m_tabuMatrix) {
        std::vector<int>(m_instanceSize, 0).swap(row);
    }
}

void CTabuListController::reset() {
    std::queue<std::pair<int, int>>().swap(m_tabuQueue);
    for (size_t i = 0; i < m_tabuPeriod; ++i) {
        std::pair<int, int> invalidPair = {InvalidIndex, InvalidIndex};
        m_tabuQueue.push(invalidPair);    
    }

    for (auto & row : m_tabuMatrix) {
        std::fill(row.begin(), row.end(), 0); 
    }
}

bool CTabuListController::isMoveTabu(const std::pair<int ,int> & move) {
    return (0 < m_tabuMatrix.at(move.first).at(move.second));
}

bool CTabuListController::isMoveSatisfyingAspirationCriteria(const unsigned currentCost,
                                                             const unsigned moveCost) {
    return moveCost < (currentCost - m_aspirationThreshold);
}

void CTabuListController::updateTabuOnStep(const std::pair<int, int> & move) {
    removeOldestMoveFromTabu();
    addUsedMoveToTabu(move);
}

void CTabuListController::addUsedMoveToTabu(const std::pair<int, int> & move) {
    ++m_tabuMatrix.at(move.first).at(move.second);
    m_tabuQueue.push(move);
}

void CTabuListController::removeOldestMoveFromTabu() {
    auto & releasedFromTabu = m_tabuQueue.front(); 
    if (releasedFromTabu.first > InvalidIndex && releasedFromTabu.second > InvalidIndex) {
        --m_tabuMatrix.at(releasedFromTabu.first).at(releasedFromTabu.second);
    }
    m_tabuQueue.pop();
}