#define BOOST_TEST_MODULE Utils

#include <memory>
#include <boost/test/unit_test.hpp>
#include <Utils/StatisticsCalculator/StatisticsCalculator.h>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_mean) {
    CStatisticsCalculator statistcsCalculator; 
    double expectedMean = 4.5;

    for (int i = 0; i < 10; ++i) {
        statistcsCalculator.update(i);
    }

    BOOST_CHECK_EQUAL(expectedMean, statistcsCalculator.getMean());
}

BOOST_AUTO_TEST_CASE(test_stdDev) {
    CStatisticsCalculator statistcsCalculator; 
    double expectedStdDev = 0;
    double expectedMean = 4.5;

    for (int i = 0; i < 10; ++i) {
        statistcsCalculator.update(i);
        expectedStdDev += (i - expectedMean) * (i - expectedMean);
    }
    expectedStdDev = std::sqrt(expectedStdDev / 10);

    BOOST_CHECK_EQUAL(expectedStdDev, statistcsCalculator.getStdDev());
}