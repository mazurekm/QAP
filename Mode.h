#ifndef MODE
#define MODE

#include <memory>
#include <map>

#include <Utils/ConfManager/ConfManager.h>
#include <Utils/InstanceLoader/InstanceLoader.h>
#include <Utils/SmartStopwatch/SmartStopwatch.h>
#include <Utils/CsvHelper/CsvHelper.h>
#include <AlgorithmFactory.h>


class IMode
{
public:
	IMode();
	void operator()();

protected:
	virtual void perform() = 0;
	void loadInstances();

	std::map<std::string, Instance> instanceMap;
	SmartStopwatch m_stopWatch;
	CCsvHelper m_csv;
	CAlgorithmFactory m_algorithmFactory;
};

#endif