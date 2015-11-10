#ifndef METROPOLIS
#define METROPOLIS

#include <Algorithms/Strategy/Strategy.h>

class CMetropolis : public IStrategy
{
public:
	CMetropolis(const Matrix &flow, const Matrix &distance);
	void perfom();
	void setParameters(double temperature, double alfa);

private:
	double m_temperature;
	double m_alfa;
};


#endif