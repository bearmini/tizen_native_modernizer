/*
 * Tizen Native Modernizer
 * Copyright (c) 2013 Takashi Oguma
 *
 * You may use any Tizen Native Modernizer project under the terms of the MIT License.
 */

#ifndef _TIZENNATIVEMODERNIZER_H_
#define _TIZENNATIVEMODERNIZER_H_

// C++ headers
#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

// Tizen headers
#include <FBase.h>

namespace tnm
{

#if __cplusplus >= 201103L // newer than or equal to C++11

#else // older than C++11

#endif // __cplusplus >= 201103L

// boost-ish utility classes
template<class T>
class scoped_ptr
{
public:
	scoped_ptr(T* p): __p(p) {}
	~scoped_ptr() { delete __p; }
private:
	T* __p;
};

template<class T>
class scoped_array
{
public:
	scoped_array(T* p) : __p(p) {}
	virtual ~scoped_array()	{ delete[] __p; }
	T* get() const { return __p; }
private:
	T* __p;
};

// improvements for std::string
std::vector<std::string> split(const std::string& str, const std::string& delim);
std::string ltrim(const std::string& str);
std::string rtrim(const std::string& str);
std::string trim(const std::string& str);

/**
 *  generates a ByteBuffer object.
 *  @param   a [in] source of the buffer
 *  @param   size [in] size of 'a' in bytes
 *  @return  a pointer to a created ByteBuffer object
 */
Tizen::Base::ByteBuffer* gen_bb_n(const byte a[], size_t size)
{
	auto result = new Tizen::Base::ByteBuffer();
	result->Construct(size);
	for (size_t i = 0; i < size; ++i)
	{
		result->SetByte(i, a[i]);
	}
	return result;
}

template<size_t N>
Tizen::Base::ByteBuffer* gen_bb_n(const std::array<byte, N>& a)
{
	return gen_bb_n(a.data(), a.size());
}

// algorithms fo Tizen classes
template<class fn_t>
_EXPORT_ void iterate_on_bb(const Tizen::Base::ByteBuffer* pBuffer, size_t start, size_t length, fn_t fn)
{
	for (size_t i = start; i < start + length; ++i)
	{
		byte b;
		pBuffer->GetByte(i, b);
		fn(i, b);
	}
}

template<class fn_t>
_EXPORT_ void iterate_on_bb(const Tizen::Base::ByteBuffer* pBuffer, fn_t fn)
{
	iterate_on_bb(pBuffer, 0, pBuffer->GetCapacity(), fn);
}

template<class fn_t>
_EXPORT_ void iterate_on_list(const Tizen::Base::Collection::IList* pList, fn_t fn)
{
	std::unique_ptr<Tizen::Base::Collection::IEnumerator> pEnum(pList->GetEnumeratorN());
	while (pEnum->MoveNext() == E_SUCCESS)
	{
		fn(pEnum->GetCurrent());
	}
}

template<class fn_t>
_EXPORT_ void iterate_on_map(const Tizen::Base::Collection::IMap* pMap, fn_t fn)
{
	std::unique_ptr<Tizen::Base::Collection::IMapEnumerator> pEnum(pMap->GetMapEnumeratorN());
	while (pEnum->MoveNext() == E_SUCCESS)
	{
		fn(pEnum->GetKey(), pEnum->GetValue());
	}
}

// conversions from STL classes to Tizen classes
template<class fk_t, class fv_t>
Tizen::Base::Collection::IMap* gen_hashmap_n(const std::string& str, fk_t fk, fv_t fv)
{
	using namespace Tizen::Base::Collection;

	auto pMap = new HashMap(SingleObjectDeleter);
	pMap->Construct();

	auto&& a = split(str, ",");
	std::for_each(a.begin(), a.end(), [pMap, fk, fv](const std::string& s){
		auto&& kv = split(s, "=>");
		if (kv.size() < 2)
		{
			return;
		}

		auto&& k = trim(kv[0]);
		if (k == "")
		{
			return;
		}

		auto&& v = trim(kv[1]);

		pMap->Add(fk(k), fv(v));
	});

	return pMap;
}

_EXPORT_ Tizen::Base::Collection::IMap* gen_hashmap_n(const std::string& str);

// conversion functions from Tizen classes to STL classes
std::string stlstr(const Tizen::Base::Object* pStr);
std::string stlstr(const Tizen::Base::String* pStr);
std::string stlstr(const Tizen::Base::String& str);

template<class T, class fn_t>
std::vector<T>
stlvec(const Tizen::Base::Collection::IList* pList, fn_t fn)
{
	std::vector<T> result;
	iterate_on_list(pList, [&](Tizen::Base::Object* pVal) {
		result.push_back(fn(pVal));
	});
	return result;
}

template<class T, class fn_t>
std::vector<T>
stlvec(const Tizen::Base::ByteBuffer* pBuffer, fn_t fn)
{
	std::vector<T> result;
	iterate_on_bb(pBuffer, [&](byte b) {
		result.push_back(fn(b));
	});
	return result;
}

template<class key_t, class val_t, class fn_k_t, class fn_v_t>
std::map<key_t, val_t>
stlmap(const Tizen::Base::Collection::IMap* pMap, fn_k_t fk, fn_v_t fv)
{
	typedef std::map<key_t, val_t> map_t;
	map_t result;
	iterate_on_map(pMap, [&](Tizen::Base::Object* pKey, Tizen::Base::Object* pVal) {
		auto&& key = fk(pKey);
		auto&& val = fv(pVal);
		result.insert(make_pair(key, val));
	});
	return result;
}

}

#endif // _TIZENNATIVEMODERNIZER_H_

