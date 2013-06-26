/*
 * Tizen Native Modernizer
 * Copyright (c) 2013 Takashi Oguma
 *
 * You may use any Tizen Native Modernizer project under the terms of the MIT License.
 */

#ifndef _TIZENNATIVEMODERNIZER_H_
#define _TIZENNATIVEMODERNIZER_H_

// C++ headers
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

// algorithms fo Tizen classes
template<class fun_t>
_EXPORT_ void iterate_on_map(const Tizen::Base::Collection::IMap* pMap, fun_t f);

// conversions from STL classes to Tizen classes
_EXPORT_ Tizen::Base::Collection::IMap* gen_hashmap(const std::string& str);

// conversion functions from Tizen classes to STL classes
std::string stlstr(const Tizen::Base::Object* pStr);
std::string stlstr(const Tizen::Base::String* pStr);
std::string stlstr(const Tizen::Base::String& str);
template<class T>
_EXPORT_ std::vector<T> stlvec(const Tizen::Base::Collection::IList* pList);

template<class T>
_EXPORT_ std::vector<T> stlvec(const Tizen::Base::ByteBuffer* pBuffer);

template<class key_t, class value_t>
_EXPORT_ std::map<key_t, value_t> stlmap(const Tizen::Base::Collection::IMap* pMap);

}

#endif // _TIZENNATIVEMODERNIZER_H_

