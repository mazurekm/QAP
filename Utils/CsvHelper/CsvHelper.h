#include <minicsv/minicsv.h>
#include <string>

class CCsvHelper
{
public:
	CCsvHelper(const char fieldDelimiter = ';', const std::string& unescape = "$$");
	void toFile(const std::string &filename);
	std::string getText(); 
	void clear();

	template <typename T> void add(T value)
	{
		m_osst << value << NEWLINE;
	}

	template <typename T, typename ... Params> void add(T value, Params ... params)
	{
		m_osst << value;
		add(params... );
	}

private:
	csv::ostringstream m_osst;
};