#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <code_scanner.h>
#include <fstream>
#include <sstream>

using namespace codeswamp;
using namespace std;
using namespace testing;

TEST(code_pre_record, default_ctor_equality)
{
    CCodePreRecord cpr1, cpr2;
    EXPECT_TRUE(cpr1 == cpr2);
}

TEST(code_pre_record, equality)
{
    CCodePreRecord cpr1("one", "two", "three", "four");
    CCodePreRecord cpr2("one", "two", "three", "four");

    EXPECT_TRUE(cpr1 == cpr2);
}

TEST(code_pre_record, non_equality)
{
    CCodePreRecord cpr1("one", "two", "three", "four");
    CCodePreRecord cpr2("five", "six", "seven", "eight");

    EXPECT_FALSE(cpr1 == cpr2);
}
