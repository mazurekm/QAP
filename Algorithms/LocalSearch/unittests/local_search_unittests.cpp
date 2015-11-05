#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/LocalSearch/Greedy.h>
#include <Algorithms/LocalSearch/Steepest.h>
#include <Algorithms/LocalSearch/_3_Opt.h>
#include <Utils/InstanceLoader/InstanceLoader.h>

#include <algorithm>
#include <iterator>
#include <memory>
#include <iostream>

class Mock_3_Opt : public C_3_Opt {
public:
	Mock_3_Opt(const Matrix &, const Matrix &);
	void computeCostWrapper();
};

Mock_3_Opt::Mock_3_Opt(const Matrix &flow, const Matrix &distance) :
    C_3_Opt(flow, distance, false)
{
}

void Mock_3_Opt::computeCostWrapper() {
    computeCost();
}

BOOST_AUTO_TEST_CASE(test_greedy_with_instance)
{
	auto input = InstanceLoader::loadInstanceFromFile("test.dat", "test.sln");
	std::unique_ptr<IStrategy> ptr( new CGreedy (input.flows, input.distances ));
	double cost = input.optimalSolution;
	
	for (int i = 0; i < 1000; ++i) {
		ptr->perform();
		BOOST_CHECK(ptr->getCost() >= cost);
	}

	std::ostream_iterator<int> beginIter(std::cout, " ");
	auto res = ptr->getResult();
	std::copy(res.begin(), res.end(), beginIter);
	std::cout << ptr->getCost() << std::endl;
}

BOOST_AUTO_TEST_CASE(test_steepest_with_instance)
{
	auto input = InstanceLoader::loadInstanceFromFile("test.dat", "test.sln");
	std::unique_ptr<IStrategy> ptr( new CSteepest (input.flows, input.distances ));
	double cost = input.optimalSolution;
	
	for (int i = 0; i < 1000; ++i) {
		ptr->perform();
		BOOST_CHECK(ptr->getCost() >= cost);
	}
	
	std::ostream_iterator<int> beginIter(std::cout, " ");
	auto res = ptr->getResult();
	std::copy(res.begin(), res.end(), beginIter);
	std::cout << ptr->getCost() << std::endl;
}

BOOST_AUTO_TEST_CASE(test_3_opt_with_instance)
{
	auto input = InstanceLoader::loadInstanceFromFile("test.dat", "test.sln");
	std::unique_ptr<Mock_3_Opt> ptr( new Mock_3_Opt (input.flows, input.distances ));
	double cost = input.optimalSolution;
	
	for (int i = 0; i < 1000; ++i) {
		ptr->perform();
		long theCost = ptr->getCost();
		ptr->computeCostWrapper();
		BOOST_CHECK_EQUAL(ptr->getCost(), theCost);
		BOOST_CHECK(ptr->getCost() >= cost);
	}
	
	std::ostream_iterator<int> beginIter(std::cout, " ");
	auto res = ptr->getResult();
	std::copy(res.begin(), res.end(), beginIter);
	std::cout << ptr->getCost() << std::endl;
}