#include "ModeFactory.h"
#include "MeasureTimeMode.h"
#include "MeasureIterationCostMode.h"
#include "StartEndCostMode.h"

IMode *CModeFactory::create(const std::string &name)
{
	if("MeasureTimeMode" == name)
	{
		return new CMeasureTimeMode();
	}
	else if("MeasureIterationCostMode" == name)
	{
		return new CMeasureIterationCostMode();
	}
	else if("StartEndCostMode")
	{
		return new CStartEndCostMode();
	}

	throw std::runtime_error("Incorrect mode");
}