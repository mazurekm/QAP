#define BOOST_TEST_MODULE Utils

#include <boost/test/unit_test.hpp>
#include <Utils/ConfManager/ConfManager.h>

#include <iostream>

BOOST_AUTO_TEST_CASE(conf_test)
{
	CConfManager mgr("Tests/test.json");
	auto root = mgr.getRoot();
	BOOST_CHECK_EQUAL(root["aaa"].asString(), "bbb");
	BOOST_CHECK_EQUAL(root["ccc"].asInt(), 4);
}