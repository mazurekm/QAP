#include "ConfManager.h"
#include <boost/filesystem.hpp>
#include <fstream>

CConfManager::CConfManager(const std::string &path) : m_path(path)
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
	   false == m_root.isMember("TimeLimit") )
	{
		throw JsonParseException("Strategy, Data and TimeLimit fields are required");
	}

}

Json::Value CConfManager::getRoot() const
{
	return m_root;
}

std::unordered_set<std::string> CConfManager::getStrategies()
{
	auto data = m_root["Strategy"].getMemberNames();
	std::unordered_set<std::string> result(data.begin(), data.end());
	return result;
}

std::unordered_set<std::string> CConfManager::getInputData()
{
	auto data = m_root["Data"];
	std::unordered_set<std::string> result;
	for(auto & obj : data)
	{
		if(true == obj.isString())
		{
			result.insert(obj.asString());
		}
	}
	return result;
}

Json::Value CConfManager::getAlgParameters(const std::string &algName)
{
	if(false == m_root["Strategy"].isMember(algName))
	{
		return Json::Value();
	}
	return m_root["Strategy"][algName]; 
}

double CConfManager::getTimeLimit() const
{
	return m_root["TimeLimit"].asDouble();
}
