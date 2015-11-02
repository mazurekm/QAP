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
	CConfManager(const std::string &path);
	Json::Value getRoot() const;

	std::unordered_set<std::string> getStrategies();
	std::unordered_map<std::string, std::string> getInputData();
	double getTimeLimit() const;
	Json::Value getAlgParameters(const std::string &algName);

private:
	std::string m_path;	
	Json::Value m_root;
	Json::Reader m_reader;
};

#endif