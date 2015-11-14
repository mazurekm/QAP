#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/Random/Random.h>
#include <Utils/InstanceLoader/InstanceLoader.h>
#include <memory>
#include <algorithm>
#include <iterator>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_random)
{
	std::unique_ptr<IStrategy> ptr( new CRandom (Matrix(10), Matrix(10)) );
	ptr->perform();
	auto res = ptr->getResult();

	int current = 0;
	int counter =  std::count_if(res.begin(), res.end(), 
		[&](int i)->bool {return ++current==i;} 
	);

	BOOST_CHECK(current != counter);
}

BOOST_AUTO_TEST_CASE(test_random_with_instance)
{
	auto input = InstanceLoader::loadInstanceFromFile("test.dat", "test.sln");
	std::unique_ptr<IStrategy> ptr( new CRandom (input.flows, input.distances ));
	double cost = input.optimalSolution;
	
	for (int i = 0; i< 10; ++i) {
		ptr->perform();
		std::cout << ptr->getCost() << std::endl;
		auto costCalculator = ptr->getCostStatsCalculator();
		std::cout << costCalculator.getMean() << " " << costCalculator.getStdDev() << std::endl;
		BOOST_CHECK(ptr->getCost() >= cost);
	}

	std::ostream_iterator<int> beginIter(std::cout, " ");
	auto res = ptr->getResult();
	std::copy(res.begin(), res.end(), beginIter);
	std::cout << ptr->getCost() << std::endl;
}