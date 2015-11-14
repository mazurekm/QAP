#ifndef METROPOLIS
#define METROPOLIS

#include <Algorithms/Strategy/Strategy.h>

class CMetropolis : public IStrategy
{
public:
	CMetropolis(const Matrix &flow, const Matrix &distance);
	void perform();
	void setParameters(double temperature, double alfa = 0.95);

	double getAdaptiveTemp() const;
	double getTemperature() const;

private:
	double m_temperature;
	double m_adaptiveTemp;

	double m_alfa;
};


#endif