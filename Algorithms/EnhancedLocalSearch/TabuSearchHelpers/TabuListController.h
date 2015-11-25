#ifndef TABU_LIST_CONTROLLER
#define TABU_LIST_CONTROLLER

#include <queue>
#include <vector>

typedef std::vector<std::vector<int>> Matrix;
const int InvalidIndex = -1;

class CTabuListController {
    unsigned m_instanceSize, m_aspirationThreshold;
    unsigned m_tabuPeriod;
    Matrix m_tabuMatrix;
    std::queue<std::pair<int, int>> m_tabuQueue;

    void addUsedMoveToTabu(const std::pair<int, int> &);
    void removeOldestMoveFromTabu();
public:
    CTabuListController(const unsigned, const double, const unsigned);
    void reset();
    bool isMoveTabu(const std::pair<int, int> &);
    void updateTabuOnStep(const std::pair<int, int> &);
    bool isMoveSatisfyingAspirationCriteria(const unsigned, const unsigned);
};

#endif