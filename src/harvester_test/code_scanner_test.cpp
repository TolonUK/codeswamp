#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <code_scanner.h>
#include <fstream>
#include <sstream>

using namespace codeswamp;
using namespace std;
using namespace testing;

class CMockSink : public ICodePreRecordSink
{
public:
    virtual void operator()(const CCodePreRecord& o)
    {
        m_last_cpr = o;
        call_op(o); 
    }

    MOCK_METHOD1(call_op, void(const CCodePreRecord&));

    const CCodePreRecord& last_cpr() const
    { return m_last_cpr; }

private:
    CCodePreRecord m_last_cpr;
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

TEST(code_scanner, skip_header_preamble)
{
    CMockSink s;
    code_scanner cs;
    ifstream ifs("..\\data\\test_cases\\skip_header_preamble.h");

    EXPECT_CALL(s, call_op(_));
    
    cs.parse(ifs, s);

    CCodePreRecord cpr;
    cpr.add_identifier("FACILITY_XPS");
    cpr.add_number("82");

    EXPECT_EQ(cpr.identifier_store(), s.last_cpr().identifier_store());
    EXPECT_EQ(cpr.number_store(), s.last_cpr().number_store());
}
