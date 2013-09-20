#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <code_scanner.h>
#include <sstream>

using namespace codeswamp;
using namespace std;
using namespace testing;

class CMockSink : public ICodePreRecordSink
{
public:
    virtual void operator()(const CCodePreRecord& o)
    { call_op(o); }

    MOCK_METHOD1(call_op, void(const CCodePreRecord&));
};

const char* TEST_EMPTY = "";
TEST(code_scanner, empty_data)
{
    CMockSink s;
    code_scanner cs;
    istringstream iss(TEST_EMPTY);

    EXPECT_CALL(s, call_op(_)).Times(0);

    cs.parse(iss, s);
}

const char* TEST_SPACE = " ";
TEST(code_scanner, space_data)
{
    CMockSink s;
    code_scanner cs;
    istringstream iss(TEST_SPACE);

    EXPECT_CALL(s, call_op(_)).Times(0);

    cs.parse(iss, s);
}
