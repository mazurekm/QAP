#include "ConfManager.h"
#include <boost/filesystem.hpp>
#include <fstream>

void CConfManager::loadConfiguration(const std::string &path)
{
	if (false == boost::filesystem::exists( path ) )
	{
  		throw JsonNotFoundException();
	}

	std::ifstream fs(path);

	if(false == m_reader.parse(fs, m_root))
	{
		fs.close();
		throw JsonParseException( m_reader.getFormattedErrorMessages() );
	}

	fs.close();

	if(false == m_root.isMember("Strategy") || 
	   false == m_root.isMember("Data") ||
	   false == m_root.isMember("TimeLimit") ||
	   false == m_root.isMember("Mode") || 
	   false == m_root.isMember("IterationLimit"))
	{
		throw JsonParseException("Strategy, Data, Mode and TimeLimit fields are required");
	}

}

Json::Value CConfManager::getRoot() const
{
	return m_root;
}

std::unordered_set<std::string> CConfManager::getStrategies()
{
	if(true == m_root.getMemberNames().empty())
	{
		return std::unordered_set<std::string>();
	}

	auto data = m_root["Strategy"].getMemberNames();
	std::unordered_set<std::string> result(data.begin(), data.end());
	return result;
}

std::unordered_map<std::string, std::string> CConfManager::getInputData()
{
	if(true == m_root.getMemberNames().empty())
	{
		return std::unordered_map<std::string, std::string>();
	}

	auto data = m_root["Data"];
	std::unordered_map<std::string, std::string> result;
	for(auto & obj : data)
	{
		if(true == obj[0].isString())
		{
			result[obj[0].asString()] = obj[1].asString();
		}
	}
	return result;
}

Json::Value CConfManager::getAlgParameters(const std::string &algName)
{
	if(true == m_root.getMemberNames().empty())
	{
		return m_root;
	}

	if(false == m_root["Strategy"].isMember(algName))
	{
		return Json::Value();
	}
	return m_root["Strategy"][algName]; 
}

double CConfManager::getTimeLimit() const
{
	if(true == m_root.getMemberNames().empty())
	{
		return 0;
	}

	return m_root["TimeLimit"].asDouble();
}

long CConfManager::getIterationLimit() const {

	if(true == m_root.getMemberNames().empty())
	{
		return 0;
	}
	return m_root["IterationLimit"].asInt();
}

std::unordered_set<std::string> CConfManager::getModes()
{
	if(true == m_root.getMemberNames().empty())
	{
		return std::unordered_set<std::string>();
	}
	
	auto data = m_root["Mode"].getMemberNames();
	std::unordered_set<std::string> result(data.begin(), data.end());
	return result;
}