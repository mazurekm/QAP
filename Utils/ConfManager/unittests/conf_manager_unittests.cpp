#define BOOST_TEST_MODULE Utils

#include <boost/test/unit_test.hpp>
#include <Utils/ConfManager/ConfManager.h>

#include <iostream>
#include <unordered_set>
#include <unordered_map>

BOOST_AUTO_TEST_CASE(conf_test)
{
	CConfManager mgr("test.json");
	auto files = mgr.getInputData();
	auto sts = mgr.getStrategies();

	BOOST_CHECK_EQUAL(files.size(), 3);
	BOOST_CHECK_EQUAL(sts.size(), 3);
	BOOST_CHECK_EQUAL(mgr.getTimeLimit(), 10.0);

	BOOST_CHECK_EQUAL("ofile1", files["file1"]);
	BOOST_CHECK_EQUAL("ofile2", files["file2"]);
	BOOST_CHECK_EQUAL("ofile3", files["file3"]);
}