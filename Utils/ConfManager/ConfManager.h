#ifndef CONF_MANAGER
#define CONF_MANAGER

#include <string>
#include <json/json.h>
#include <json/reader.h>

class CConfManager
{
public:
	CConfManager(const std::string &path);
	Json::Value getRoot() const;
private:
	std::string m_path;	
	Json::Value m_root;
	Json::Reader m_reader;
};

#endif