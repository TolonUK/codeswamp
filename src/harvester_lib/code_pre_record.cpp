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
#include "code_pre_record.h"
#include <iostream>
#include <boost/tuple/tuple_comparison.hpp>

using namespace codeswamp;
using namespace std;

namespace codeswamp {
template<typename T>
std::ostream& operator<<(std::ostream& o, const vector<T>& v)
{
    auto i = v.begin();

    if (i != v.end())
    {
        o << *i;
        ++i;
        for(; i != v.end(); ++i)
            o << "," << *i;
    }

    return o;
}
} // namespace codeswamp

bool CCodePreRecord::might_be_a_code() const
{
    return
        (find(m_preprocessor_store.begin(), m_preprocessor_store.end(), std::string("#define")) != m_preprocessor_store.end())
        && (!m_identifier_store.empty())
        && (!m_number_store.empty());
}

bool CCodePreRecord::operator==(const CCodePreRecord& rhs) const
{
    return
        boost::tie(m_comment_store, m_preprocessor_store, m_identifier_store, m_number_store)
        ==
        boost::tie(rhs.m_comment_store, rhs.m_preprocessor_store, rhs.m_identifier_store, rhs.m_number_store);
}

std::ostream& codeswamp::operator<<(std::ostream& os, const CCodePreRecord& cpr)
{
    return os << "CCodePreRecord("
              << "m_comment_store: {" << cpr.m_comment_store
              << "}, m_preprocessor_store: {" << cpr.m_preprocessor_store
              << "}, m_identifier_store: {" << cpr.m_identifier_store
              << "}, m_number_store: {" << cpr.m_number_store
              << "})";
}
