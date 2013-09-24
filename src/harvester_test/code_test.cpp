#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <code.h>
#include <fstream>
#include <sstream>

using namespace codeswamp;
using namespace std;
using namespace testing;

TEST(code, default_ctor_equality)
{
    CCode c1, c2;
    EXPECT_TRUE(c1 == c2);
}

TEST(code, equality)
{
    CCode c1(1,2,3,4);
    CCode c2(1,2,3,4);

    EXPECT_TRUE(c1 == c2);
}

TEST(code, non_equality)
{
    CCode c1(1,2,3,4);
    CCode c2(5,6,7,8);

    EXPECT_FALSE(c1 == c2);
}
