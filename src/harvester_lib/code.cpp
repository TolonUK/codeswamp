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
#include "code.h"
#include <iostream>
#include <boost/tuple/tuple_comparison.hpp>

using namespace boost;
using namespace codeswamp;
using namespace std;

bool CCode::operator==(const CCode& rhs) const
{
    return
        boost::tie(m_code, m_facility, m_raw_code, m_severity)
        ==
        boost::tie(rhs.m_code, rhs.m_facility, rhs.m_raw_code, rhs.m_severity);
}

std::ostream& codeswamp::operator<<(std::ostream& os, const CCode& c)
{
    return os << "CCode("
              << "m_raw_code := " << c.m_raw_code
              << ", m_code := " << c.m_code
              << ", m_facility := " << c.m_facility
              << ", m_severity := " << c.m_severity
              << ")";
}
