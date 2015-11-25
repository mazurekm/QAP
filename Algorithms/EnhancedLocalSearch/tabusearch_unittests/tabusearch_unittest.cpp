#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <Algorithms/EnhancedLocalSearch/TabuSearch.h>
#include <Algorithms/EnhancedLocalSearch/TabuSearchHelpers/TabuListController.h>
#include <Utils/InstanceLoader/InstanceLoader.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>

std::string data ="  12\n\n"

 "  0 27 85  2  1 15 11 35 11 20 21 61\n"
 " 27  0 80 58 21 76 72 44 85 94 90 51\n"
 " 85 80  0  3 48 29 90 66 41 15 83 96\n"
 "  2 58  3  0 74 45 65 40 54 83 14 71\n"
 "  1 21 48 74  0 77 36 53 37 26 87 76\n"
 " 15 76 29 45 77  0 91 13 29 11 77 32\n"
 " 11 72 90 65 36 91  0 87 67 94 79  2\n"
 " 35 44 66 40 53 13 87  0 10 99 56 70\n"
 " 11 85 41 54 37 29 67 10  0 99 60  4\n"
 " 20 94 15 83 26 11 94 99 99  0 56  2\n"
 " 21 90 83 14 87 77 79 56 60 56  0 60\n"
 " 61 51 96 71 76 32  2 70  4  2 60  0\n\n"

 "  0 21 95 82 56 41  6 25 10  4 63  6\n"
 " 21  0 44 40 75 79  0 89 35  9  1 85\n"
 " 95 44  0 84 12  0 26 91 11 35 82 26\n"
 " 82 40 84  0 69 56 86 45 91 59 18 76\n"
 " 56 75 12 69  0 39 18 57 36 61 36 21\n"
 " 41 79  0 56 39  0 71 11 29 82 82  6\n"
 "  6  0 26 86 18 71  0 71  8 77 74 30\n"
 " 25 89 91 45 57 11 71  0 89 76 76 40\n"
 " 10 35 11 91 36 29  8 89  0 93 56  1\n"
 "  4  9 35 59 61 82 77 76 93  0 50  4\n"
 " 63  1 82 18 36 82 74 76 56 50  0 36\n"
 "  6 85 26 76 21  6 30 40  1  4 36  0";

std::string sln = "  12  224416\n"
   "   8 1 6 2 11 10 3 5 9 7 12 4";

class MockTabuSearch : public CTabuSearch {
public:
    MockTabuSearch(const Matrix &, const Matrix &, const CTabuListController &,
                   const std::string &, const double, const double, bool);
    unsigned getSolutionsToReview() const {return m_solutionsToReview;}
    unsigned getSizeOfCandidatesList() const {return m_targetSizeOfCandidatesList;}
    long computeCostWrapper(const std::pair<int, int> &);
    std::vector<Candidate> constructAndGetCandidateListWrapper();
};

MockTabuSearch::MockTabuSearch(const Matrix &flow, const Matrix &distance, const CTabuListController & tabuListController,
                               const std::string & candidateListMainQuantity, const double ratioOfReviewedSolutionsForCandidatesList,
                               const double ratioOfCandidates, bool gatherCost) :
                              CTabuSearch(flow, distance, tabuListController, candidateListMainQuantity,
                                          ratioOfReviewedSolutionsForCandidatesList, ratioOfCandidates, gatherCost) {
    m_result = {5, 4, 2, 0, 11, 7, 9, 6, 1, 3, 10, 8};
    computeCost();
}

long MockTabuSearch::computeCostWrapper(const std::pair<int, int> & pair) {
    long oldCost = m_cost;
    computeCost(pair);
    long pairCost = m_cost;
    m_cost = oldCost;
    return pairCost;
}

std::vector<Candidate> MockTabuSearch::constructAndGetCandidateListWrapper() {
    setBestCandidate();
    constructCandidateListIfCostIncreasedTooMuch();
    return m_candidateList;
}

void createInstanceFiles() {
    std::string path = boost::filesystem::current_path().string();
    if (!boost::filesystem::exists(path+"/test.dat")) {
        std::ofstream dat(path+"/test.dat");
        dat << data;
        dat.close();

        std::ofstream sol(path+"/test.sln");
        sol << sln;
        sol.close();
    }
}

Instance loadInstance() {
    std::string path = boost::filesystem::current_path().string();
    return InstanceLoader::loadInstanceFromFile(path+"/test.dat", path+"/test.sln");
}

void cleanAfterTest() {
    std::string path = boost::filesystem::current_path().string();
    std::remove(std::string(path+"/test.dat").c_str());
    std::remove(std::string(path+"/test.sln").c_str());
}


