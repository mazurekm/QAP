#define BOOST_TEST_MODULE Utils

#include <boost/test/unit_test.hpp>
#include <Utils/ConfManager/ConfManager.h>

#include <iostream>
#include <unordered_set>

BOOST_AUTO_TEST_CASE(conf_test)
{
	CConfManager mgr("Tests/test.json");
	auto files = mgr.getInputData();
	auto sts = mgr.getStrategies();

	BOOST_CHECK_EQUAL(files.size(), 3);
	BOOST_CHECK_EQUAL(sts.size(), 3);
	BOOST_CHECK_EQUAL(mgr.getTimeLimit(), 10.0);
}