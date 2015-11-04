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
    void performNormalComputeCost();
    void setPair(int, int);
    static int testId;
};

int MockStrategy::testId;

MockStrategy::MockStrategy(const Matrix & flow, const Matrix & distance) : IStrategy(flow, distance) {
    if (0 == testId) {
        m_result = {0, 1}; 
    }
    else if (1 == testId) {
        m_result = {8, 3, 5, 2, 10, 6, 11, 1, 7, 9, 0, 4};
    }
    else if (2 == testId) {
        m_result = {4, 6, 0, 9, 10, 2, 3, 1, 8, 5, 11, 7};
    }
    computeCost();
}

void MockStrategy::perform() {
    computeCost(swapedIndxs);
    std::swap(m_result[swapedIndxs.first], m_result[swapedIndxs.second]);
}

void MockStrategy::performNormalComputeCost() {
    computeCost();
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
    BOOST_CHECK_EQUAL(12, mockStrategyPtr->getCost());
    int expectedCost = 12;

    mockStrategyPtr->perform();

    BOOST_CHECK_EQUAL(expectedCost, mockStrategyPtr->getCost());
}

BOOST_AUTO_TEST_CASE(test_computeCost) {
    Matrix flow = {
        {0, 0, 0, 255, 293, 328, 331, 318, 362, 221, 314, 390},
        {0, 0, 1, 255, 293, 329, 331, 318, 363, 222, 314, 390},
        {0, 1, 0, 255, 293, 328, 330, 318, 362, 221, 313, 390},
        {255, 255, 255, 0, 93, 120, 106, 106, 113, 81, 63, 195},
        {293, 293, 293, 93, 0, 35, 42, 25, 95, 72, 75, 107},
        {328, 329, 328, 120, 35, 0, 24, 13, 82, 107, 82, 75},
        {331, 331, 330, 106, 42, 24, 0, 20, 59, 111, 60, 91},
        {318, 318, 318, 106, 25, 13, 20, 0, 78, 97, 71, 89},
        {362, 363, 362, 113, 95, 82, 59, 78, 0, 152, 50, 129},
        {221, 222, 221, 81, 72, 107, 111, 97, 152, 0, 111, 173},
        {314, 314, 313, 63, 75, 82, 60, 71, 50, 111, 0, 150},
        {390, 390, 390, 195, 107, 75, 91, 89, 129, 173, 150, 0}
    };
    Matrix distance = {
        {0, 0, 5, 1, 1, 14261, 246, 55342, 0, 1, 36, 1828},
        {1, 0, 14568, 1064, 4, 0, 58098, 6273, 2, 3, 0, 57},
        {25642, 0, 0, 0, 2, 0, 1, 0, 0, 0, 0, 0},
        {27, 0, 62, 0, 0, 1, 0, 2491, 0, 0, 490, 0},
        {0, 57, 0, 0, 0, 0, 456, 9591, 0, 0, 1036, 0},
        {0, 3797, 7, 0, 0, 0, 9, 0, 41986, 19780, 5, 0},
        {948, 14543, 1, 93, 0, 5, 0, 3720, 0, 2, 39, 759},
        {0, 0, 0, 8, 0, 2, 3516, 0, 0, 2106, 0, 20364},
        {2911, 10710, 9, 30, 5399, 0, 0, 0, 0, 867, 0, 0},
        {0, 3, 47029, 264, 4880, 1, 5417, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 12262, 2791, 0, 0, 5, 7632, 0, 0},
        {0, 36146, 0, 0, 525, 49, 1, 19, 0, 0, 35539, 0}
    };
    MockStrategy::testId = 1;
    std::unique_ptr<MockStrategy> mockStrategyPtr(new MockStrategy (flow, distance));
    long expectedCost = 39464925;

    BOOST_CHECK_EQUAL(expectedCost, mockStrategyPtr->getCost());

    mockStrategyPtr->setPair(1, 4);
    expectedCost = 52790216;

    mockStrategyPtr->perform();

    BOOST_CHECK_EQUAL(expectedCost, mockStrategyPtr->getCost());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 11);

    for (int i = 0; i < (2 << 15); ++i) {
        std::pair<int, int>swapIndxs = {dis(rd), dis(rd)};
        mockStrategyPtr->setPair(swapIndxs.first, swapIndxs.second);
        mockStrategyPtr->perform();
        expectedCost = mockStrategyPtr->getCost();

        mockStrategyPtr->performNormalComputeCost();

        BOOST_CHECK_EQUAL(expectedCost, mockStrategyPtr->getCost());
    }
}

BOOST_AUTO_TEST_CASE(test_computeCost2) {
    Matrix flow = {
        {0, 90, 10, 23, 43, 88, 0, 0, 0, 0, 0, 0},
        {90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {10, 0, 0, 0, 0, 0, 26, 16, 0, 0, 0, 0},
        {23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {43, 0, 0, 0, 0, 0, 0, 0, 1, 96, 29, 37},
        {88, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 96, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 29, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 37, 0, 0, 0, 0, 0, 0, 0},
    };

    Matrix distance = {
        {0, 36, 54, 26, 59, 72, 9, 34, 79, 17, 46, 95},
        {36, 0, 73, 35, 90, 58, 30, 78, 35, 44, 79, 36},
        {54, 73, 0, 21, 10, 97, 58, 66, 69, 61, 54, 63},
        {26, 35, 21, 0, 93, 12, 46, 40, 37, 48, 68, 85},
        {59, 90, 10, 93, 0, 64, 5, 29, 76, 16, 5, 76},
        {72, 58, 97, 12, 64, 0, 96, 55, 38, 54, 0, 34},
        {9, 30, 58, 46, 5, 96, 0, 83, 35, 11, 56, 37},
        {34, 78, 66, 40, 29, 55, 83, 0, 44, 12, 15, 80},
        {79, 35, 69, 37, 76, 38, 35, 44, 0, 64, 39, 33},
        {17, 44, 61, 48, 16, 54, 11, 12, 64, 0, 70, 86},
        {46, 79, 54, 68, 5, 0, 56, 15, 39, 70, 0, 18},
        {95, 36, 63, 85, 76, 34, 37, 80, 33, 86, 18, 0},
    };
    MockStrategy::testId = 2;
    std::unique_ptr<MockStrategy> mockStrategyPtr(new MockStrategy (flow, distance));
    long expectedCost = 9742;

    BOOST_CHECK_EQUAL(expectedCost, mockStrategyPtr->getCost()); 
}
