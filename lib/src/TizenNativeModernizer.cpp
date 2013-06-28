/*
 * Tizen Native Modernizer
 * Copyright (c) 2013 Takashi Oguma
 *
 * You may use any Tizen Native Modernizer project under the terms of the MIT License.
 */

#include "TizenNativeModernizer.h"

// C++ headers
#include <iostream>
#include <memory>

// Tizen headers

// using namespaces
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

namespace tnm
{

// improvements for std::string
std::vector<std::string>
split(const std::string& str, const std::string& delim)
{
	std::vector<std::string> result;

	size_t current = 0;
	size_t found = 0;
	size_t delimlen = delim.size();
	while ((found = str.find(delim, current)) != std::string::npos)
	{
		result.push_back(std::string(str, current, found - current));
		current = found + delimlen;
	}
	result.push_back(std::string(str, current, str.size() - current));
	return result;
}

std::string
ltrim(const std::string& str)
{
	std::string s(str);
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

std::string
rtrim(const std::string& str)
{
	std::string s(str);
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

std::string
trim(const std::string& s)
{
	return ltrim(rtrim(s));
}

IMap* gen_hashmap_n(const std::string& str)
{
	return gen_hashmap_n(str,
			[](const std::string& key){return new String(key.c_str());},
			[](const std::string& val){return new String(val.c_str());});
}

std::string
stlstr(const Object* pObj)
{
	auto pStr = dynamic_cast<const String*>(pObj);
	if (pStr != null)
	{
		return stlstr(pStr);
	}
	else
	{
		return "";
	}
}

std::string
stlstr(const String* pStr)
{
	size_t length = ::wcstombs(null, pStr->GetPointer(), 0);
	scoped_array<char> buf(new char[length + 1]);
	::memset(buf.get(), 0, length + 1);
	::wcstombs(buf.get(), pStr->GetPointer(), length);
	return std::string(buf.get());
}

std::string
stlstr(const String& str)
{
	return stlstr(&str);
}

}
