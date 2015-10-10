#ifndef STRATEGY
#define STRATEGY

#include<vector>

typedef std::vector<std::vector<int> > Matrix;

class IStrategy
{
public:
	IStrategy(const Matrix &flow, const Matrix &distance);
	virtual void perform(std::vector<int> &result, int &cost, double &time) = 0; 

protected:
	Matrix m_flow;
	Matrix m_distance;
};

#endif