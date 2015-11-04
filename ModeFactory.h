#ifndef MODE_FACTORY
#define MODE_FACTORY

#include <string>

#include "Mode.h"

class CModeFactory
{
public:
	IMode *create(const std::string &name);
};

#endif