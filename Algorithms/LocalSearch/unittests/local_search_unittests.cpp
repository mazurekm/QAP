#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/LocalSearch/Greedy.h>
#include <Algorithms/LocalSearch/Steepest.h>
#include <Utils/InstanceLoader/InstanceLoader.h>

#include <algorithm>
#include <iterator>
#include <memory>
#include <iostream>


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