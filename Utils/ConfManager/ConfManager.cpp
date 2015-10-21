#include "ConfManager.h"
#include <boost/filesystem.hpp>
#include <stdexcept>

class JsonNotFoundException : public std::runtime_error
{
public:
	JsonNotFoundException() : std::runtime_error("Could not find config file")	
	{
		
	}
};

CConfManager::CConfManager(const std::string &path) : m_path(path)
{
	if (false == boost::filesystem::exists( path ) )
	{
  		throw new JsonNotFoundException();
	}
}