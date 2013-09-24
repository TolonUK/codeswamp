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
#include "code_scanner.h"
#include <contrib/simple_cpp_lexer/error_code_lexer.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace simple_cpp_lexer_spirit;
using namespace codeswamp;
using namespace boost::algorithm;

struct null_action
{
    template <typename T>
    void operator()(T a) const
    { }

    template <typename IteratorT>
    void operator()(IteratorT first, IteratorT last) const
    { }
};

struct standard_action
{
    standard_action(const char* name, ostream& o) : m_name(name), m_out(o) { }

    template <typename T>
    void operator()(T a) const
    {
        m_out << m_name << ": " << a << endl;
    }

    template <typename IteratorT>
    void operator()(IteratorT first, IteratorT last) const
    {
        m_out << m_name << ": ";
        while (first != last)
            m_out << *first++;
        m_out << endl;
    }

private:
    std::string m_name;
    ostream& m_out;
};

class record_action;

struct comment_action
{
    comment_action(record_action& sink) : m_sink(sink) { }

    template <typename IteratorT>
    void operator()(IteratorT first, IteratorT last) const
    {
        string s(first, last);
        m_sink.on_comment(s);
    }

private:
    record_action& m_sink;
};

struct preprocessor_action
{
    preprocessor_action(record_action& sink) : m_sink(sink) { }

    template <typename IteratorT>
    void operator()(IteratorT first, IteratorT last) const
    {
        string s(first, last);
        m_sink.on_preprocessor(s);
    }

private:
    record_action& m_sink;
};

struct identifier_action
{
    identifier_action(record_action& sink) : m_sink(sink) { }

    template <typename IteratorT>
    void operator()(IteratorT first, IteratorT last) const
    {
        string s(first, last);
        m_sink.on_identifier(s);
    }

private:
    record_action& m_sink;
};

struct number_action
{
    number_action(record_action& sink) : m_sink(sink) { }

    template <typename IteratorT>
    void operator()(IteratorT first, IteratorT last) const
    {
        string s(first, last);
        m_sink.on_number(s);
    }

private:
    record_action& m_sink;
};

class trim_input
{
public:
    trim_input(const string& s) :
        m_s(s)
    { trim(m_s); }

    operator const string&()
    { return m_s; }

private:
    string m_s;
};

class record_action
{
public:
    record_action(ICodePreRecordSink& o) : 
        m_out(o),
        m_preprocessor(*this),
        m_comment(*this),
        m_identifier(*this),
        m_number(*this)
    { }

    void on_preprocessor(const string& s)
    {
        if (m_cpr.has_preprocessor())
        {
            commit();
        }

        m_cpr.add_preprocessor(trim_input(s));
    }

    void on_comment(const string& s)
    {
        if (m_cpr.has_non_comment_data())
        {
            commit();
        }
       
        m_cpr.add_comment(trim_input(s));
    }

    void on_identifier(const string& s)
    {
        m_cpr.add_identifier(trim_input(s));
    }

    void on_number(const string& s)
    {
        m_cpr.add_number(trim_input(s));
    }

    void flush()
    { commit(); }

    preprocessor_action& preprocessor()
    { return m_preprocessor; }
    comment_action& comment()
    { return m_comment; }
    identifier_action& identifier()
    { return m_identifier; }
    number_action& number()
    { return m_number; }

    friend ostream& operator<<(ostream& os, const record_action& ra)
    {
        return os 
                << "record_action("
                << "m_cpr := " << ra.m_cpr
                << ")";
    }

private:
    void commit()
    {
        if (m_cpr.might_be_a_code())
            m_out(m_cpr);

        m_cpr.clear();
    }

    ICodePreRecordSink& m_out;

    comment_action m_comment;
    preprocessor_action m_preprocessor;
    identifier_action m_identifier;
    number_action m_number;

    CCodePreRecord m_cpr;
};

struct my_actions
{
    my_actions(ICodePreRecordSink& o) : 
        m_out(o), 
        m_r(o),
        preprocessor(m_r.preprocessor()),
        comment(m_r.comment()),
        identifier(m_r.identifier()),
        number(m_r.number())
    { }

    void flush()
    { m_r.flush(); }

    record_action m_r;

    preprocessor_action& preprocessor;
    comment_action& comment;
    null_action keyword;
    identifier_action& identifier;
    null_action special;
    null_action string;
    null_action literal;
    number_action& number;
    null_action unexpected;

private:
    ICodePreRecordSink& m_out;
};

void code_scanner::parse(istream& in, ICodePreRecordSink& sink)
{
    in.unsetf(ios::skipws); //  Turn off white space skipping on the stream

    vector<char> vec;
    std::copy(
        istream_iterator<char>(in),
        istream_iterator<char>(),
        std::back_inserter(vec));

    // This handles the case where the header input ends without a newline.
    // Without it, the last error code in the header may not be processed.
    vec.push_back('\n');

    vector<char>::const_iterator first = vec.begin();
    vector<char>::const_iterator last = vec.end();

    my_actions actions(sink);
    error_code_lexer_2<my_actions> p(actions);
    parse_info<vector<char>::const_iterator> info =
        ::parse(first, last, p);

    actions.flush();

    if (!info.full)
    {
        throw 1.0;
        //cerr << "parsing error\n";
        //cerr << string(info.stop, last);
    }
}
