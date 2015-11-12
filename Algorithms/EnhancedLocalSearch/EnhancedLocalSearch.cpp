#include "EnhancedLocalSearch.h"

IEnhancedLocalSearch::IEnhancedLocalSearch(const Matrix &flow, const Matrix &distance) :
    IStrategy(flow, distance) {

}

void IEnhancedLocalSearch::perform() {
}