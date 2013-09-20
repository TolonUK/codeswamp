#include "make_code_record.h"
#include "comment_stripper_winpsdk.h"
#include <winerror.h>
#include <iostream>
#include <string>
#include <sstream>

using namespace codeswamp;
using namespace std;

// make_code_record

string mcri_identifier(const CCodePreRecord& in)
{
    if (in.has_identifier())
        return in.first_identifier();
    else
        return string();
}

string mcri_comment(const CCodePreRecord& in)
{ 
    stringstream ss;
    in.copy_comment_store(ostream_iterator<string>(ss));
    return strip_comment_winpsdk(ss.str());
}

CCode mcri_code(const CCodePreRecord& in)
{ 
    unsigned __int32 nRawCode = 0;

    {
        stringstream ss;
        in.copy_number_store(ostream_iterator<string>(ss));
        ss >> nRawCode;
    }

    if (!nRawCode)
    {
        stringstream ss;
        ss << hex;
        in.copy_number_store(ostream_iterator<string>(ss));
        ss >> nRawCode;
    }

    return CCode(
        nRawCode,
        HRESULT_CODE(nRawCode),
        HRESULT_FACILITY(nRawCode),
        HRESULT_SEVERITY(nRawCode));
}

CCodeRecord make_code_record_impl(const CCodePreRecord& in)
{
    return CCodeRecord(
        mcri_identifier(in),
        mcri_comment(in),
        mcri_code(in));
}

make_code_record::make_code_record(const CCodePreRecord& in) :
    m_cr(make_code_record_impl(in))
{ }
