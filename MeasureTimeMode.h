#ifndef MEASURE_TIME_MODE
#define MEASURE_TIME_MODE

#include "Mode.h"

class CMeasureTimeMode : public IMode
{
public:
	CMeasureTimeMode();
protected:
	void perform();
};

#endif