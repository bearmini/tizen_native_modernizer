#include "tnm.h"
#include "TizenNativeModernizer.h"

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
	auto str = "a => 1, b => 2, c => 3";
	std::vector<std::string> a = split(str, ",");
	ASSERT_TRUE(a.size() == 3);
}
TEST_F(TestSuite, test_stlmap)
{
	auto str = "a => 1, b => 2, c => 3";
	std::auto_ptr<IMap> src(gen_hashmap(str));
	ASSERT_TRUE(src->GetCount() == 3);
}
