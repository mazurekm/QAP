#ifndef SETTING
#define SETTING

#include <boost/variant/variant.hpp>
#include <string>

typedef boost::variant<std::string, unsigned, double> Setting;

#endif