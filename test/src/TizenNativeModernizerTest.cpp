#include "tnm.h" // under test

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

TEST_F(TestSuite, test_stlmap)
{
	using namespace tnm;
	auto str = "a => 1, b => 2, c => 3, ,e=>5";
	std::auto_ptr<IMap> map(gen_hashmap(str));
	ASSERT_TRUE(map->GetCount() == 4);
	ASSERT_TRUE(stlstr(map->GetValue(String("a"))) == "1");
	ASSERT_TRUE(stlstr(map->GetValue(String("b"))) == "2");
	ASSERT_TRUE(stlstr(map->GetValue(String("c"))) == "3");
	ASSERT_TRUE(stlstr(map->GetValue(String("e"))) == "5");
}
