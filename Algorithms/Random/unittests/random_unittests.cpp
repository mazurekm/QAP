#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <Algorithms/Random/Random.h>
#include <memory>
#include <algorithm>
#include <iterator>

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
	BOOST_CHECK_EQUAL(-1, ptr->getCost());
}