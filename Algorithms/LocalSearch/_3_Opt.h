#ifndef _3_OPT
#define _3_OPT

#include <Algorithms/LocalSearch/LocalSearch.h>

const int OptLength = 3;

class C_3_Opt : public ILocalSearch {
    long minimalCostWithinIteration;
    std::vector<std::pair<int, int>> swapIdxsPairs;
    void updateBestSwapCollectionIfNecessary(const long &, std::vector<std::pair<int, int>> &);
    void setFirstAndSecondAsSwappedPair(std::vector<int> &);
    void setFirstAndThirdAsSwappedPair(std::vector<int> &);
    void setSecondAndThirdAsSwappedPair(std::vector<int> &);
    void setFirstAndSecondThenSecondAndThirdAsSwappedPairs(std::vector<int> &);
    void setSecondAndThirdThenFirstAndSecondAsSwappedPairs(std::vector<int> &);
protected:
    void performWithin();
public:
    C_3_Opt(const Matrix &flow, const Matrix &distance);
};

#endif