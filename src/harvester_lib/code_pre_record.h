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
#ifndef CODESWAMP__CODE_PRE_RECORD_H
#define CODESWAMP__CODE_PRE_RECORD_H

#include <iosfwd>
#include <string>
#include <vector>
#include <boost/algorithm/string/trim_all.hpp>

namespace codeswamp {

//! \todo comment this class
class CCodePreRecord
{
public:
    CCodePreRecord()
    { }

    CCodePreRecord(const std::string& c, const std::string& pp, const std::string& i, const std::string& n)
    {
        add_comment(c);
        add_preprocessor(pp);
        add_identifier(i);
        add_number(n);
    }

    void add_comment(const std::string& s)
    { store_if_nontrivial(m_comment_store, s); }

    void add_preprocessor(const std::string& s)
    { store_if_nontrivial(m_preprocessor_store, s); }

    void add_identifier(const std::string& s)
    { store_if_nontrivial(m_identifier_store, s); }

    void add_number(const std::string& s)
    { store_if_nontrivial(m_number_store, s); }

    bool has_non_comment_data() const
    {
        return 
            !m_identifier_store.empty() ||
            !m_preprocessor_store.empty() ||
            !m_number_store.empty();
    }
    
    bool has_preprocessor() const
    { return !m_preprocessor_store.empty(); }

    bool has_identifier() const
    { return !m_identifier_store.empty(); }

    bool might_be_a_code() const;

    std::string first_identifier() const
    { return *m_identifier_store.begin(); }

    void clear()
    {
        m_comment_store.clear();
        m_preprocessor_store.clear();
        m_identifier_store.clear();
        m_number_store.clear();
    }

    template<typename T>
    void copy_comment_store(T& t) const
    { copy(m_comment_store.begin(), m_comment_store.end(), t); }

    template<typename T>
    void copy_identifier_store(T& t) const
    { copy(m_identifier_store.begin(), m_identifier_store.end(), t); }

    template<typename T>
    void copy_number_store(T& t) const
    { copy(m_number_store.begin(), m_number_store.end(), t); }

    const std::vector<std::string>& comment_store() const
    { return m_comment_store; }

    const std::vector<std::string>& preprocessor_store() const
    { return m_preprocessor_store; }

    const std::vector<std::string>& identifier_store() const
    { return m_identifier_store; }

    const std::vector<std::string>& number_store() const
    { return m_number_store; }

    bool operator==(const CCodePreRecord& rhs) const;

    friend std::ostream& operator<<(std::ostream&, const CCodePreRecord&);

private:
    void store_if_nontrivial(std::vector<std::string>& c, const std::string& s)
    {
        if (s.empty())
            return;

        std::string sCopy(boost::algorithm::trim_all_copy(s));
        if (!sCopy.empty())
            c.emplace_back(std::move(sCopy));
    }

    std::vector<std::string> m_comment_store;
    std::vector<std::string> m_preprocessor_store;
    std::vector<std::string> m_identifier_store;
    std::vector<std::string> m_number_store;
};

}

#endif
