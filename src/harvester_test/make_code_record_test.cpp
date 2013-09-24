#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <code_scanner.h>
#include <make_code_record.h>
#include <fstream>
#include <sstream>

using namespace codeswamp;
using namespace std;
using namespace testing;

TEST(make_code_record, skip_header_preamble)
{
    make_code_record mcr;

    code_scanner cs;
    ifstream ifs("..\\data\\test_cases\\skip_header_preamble.h");

    cs.parse(ifs, mcr);

    CCodeRecord cr("FACILITY_XPS", "Define the facility codes", CCode(82,82,0,0));

    EXPECT_EQ(cr, mcr.cr());
}

TEST(make_code_record, lone_facility_code)
{
    make_code_record mcr;

    code_scanner cs;
    ifstream ifs("..\\data\\test_cases\\lone_facility_code.h");

    cs.parse(ifs, mcr);

    CCodeRecord cr("FACILITY_XAML", "", CCode(43,43,0,0));

    EXPECT_EQ(cr, mcr.cr());
}
