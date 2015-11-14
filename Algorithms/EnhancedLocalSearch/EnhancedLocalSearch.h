#ifndef ENHANCED_LOCAL_SEARCH
#define ENHANCED_LOCAL_SEARCH

#include <Algorithms/Strategy/Strategy.h>

class IEnhancedLocalSearch : public IStrategy {
    
public:
    IEnhancedLocalSearch(const Matrix &flow, const Matrix &distance);
    virtual void perform();
};

#endif