#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/Strategy/Strategy.h>
#include <vector>
#include <iostream>

class MockStrategy : public IStrategy {
    std::pair<int, int> swapedIndxs;
public:
    MockStrategy(const Matrix & flow, const Matrix & distance);
    void perform();
    void setPair(int, int);
    static int testId;
};

int MockStrategy::testId;

MockStrategy::MockStrategy(const Matrix & flow, const Matrix & distance) : IStrategy(flow, distance) {
    if (0 == testId) {
        m_result = {0, 1}; 
    }
    else if (1 == testId) {
        m_result = {2, 3, 1, 0, 4, 5};
    }
    computeCost();
}

void MockStrategy::perform() {
    computeCost(swapedIndxs);
}

void MockStrategy::setPair(int a, int b) {
    swapedIndxs = std::make_pair(a, b);
}

BOOST_AUTO_TEST_CASE(test_computeCost_simpleCase) {
    Matrix flow = {
        {0, 2},
        {2, 0}
    };
    Matrix distance = {
        {0, 3},
        {3, 0}
    };
    MockStrategy::testId = 0;
    std::unique_ptr<MockStrategy> mockStrategyPtr(new MockStrategy (flow, distance));
    mockStrategyPtr->setPair(0, 1);
    BOOST_CHECK_EQUAL(6, mockStrategyPtr->getCost());
    int expectedCost = 6;

    mockStrategyPtr->perform();

    BOOST_CHECK_EQUAL(expectedCost, mockStrategyPtr->getCost());
}

BOOST_AUTO_TEST_CASE(test_computeCost) {
    Matrix flow = {
        {0, 71, 11, 29, 82, 82},
        {71, 0, 74, 30, 89, 76},
        {11, 74, 0, 1, 50, 4},
        {29, 30, 1, 0, 1, 15},
        {82, 89, 50, 1, 0, 21},
        {82, 76, 4, 15, 21, 0}
    };
    Matrix distance = {
        {0, 21, 95, 82, 56, 41},
        {21, 0, 63, 6, 44, 40},
        {95, 63, 0, 35, 9, 1},
        {82, 6, 35, 0, 26, 91},
        {56, 44, 9, 26, 0, 69},
        {41, 40, 1, 91, 69, 0}
    };
    MockStrategy::testId = 1;
    std::unique_ptr<MockStrategy> mockStrategyPtr(new MockStrategy (flow, distance));
    mockStrategyPtr->setPair(1, 4);
    int expectedCost = 28267;

    mockStrategyPtr->perform();

    BOOST_CHECK_EQUAL(expectedCost, mockStrategyPtr->getCost());
}