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


#if __cplusplus >= 201103L // newer than or equal to C++11

#else // older than C++11

#endif // __cplusplus >= 201103L


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

std::vector<std::string> split(const std::string& str, const std::string& delim);

_EXPORT_ Tizen::Base::Collection::IMap* gen_hashmap(const std::string& str);

template<class fun_t>
_EXPORT_ void iterate_on_map(const Tizen::Base::Collection::IMap* pMap, fun_t f);

template<class T>
_EXPORT_ std::vector<T> stlvec(const Tizen::Base::Collection::IList* pList);

template<class T>
_EXPORT_ std::vector<T> stlvec(const Tizen::Base::ByteBuffer* pBuffer);

template<class key_t, class value_t>
_EXPORT_ std::map<key_t, value_t> stlmap(const Tizen::Base::Collection::IMap* pMap);


#endif // _TIZENNATIVEMODERNIZER_H_

