#include "ConfManager.h"
#include <boost/filesystem.hpp>
#include <stdexcept>
#include <fstream>

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

CConfManager::CConfManager(const std::string &path) : m_path(path)
{
	if (false == boost::filesystem::exists( path ) )
	{
  		throw new JsonNotFoundException();
	}

	std::ifstream fs(path);

	if(false == m_reader.parse(fs, m_root))
	{
		fs.close();
		throw new JsonParseException( m_reader.getFormattedErrorMessages() );
	}
	fs.close();
}

Json::Value CConfManager::getRoot() const
{
	return m_root;
}