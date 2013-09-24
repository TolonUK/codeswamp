#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <code_record.h>
#include <fstream>
#include <sstream>

using namespace codeswamp;
using namespace std;
using namespace testing;

TEST(code_record, default_ctor_equality)
{
    CCodeRecord cr1, cr2;
    EXPECT_TRUE(cr1 == cr2);
}

TEST(code_record, equality)
{
    CCodeRecord cr1("one", "two", CCode(1,2,3,4));
    CCodeRecord cr2("one", "two", CCode(1,2,3,4));

    EXPECT_TRUE(cr1 == cr2);
}

TEST(code_record, non_equality)
{
    CCodeRecord cr1("one", "two", CCode(1,2,3,4));
    CCodeRecord cr2("three", "four", CCode(5,6,7,8));

    EXPECT_FALSE(cr1 == cr2);
}
