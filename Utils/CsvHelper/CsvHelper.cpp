#include "CsvHelper.h"
#include <fstream>

#include <boost/algorithm/string.hpp>

CCsvHelper::CCsvHelper(const char fieldDelimiter, const std::string &unescapeStr)
{
	m_osst.set_delimiter(fieldDelimiter, unescapeStr.c_str());
}

std::string CCsvHelper::getText()
{
	std::string text = m_osst.get_text();
    //boost::replace_all(text, m_osst.get_escape_str(), m_osst.get_delimiter());
    return text;
}

void CCsvHelper::clear()
{
	m_osst.get_ostringstream().str("");
}

void CCsvHelper::toFile(const std::string & filename)
{
	std::fstream fd(filename, std::ios_base::out);
	fd << getText();
	fd.close();
}
