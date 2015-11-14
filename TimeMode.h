#ifndef MEASURE_TIME_MODE
#define MEASURE_TIME_MODE

#include "Mode.h"
#include <Utils/StatisticsCalculator/StatisticsCalculator.h>
#include <unordered_map>

typedef std::unordered_map<std::string, CStatisticsCalculator> StatsCalculatorMap;

class CTimeMode : public IMode
{
public:
	CTimeMode();
protected:
	void perform();
    void setStatsCalculators(const std::shared_ptr<IStrategy> &);
    StatsCalculatorMap statsCalculatorMap;
};

#endif