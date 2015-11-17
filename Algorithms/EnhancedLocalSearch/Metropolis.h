#ifndef METROPOLIS
#define METROPOLIS

#include <Algorithms/EnhancedLocalSearch/EnhancedLocalSearch.h>

class CMetropolis : public IEnhancedLocalSearch
{
public:
	CMetropolis(const Matrix &flow, const Matrix &distance, double temperature, double alfa);
	double getTemperature() const;

private:

	void performWithin();
	double m_temperature;
	double m_alfa;
};


#endif
