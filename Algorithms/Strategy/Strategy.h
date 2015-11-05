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
	long getCost() const;
	double getMeanCost() const;
	double getStdDevCost() const;

protected:
	virtual void computeCost();
	virtual void computeCost(const std::pair<int, int> &);
	void substractFromCostAllArcsBoundWithPair(const std::pair<int, int> &);
	void addToCostAllArcsBoundWithPair(const std::pair<int, int> &);
	void restorePreviousResultIfItWasBetter();
	void savePreviousResult();
	void updateMeasureParams();

	Matrix m_flow;
	Matrix m_distance;

	std::vector<int> m_result, m_prevResult;
	long m_cost, m_prevCost, m_performNumber;
	long m_costSum;
	long double m_squareCostSum;
};

#endif