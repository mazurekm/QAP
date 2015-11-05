#ifndef MEASURE_TIME_MODE
#define MEASURE_TIME_MODE

#include "Mode.h"

class CTimeMode : public IMode
{
public:
	CTimeMode();
protected:
	void perform();
};

#endif