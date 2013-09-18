#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <comment_stripper_winpsdk.h>
#include <string>

using namespace testing;

//--------------------------------------------------------------------------------

const char* COMMENT_MSGTEXT_IN = 
"//\n"
"// MessageId: ERROR_NET_OPEN_FAILED\n"
"//\n"
"// MessageText:\n"
"//\n"
"// The NtCreateFile API failed. This error should never be returned to an application, it is a place holder for the Windows Lan Manager Redirector to use in its internal error mapping routines.\n"
"//";

const char* COMMENT_MSGTEXT_OUT =
"The NtCreateFile API failed. This error should never be returned to an application, it is a place holder for the Windows Lan Manager Redirector to use in its internal error mapping routines.";

TEST(comment_stripper, msgtext)
{
    std::string out = strip_comment_winpsdk(COMMENT_MSGTEXT_IN);
    EXPECT_EQ(std::string(COMMENT_MSGTEXT_OUT), out);
}

//--------------------------------------------------------------------------------

const char* COMMENT_D2D_PREAMBLE_IN =
"//\n"
"// D2D specific codes\n"
"//\n"
"\n"
"//\n"
"// The object was not in the correct state to process the method.\n"
"//";

const char* COMMENT_D2D_PREAMBLE_OUT =
"The object was not in the correct state to process the method.";

TEST(comment_stripper, d2d_preamble)
{
	std::string out = strip_comment_winpsdk(COMMENT_D2D_PREAMBLE_IN);
	EXPECT_EQ(std::string(COMMENT_D2D_PREAMBLE_OUT), out);
}

//--------------------------------------------------------------------------------

const char* COMMENT_D2D_IN =
"//\n"
"// The object has not yet been initialized.\n"
"//";

const char* COMMENT_D2D_OUT =
"The object has not yet been initialized.";

TEST(comment_stripper, d2d)
{
	std::string out = strip_comment_winpsdk(COMMENT_D2D_IN);
	EXPECT_EQ(std::string(COMMENT_D2D_OUT), out);
}

//--------------------------------------------------------------------------------

const char* COMMENT_END_NEWLINE_IN =
"////////////////////////////////////\n"
"//                                //\n"
"\n"
"\n"
"//\n"
"// The return value of COM functions and methods is an HRESULT.\n"
"//\n"
"// Newly written code should use the HRESULT macros and functions.\n"
"//\n"
"\n"
"//\n"
"//  HRESULTs are 32 bit values layed out as follows:\n"
"//\n"
"//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1\n"
"//\n"
"//  where\n"
"//\n"
"\n"
"//\n"
"// Severity values\n"
"//\n"
"\n";

const char* COMMENT_END_NEWLINE_OUT =
"Severity values";

TEST(comment_stripper, end_newline)
{
	std::string out = strip_comment_winpsdk(COMMENT_END_NEWLINE_IN);
	EXPECT_EQ(std::string(COMMENT_END_NEWLINE_OUT), out);
}
