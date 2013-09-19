#pragma once

#include "harvester_lib.h"
#include <algorithm>
#include <iosfwd>
#include <string>
#include <vector>

namespace codeswamp {

class CCode
{
public:
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
 
    friend std::ostream& operator<<(std::ostream&, const CCode&);

private:
    unsigned __int32 m_raw_code;
    unsigned __int16 m_code;
    unsigned __int16 m_facility;
    unsigned __int16 m_severity;
};

class CCodeRecord
{
public:
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

    friend std::ostream& operator<<(std::ostream&, const CCodeRecord&);

private:
    std::string m_identifier;
    std::string m_comment;
    CCode m_code;
};

class CCodePreRecord
{
public:
    void add_comment(const std::string& s)
    { m_comment_store.push_back(s); }

    void add_preprocessor(const std::string& s)
    { m_preprocessor_store.push_back(s); }

    void add_identifier(const std::string& s)
    { m_identifier_store.push_back(s); }

    void add_number(const std::string& s)
    { m_number_store.push_back(s); }

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

    friend std::ostream& operator<<(std::ostream&, const CCodePreRecord&);

protected:
    std::vector<std::string> m_comment_store;
    std::vector<std::string> m_preprocessor_store;
    std::vector<std::string> m_identifier_store;
    std::vector<std::string> m_number_store;
};

class ICodePreRecordSink
{
public:
    virtual void operator()(const CCodePreRecord&) = 0;
};

class code_scanner
{
public:
    void parse(std::istream&, ICodePreRecordSink&);
};

} // namespace codeswamp