BOOST_AUTO_TEST_CASE(tabusearch_constructor_test_sizeOfInstance) {
    createInstanceFiles(); 
    auto instance = loadInstance();
    double ratioOfReviewedSolutionsForCandidatesList = 0.8;
    double ratioOfCandidates = 0.5;
    CTabuListController tabuListController(instance.distances.size(),
                                          0.25, // RatioOfTabuPeriodToSizeOfInstance
                                          1 // AspirationThreshold
                                         );
    MockTabuSearch alg(instance.flows, instance.distances, tabuListController, "SizeOfInstance", 
                    ratioOfReviewedSolutionsForCandidatesList, // RatioOfReviewedSolutionsForCandidatesList
                    ratioOfCandidates, // RatioOfCandidates
                    false
                   );
    unsigned expectedSolutionsToReview = ratioOfReviewedSolutionsForCandidatesList * unsigned(12 * 11 / 2);
    BOOST_CHECK_EQUAL(expectedSolutionsToReview, alg.getSolutionsToReview());
    unsigned expectedSizeOfCandidatesList = ratioOfCandidates * 12;
    BOOST_CHECK_EQUAL(expectedSizeOfCandidatesList, alg.getSizeOfCandidatesList());
    cleanAfterTest();
}

BOOST_AUTO_TEST_CASE(tabusearch_constructor_test_numberOfReviewedSolutions) {
    createInstanceFiles(); 
    auto instance = loadInstance();
    double ratioOfReviewedSolutionsForCandidatesList = 0.6;
    double ratioOfCandidates = 0.3;
    CTabuListController tabuListController(instance.distances.size(),
                                          0.25, // RatioOfTabuPeriodToSizeOfInstance
                                          1 // AspirationThreshold
                                         );
    MockTabuSearch alg(instance.flows, instance.distances, tabuListController, "NumberOfReviewedSolutions", 
                    ratioOfReviewedSolutionsForCandidatesList, // RatioOfReviewedSolutionsForCandidatesList
                    ratioOfCandidates, // RatioOfCandidates
                    false
                   );
    unsigned expectedSolutionsToReview = ratioOfReviewedSolutionsForCandidatesList * unsigned(12 * 11 / 2);
    BOOST_CHECK_EQUAL(expectedSolutionsToReview, alg.getSolutionsToReview());
    unsigned expectedSizeOfCandidatesList = ratioOfCandidates * expectedSolutionsToReview;
    BOOST_CHECK_EQUAL(expectedSizeOfCandidatesList, alg.getSizeOfCandidatesList());
    cleanAfterTest();
}

BOOST_AUTO_TEST_CASE(tabusearch_test_insertMove) {
    createInstanceFiles();
    auto instance = loadInstance();

    CTabuListController tabuListController(instance.distances.size(),
                                          0.25, // RatioOfTabuPeriodToSizeOfInstance
                                          1 // AspirationThreshold
                                         );
    MockTabuSearch alg(instance.flows, instance.distances, tabuListController, "SizeOfInstance", 
                    0.8, // RatioOfReviewedSolutionsForCandidatesList
                    0.5, // RatioOfCandidates
                    false
                   );
    std::vector<Candidate> expectedCandidates;
    size_t iterationLimit = 0.8 * unsigned(12 * 11 / 2);
    for (size_t i = 0; i < 12; ++i) {
        for (size_t j = i+1; j < 12; ++j) {
            if (iterationLimit == 0) {
                i = 12;
                break;
            }
            std::pair<int, int> candidatePair = {i, j};
            long candidatePairCost = alg.computeCostWrapper(candidatePair);
            Candidate candidate = {candidatePair, candidatePairCost};
            expectedCandidates.push_back(candidate);
            --iterationLimit;
        }
    }
    std::sort(expectedCandidates.begin(), expectedCandidates.end());

    expectedCandidates.resize(6);

    auto actualCandidates = alg.constructAndGetCandidateListWrapper();
    std::sort(actualCandidates.begin(), actualCandidates.end());

    BOOST_CHECK_EQUAL(expectedCandidates.size(), actualCandidates.size());
    for (size_t i = 0; i < actualCandidates.size(); ++i) {
        BOOST_CHECK_EQUAL(expectedCandidates[i].cost, actualCandidates[i].cost);
        BOOST_CHECK(expectedCandidates[i].move == actualCandidates[i].move);
    }
    cleanAfterTest();
}

BOOST_AUTO_TEST_CASE(tabusearch_test)
{
    createInstanceFiles(); 

    auto instance = loadInstance();
    CTabuListController tabuListController(instance.distances.size(),
                                          0.25, // RatioOfTabuPeriodToSizeOfInstance
                                          1 // AspirationThreshold
                                         );
    CTabuSearch alg(instance.flows, instance.distances, tabuListController, "SizeOfInstance", 
                    1, // RatioOfReviewedSolutionsForCandidatesList
                    0.2, // RatioOfCandidates
                    false
                   );
    alg.perform();
    auto res = alg.getResult();
    BOOST_CHECK_EQUAL(res.size(), 12);
    BOOST_CHECK(alg.getCost()>=224416);
    std::cout << alg.getCost() << std::endl;
    std::for_each(res.begin(), res.end(), [](int el){std::cout << el << " ";});
    std::cout << std::endl;
    cleanAfterTest();
}
