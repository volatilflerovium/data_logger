#ifndef TRAITS_H
#define TRAITS_H

#include <string>

template<typename T>
struct ToString
{
	static std::string toStr(T t) {
		try {
			return std::to_string(t);
		}
		catch (...) {
			return std::string("!!");
		}
	}
};

template<>
struct ToString<std::string>
{
	static std::string toStr(const std::string& str) {
		return str;
	}
};

template<>
struct ToString<const char*>
{
	static std::string toStr(const char* cstr) {
		return cstr;
	}
};

template<>
struct ToString<bool>
{
	static std::string toStr(bool a) {
		if (a) {
			return std::string("true");
		}
		return std::string("false");
	}
};

#endif
