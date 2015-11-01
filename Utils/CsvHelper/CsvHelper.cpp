#include "CsvHelper.h"
#include <fstream>

CCsvHelper::CCsvHelper(const char fieldDelimiter, const std::string &newlineDelimiter)
{
	m_osst.set_delimiter(fieldDelimiter, newlineDelimiter.c_str());
}

void CCsvHelper::toFile(const std::string & filename)
{
	std::fstream fd(filename, std::ios_base::out);
	fd << m_osst.get_text();
	fd.close();
}
