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
#ifndef CODESWAMP__CODE_H
#define CODESWAMP__CODE_H

#include <iosfwd>

namespace codeswamp {

//! \todo comment this class
class CCode
{
public:
    CCode() :
        m_raw_code(0),
        m_code(0),
        m_facility(0),
        m_severity(0)
    { }

    CCode(
        unsigned __int32 raw_code,
        unsigned __int16 code,
        unsigned __int16 facility,
        unsigned __int16 severity) :
    m_raw_code(raw_code),
    m_code(code),
    m_facility(facility),
    m_severity(severity)
    { }

    bool operator==(const CCode& rhs) const;
 
    friend std::ostream& operator<<(std::ostream&, const CCode&);

private:
    unsigned __int32 m_raw_code;
    unsigned __int16 m_code;
    unsigned __int16 m_facility;
    unsigned __int16 m_severity;
};

}

#endif
