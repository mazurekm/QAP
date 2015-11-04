#ifndef CONF_MANAGER
#define CONF_MANAGER

#include <string>
#include <unordered_set>
#include <unordered_map>

#include <json/json.h>
#include <json/reader.h>
#include <stdexcept>

class JsonNotFoundException : public std::runtime_error
{
public:
	JsonNotFoundException() : std::runtime_error("Could not find config file")	
	{

	}
};

class JsonParseException : public std::runtime_error
{
public:
	JsonParseException(const std::string & error) : std::runtime_error(error)
	{

	}	
};


class CConfManager
{
public:
	Json::Value getRoot() const;

	static CConfManager& getInstance()
	{
  		static CConfManager instance;
  		return instance;
	}

	void loadConfiguration(const std::string &path);

	std::unordered_set<std::string> getStrategies();
	std::unordered_set<std::string> getModes();
	std::unordered_map<std::string, std::string> getInputData();
	double getTimeLimit() const;
	long getIterationLimit() const;
	Json::Value getAlgParameters(const std::string &algName);

private:
	CConfManager() {} 
	CConfManager(const CConfManager &) = delete;
	CConfManager(CConfManager &&) = delete;
	CConfManager & operator=(const CConfManager &) = delete;
	CConfManager & operator==(CConfManager &&) = delete;

	
	Json::Value m_root;
	Json::Reader m_reader;
};

#endif