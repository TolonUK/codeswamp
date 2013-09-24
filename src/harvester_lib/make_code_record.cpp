/*
Codeswamp is copyright (c) 2013, Alex Paterson (alex@tolon.co.uk).
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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

void make_code_record::operator()(const CCodePreRecord& in)
{ m_cr = make_code_record_impl(in); }
