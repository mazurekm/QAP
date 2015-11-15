#define BOOST_TEST_MODULE Algorithms

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <Algorithms/EnhancedLocalSearch/Metropolis.h>
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


BOOST_AUTO_TEST_CASE(metropolis_test)
{
	std::string path = boost::filesystem::current_path().string();
	std::ofstream dat(path+"/test.dat");
	dat << data;
	dat.close();

	std::ofstream sol(path+"/test.sln");
	sol << sln;
	sol.close();	

	InstanceLoader loader(path+"/test.dat", path+"/test.sln");
	auto instance = loader.load();
	CMetropolis alg(instance.flows, instance.distances);

	alg.perform();
	auto res = alg.getResult();
	BOOST_CHECK_EQUAL(res.size(), 12);
	BOOST_CHECK(alg.getCost()>=224416);
	std::cout << alg.getCost() << std::endl;
	std::for_each(res.begin(), res.end(), [](int el){std::cout << el << " ";});
	std::cout << std::endl;
	std::remove(std::string(path+"/test.dat").c_str());
	std::remove(std::string(path+"/test.sln").c_str());
}
