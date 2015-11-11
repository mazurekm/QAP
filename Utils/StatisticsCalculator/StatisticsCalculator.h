#ifndef STATISTICS_CALCULATOR_H
#define STATISTICS_CALCULATOR_H

class CStatisticsCalculator {
    double quantitySum, quantitySquareSum;
    long samples;
public:
    CStatisticsCalculator();
    void update(double);
    void reset();
    double getMean() const;
    double getStdDev() const;
    double getQuantitySum() const;
};

#endif