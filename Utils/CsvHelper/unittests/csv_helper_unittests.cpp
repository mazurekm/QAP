#define BOOST_TEST_MODULE Utils

#include <boost/test/unit_test.hpp>
#include <Utils/CsvHelper/CsvHelper.h>

BOOST_AUTO_TEST_CASE(csv_helper_test)
{
	std::string str = "a;b;1\n"
					  "c;d;2\n"
					  "d;e;3\n";
	CCsvHelper csv;
	csv.add('a','b',1);
	csv.add('c','d',2);
	csv.add('d','e',3);

	BOOST_CHECK_EQUAL(str, csv.getText());
	csv.toFile("output.csv");
}