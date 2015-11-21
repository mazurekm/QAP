#ifndef METROPOLIS
#define METROPOLIS

#include <Algorithms/EnhancedLocalSearch/EnhancedLocalSearch.h>

class CMetropolis : public IEnhancedLocalSearch
{
public:
	CMetropolis(const Matrix &flow, const Matrix &distance, unsigned samples, double alfa);
	double getTemperature() const;

private:

	int getRandomInt(int lhs, int rhs);
	double getRandomReal(double lhs, double rhs);
	void computeInitTemp();

	void performWithin();
	double m_temperature;
	double m_alfa;
	unsigned m_samplesNum;
};


#endif
