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
#ifndef CODESWAMP__CODE_RECORD_H
#define CODESWAMP__CODE_RECORD_H

#include "code.h"
#include <iosfwd>
#include <string>

namespace codeswamp {

class CCodeRecord
{
public:
    CCodeRecord();

    CCodeRecord(
        const std::string& identifier, 
        const std::string& comment,
        const CCode& code);

    CCodeRecord(
        std::string&& identifier,
        std::string&& comment,
        CCode&& code);

    CCodeRecord(const CCodeRecord& src) :
        m_identifier(src.m_identifier),
        m_comment(src.m_comment),
        m_code(src.m_code)
    { }

    bool operator==(const CCodeRecord& rhs) const;

    friend std::ostream& operator<<(std::ostream&, const CCodeRecord&);

private:
    std::string m_identifier;
    std::string m_comment;
    CCode m_code;
};

}

#endif
