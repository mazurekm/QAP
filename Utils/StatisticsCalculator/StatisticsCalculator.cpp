#include "StatisticsCalculator.h"
#include <cmath>

CStatisticsCalculator::CStatisticsCalculator() : quantitySum(0), quantitySquareSum(0), samples(0) {
}

void CStatisticsCalculator::update(double quantity) {
    quantitySum += quantity;
    quantitySquareSum += quantity * quantity;
    ++samples;
}

void CStatisticsCalculator::reset() {
    quantitySum = 0;
    quantitySquareSum = 0;
    samples = 0;
}

double CStatisticsCalculator::getMean() const {
    return quantitySum / samples;
}

double CStatisticsCalculator::getStdDev() const {
    double mean = getMean();
    return std::sqrt(quantitySquareSum/samples - mean*mean);
}

double CStatisticsCalculator::getQuantitySum() const {
    return quantitySum;
}