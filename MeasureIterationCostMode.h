#ifndef MEASURE_ITERATION_COST_MODE
#define MEASURE_ITERATION_COST_MODE

#include "Mode.h"

class CMeasureIterationCostMode : public IMode
{
public:
	CMeasureIterationCostMode();
protected:
	void perform();
};

#endif