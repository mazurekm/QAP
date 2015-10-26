#ifndef STRATEGY
#define STRATEGY

#include<vector>

typedef std::vector<std::vector<int> > Matrix;

class IStrategy
{
public:
	IStrategy(const Matrix &flow, const Matrix &distance);
	
	virtual void perform() = 0; 

	std::vector<int> getResult() const;
	double getCost() const;

protected:
	virtual void computeCost();
	virtual void computeCost(std::pair<int, int> &);
	void substractFromCostAllArcsBoundWithPair(std::pair<int, int> &);
	void addToCostAllArcsBoundWithPair(std::pair<int, int> &);

	Matrix m_flow;
	Matrix m_distance;

	std::vector<int> m_result;
	long m_cost;
};

#endif