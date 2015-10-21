#ifndef CONF_MANAGER
#define CONF_MANAGER

#include <string>
#include <json/json.h>

class CConfManager
{
public:
	CConfManager(const std::string &path);
private:
	std::string m_path;	
	Json::Value m_root;
	Json::Reader m_reader;
};

#endif