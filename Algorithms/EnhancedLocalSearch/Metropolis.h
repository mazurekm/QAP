#ifndef METROPOLIS
#define METROPOLIS

#include <Algorithms/EnhancedLocalSearch/EnhancedLocalSearch.h>

class CMetropolis : public IEnhancedLocalSearch
{
public:
	CMetropolis(const Matrix &flow, const Matrix &distance);
	void perform();
	void setParameters(double temperature, double alfa);

private:
	double m_temperature;
	double m_alfa;
};


#endif