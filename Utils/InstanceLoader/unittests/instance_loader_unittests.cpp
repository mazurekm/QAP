#define BOOST_TEST_MODULE Utils

#include <boost/test/unit_test.hpp>
#include <Utils/InstanceLoader/InstanceLoader.h>
#include <fstream>
#include <sstream>
#include <iostream>

const char * TestContent = "3\n"
                           "\n"
                           "1 2 3\n"
                           "2 1 3\n"
                           "3 2 1\n"
                           "\n"
                           "4 5 6\n"
                           "5 4 6\n"
                           "6 4 5\n";

const char *solutionContent = "3 234\n"
                              "0 1 2";

void assertDimensionSizesAreEqual(std::stringstream & ss, Instance & actualInstance) {
    int buf;
    ss >> buf;
    BOOST_CHECK(buf == actualInstance.dimensionSize);
}

void assertDistanceMatricesAreEqual(std::stringstream & ss, Instance & actualInstance) {
    int expectedDistance;
    BOOST_CHECK(actualInstance.dimensionSize == (int) actualInstance.distances.size());
    for (auto iit = actualInstance.distances.begin(); iit != actualInstance.distances.end(); ++iit) {
        BOOST_CHECK(actualInstance.dimensionSize == (int) iit->size());
        for (auto jit = iit->begin(); jit != iit->end(); ++jit) {
            int actualDistance = *jit;
            ss >> expectedDistance;
            BOOST_CHECK(expectedDistance == actualDistance);
        }
    }
}

void assertFlowMatricesAreEqual(std::stringstream & ss, Instance & actualInstance) {
    int expectedFlow;
    BOOST_CHECK(actualInstance.dimensionSize == (int) actualInstance.flows.size());
    for (auto iit = actualInstance.flows.begin(); iit != actualInstance.flows.end(); ++iit) {
        BOOST_CHECK(actualInstance.dimensionSize == (int) iit->size());
        for (auto jit = iit->begin(); jit != iit->end(); ++jit) {
            int actualFlow = *jit;
            ss >> expectedFlow;
            BOOST_CHECK(expectedFlow == actualFlow);
        }
    }
}

BOOST_AUTO_TEST_CASE(test_load) {
    std::ofstream outFile("test_instance.txt", std::ofstream::out);
    std::ofstream solOutFile("solution_test_instance", std::ofstream::out);
    outFile << TestContent;
    solOutFile << solutionContent;
    outFile.close();
    solOutFile.close();
    Instance actualInstance = InstanceLoader::loadInstanceFromFile("test_instance.txt", 
                                                                   "solution_test_instance");
    std::remove("test_instance.txt");
    std::remove("solution_test_instance");

    std::stringstream ss;
    ss << TestContent;

    BOOST_CHECK_EQUAL(234, actualInstance.optimalSolution);
    BOOST_CHECK_EQUAL(3, actualInstance.optimalPermutation.size());

    assertDimensionSizesAreEqual(ss, actualInstance);
    assertFlowMatricesAreEqual(ss, actualInstance);
    assertDistanceMatricesAreEqual(ss, actualInstance);
}
