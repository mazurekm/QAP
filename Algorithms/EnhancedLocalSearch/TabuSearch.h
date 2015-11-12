#ifndef TABU_SEARCH
#define TABU_SEARCH

#include <Algorithms/EnhancedLocalSearch/EnhancedLocalSearch.h>

class CTabuSearch : public IEnhancedLocalSearch {
    
public:
    CTabuSearch(const Matrix &, const Matrix &);
};

#endif