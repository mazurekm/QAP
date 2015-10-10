#include "Strategy.h"

IStrategy::IStrategy(const Matrix &flow, const Matrix &distance):
	m_flow(flow),
	m_distance(distance)
{

}