#ifndef METROPOLIS
#define METROPOLIS

#include <Algorithms/EnhancedLocalSearch/EnhancedLocalSearch.h>

class CMetropolis : public IEnhancedLocalSearch
{
public:
	CMetropolis(const Matrix &flow, const Matrix &distance);
	void perform();
	void setParameters(double temperature = 1200, double alfa = 0.95);

	double getAdaptiveTemp() const;
	double getTemperature() const;

private:
	double m_temperature;
	double m_adaptiveTemp;

	double m_alfa;
};


#endif
