#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <code_scanner.h>
#include <make_code_record.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace codeswamp;
using namespace std;
using namespace testing;

struct test_case
{
    const char* filename;
    CCodeRecord* expected;
    size_t expected_count;
};

class mock_make_code_record : public make_code_record
{
public:
    virtual void operator()(const CCodePreRecord& in)
    {
        make_code_record::operator()(in);
        result(cr());
    }

    MOCK_METHOD1(result, void(const CCodeRecord&));
};

void run_test_case(const test_case& tc)
{
    mock_make_code_record mmcr;

    string filepath("..\\data\\test_cases\\");
    filepath += tc.filename;

    code_scanner cs;
    ifstream ifs(filepath);

    for (size_t i = 0; i < tc.expected_count; ++i)
        EXPECT_CALL(mmcr, result(tc.expected[i]));

    cs.parse(ifs, mmcr);
}

TEST(make_code_record, skip_header_preamble)
{
    CCodeRecord cr("FACILITY_XPS", "Define the facility codes", CCode(82,82,0,0));
    test_case tc = {
        "skip_header_preamble.h",
        &cr,
        1 };

    run_test_case(tc);
}

TEST(make_code_record, lone_facility_code)
{
    CCodeRecord cr("FACILITY_XAML", "", CCode(43,43,0,0));
    test_case tc = {
        "lone_facility_code.h",
        &cr,
        1 };
    
    run_test_case(tc);
}

TEST(make_code_record, messageid_and_undoc_codes)
{
    CCodeRecord cr[] = {
        CCodeRecord("ERROR_SUCCESS", "The operation completed successfully.", CCode(0,0,0,0)),
        CCodeRecord("NO_ERROR" , "", CCode(0,0,0,0)),
        CCodeRecord("SEC_E_OK", "", CCode(0,0,0,0)),
        CCodeRecord("ERROR_INVALID_FUNCTION", "Incorrect function.", CCode(1,1,0,0)) };
    const size_t cr_count = sizeof(cr)/sizeof(cr[0]);

    test_case tc = {
        "messageid_and_undoc_codes.h",
        cr,
        cr_count };

    run_test_case(tc);
}
