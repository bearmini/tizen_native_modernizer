/*
 * Tizen Native Modernizer
 * Copyright (c) 2013 Takashi Oguma
 *
 * You may use any Tizen Native Modernizer project under the terms of the MIT License.
 */

#include "TizenNativeModernizer.h"

// C++ headers
#include <memory>

// Tizen headers

// using namespaces
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;


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

template<class fk_t, class fv_t>
IMap* gen_hashmap(const std::string& str, fk_t fk, fv_t fv)
{
	HashMap* pMap = new HashMap(SingleObjectDeleter);
	pMap->Construct();

	std::vector<std::string>&& a = split(str, ",");
	std::for_each(a.begin(), a.end(), [pMap, fk, fv](const std::string& s){
		std::vector<std::string>&& kv = split(s, "=>");
		if (kv.size() != 2)
			return;

		auto k = kv[0];
		auto v = kv[1];
		pMap->Add(fk(k), fv(v));
	});

	return pMap;
}

IMap* gen_hashmap(const std::string& str)
{
	return gen_hashmap(str,
			[](const std::string& key){return new String(key.c_str());},
			[](const std::string& val){return new String(val.c_str());});
}

template<class fun_t>
_EXPORT_ void iterate_on_map(const IMap* pMap, fun_t f)
{
	std::auto_ptr<IMapEnumerator> pEnum(pMap->GetMapEnumeratorN());
	while (pEnum->MoveNext() == E_SUCCESS)
	{
		f(pEnum->GetKey(), pEnum->GetValue());
	}
}

std::string
stlstr(const String& str)
{
	size_t length = ::wcstombs(null, str.GetPointer(), 0);
	scoped_array<char> buf(new char[length + 1]);
	::memset(buf.get(), 0, length + 1);
	::wcstombs(buf.get(), str.GetPointer(), length);
	return std::string(buf.get());
}

template<class T>
std::vector<T>
stlvec(const IList* pList)
{
	std::vector<T> result;
	return result;
}

template<class T>
std::vector<T>
stlvec(const ByteBuffer* pBuffer)
{
	std::vector<T> result;
	return result;
}

template<class key_t, class val_t>
std::map<key_t, val_t>
stlmap(const IMap* pMap)
{
	std::map<key_t, val_t> result;
	iterate_on_map(pMap, [&result](Object* pKey, Object* pVal) {
		auto key = static_cast<key_t>(pKey);
		auto val = static_cast<val_t>(pVal);
		result.insert(make_pair(key, val));
	});
	return result;
}
