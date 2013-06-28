#include "tnm.h" // under test

#include <algorithm>

#include <gtest/gtest.h>

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

_EXPORT_ int
OspMain(int argc, char *pArgv[])
{
	testing::InitGoogleTest( &argc, pArgv);
	return RUN_ALL_TESTS();
}
#ifdef __cplusplus
}
#endif // __cplusplus


class TestSuite : public testing::Test
{
protected:
	virtual void SetUp()
	{

	}
	virtual void TearDown()
	{

	}
};

TEST_F(TestSuite, test_split)
{
	using namespace tnm;
	auto str = "a => 1, b => 2, c => 3";
	std::vector<std::string> a = split(str, ",");
	ASSERT_TRUE(a.size() == 3);
	ASSERT_TRUE(a[0] == "a => 1");
	ASSERT_TRUE(a[1] == " b => 2");
	ASSERT_TRUE(a[2] == " c => 3");
}

TEST_F(TestSuite, test_ltrim)
{
	using namespace tnm;
	ASSERT_TRUE(ltrim("abc") == "abc");
	ASSERT_TRUE(ltrim(" abc") == "abc");
	ASSERT_TRUE(ltrim("  abc") == "abc");
	ASSERT_TRUE(ltrim("abc ") == "abc ");
	ASSERT_TRUE(ltrim("abc  ") == "abc  ");
	ASSERT_TRUE(ltrim(" abc  ") == "abc  ");
	ASSERT_TRUE(ltrim(" a bc  ") == "a bc  ");
}

TEST_F(TestSuite, test_rtrim)
{
	using namespace tnm;
	ASSERT_TRUE(rtrim("abc") == "abc");
	ASSERT_TRUE(rtrim(" abc") == " abc");
	ASSERT_TRUE(rtrim("  abc") == "  abc");
	ASSERT_TRUE(rtrim("abc ") == "abc");
	ASSERT_TRUE(rtrim("abc  ") == "abc");
	ASSERT_TRUE(rtrim(" abc  ") == " abc");
	ASSERT_TRUE(rtrim(" a bc  ") == " a bc");
}

TEST_F(TestSuite, test_trim)
{
	using namespace tnm;
	ASSERT_TRUE(trim("abc") == "abc");
	ASSERT_TRUE(trim(" abc") == "abc");
	ASSERT_TRUE(trim("  abc") == "abc");
	ASSERT_TRUE(trim("abc ") == "abc");
	ASSERT_TRUE(trim("abc  ") == "abc");
	ASSERT_TRUE(trim(" abc  ") == "abc");
	ASSERT_TRUE(trim(" a bc  ") == "a bc");
}

TEST_F(TestSuite, test_gen_bb_n)
{

}

TEST_F(TestSuite, test_iterate_on_bb)
{
	using namespace tnm;
	byte a[] = { 1, 2, 3 };
	std::unique_ptr<ByteBuffer> pBuf{gen_bb_n(a, sizeof(a))};

	std::vector<byte> v;
	iterate_on_bb(pBuf.get(), [&](const size_t& i, const byte& b){ v.push_back(i + b); });
	ASSERT_TRUE(v.size() == 3);
	ASSERT_TRUE(v[0] == 1);
	ASSERT_TRUE(v[1] == 3);
	ASSERT_TRUE(v[2] == 5);
}

TEST_F(TestSuite, test_gen_hashmap_n)
{
	using namespace tnm;
	auto str = "a => 1, b => 2, c => 3, ,e=>5";
	std::unique_ptr<IMap> map{gen_hashmap_n(str)};
	ASSERT_TRUE(map->GetCount() == 4);
	ASSERT_TRUE(stlstr(map->GetValue(String("a"))) == "1");
	ASSERT_TRUE(stlstr(map->GetValue(String("b"))) == "2");
	ASSERT_TRUE(stlstr(map->GetValue(String("c"))) == "3");
	ASSERT_TRUE(stlstr(map->GetValue(String("e"))) == "5");
}

TEST_F(TestSuite, test_stlmap)
{
	using namespace tnm;
	auto str = "a => 1, b => 2, c => 3, ,e=>5";
	std::unique_ptr<IMap> tm{gen_hashmap_n(str)};

	auto&& sm = stlmap<std::string, std::string>(tm.get(),
			[](Object* pKey){ return stlstr(pKey); },
			[](Object* pVal){ return stlstr(pVal); });
	ASSERT_TRUE(sm.size() == 4);
	ASSERT_TRUE(sm.at(std::string("a")) == "1");
	ASSERT_TRUE(sm.at(std::string("b")) == "2");
	ASSERT_TRUE(sm.at(std::string("c")) == "3");
	ASSERT_TRUE(sm.at(std::string("e")) == "5");
}
