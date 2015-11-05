#include "ModeFactory.h"
#include "TimeMode.h"
#include "IterationCostMode.h"
#include "StartEndCostMode.h"

IMode *CModeFactory::create(const std::string &name)
{
	if("TimeMode" == name)
	{
		return new CTimeMode();
	}
	else if("IterationCostMode" == name)
	{
		return new CIterationCostMode();
	}
	else if("StartEndCostMode")
	{
		return new CStartEndCostMode();
	}

	throw std::runtime_error("Incorrect mode");
}