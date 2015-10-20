#include "LocalSearch.h"
#include <algorithm>
#include <iterator>
#include <random>

ILocalSearch::ILocalSearch(const Matrix &flow, const Matrix &distance) : 
	IStrategy(flow, distance)
{

}

std::vector<int> ILocalSearch::initPermutation(unsigned N)
{
	std::vector<int> result;
	int current = 0;
	std::generate_n(
			std::back_inserter(result), 
			N, 
			[&]()->int{ return ++current; }
	);

	std::random_device rd;
    std::mt19937 randomGen(rd());
	std::shuffle(m_result.begin(), m_result.end(), randomGen);

	return result;
}