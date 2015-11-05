#ifndef MEASURE_ITERATION_COST_MODE
#define MEASURE_ITERATION_COST_MODE

#include "Mode.h"

class CIterationCostMode : public IMode
{
public:
	CIterationCostMode();
protected:
	void perform();
};

#endif