#ifndef START_END_COST_MODE
#define START_END_COST_MODE

#include "Mode.h"

class CStartEndCostMode : public IMode
{
public:
	CStartEndCostMode();
protected:
	void perform();
};

#endif