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
#include "code_record.h"
#include <iostream>
#include <boost/tuple/tuple_comparison.hpp>

using namespace codeswamp;
using namespace std;

CCodeRecord::CCodeRecord()
{ }

CCodeRecord::CCodeRecord(
        const std::string& identifier, 
        const std::string& comment,
        const CCode& code) : 
    m_identifier(identifier),
    m_comment(comment),
    m_code(code)
{ }

CCodeRecord::CCodeRecord(
        std::string&& identifier,
        std::string&& comment,
        CCode&& code) :
    m_identifier(identifier),
    m_comment(comment),
    m_code(code)
{ }

bool CCodeRecord::operator==(const CCodeRecord& rhs) const
{
    return
        boost::tie(m_code, m_comment, m_identifier)
        ==
        boost::tie(rhs.m_code, rhs.m_comment, rhs.m_identifier);
}

std::ostream& codeswamp::operator<<(std::ostream& os, const CCodeRecord& cr)
{
    return os << "CCodeRecord("
              << "m_identifier := " << cr.m_identifier
              << ", m_comment := " << cr.m_comment
              << ", m_code := " << cr.m_code
              << ")";
}
