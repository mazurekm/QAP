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
    outFile << TestContent;
    outFile.close();
    Instance actualInstance = InstanceLoader::loadInstanceFromFile("test_instance.txt");
    std::remove("test_instance.txt");

    std::stringstream ss;
    ss << TestContent;

    assertDimensionSizesAreEqual(ss, actualInstance);
    assertDistanceMatricesAreEqual(ss, actualInstance);
    assertFlowMatricesAreEqual(ss, actualInstance);
}
