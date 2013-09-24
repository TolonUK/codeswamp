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
#include "comment_stripper_winpsdk.h"
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

string strip_comment(const string& comment)
{
    string s(comment);

    // replace "//" with ""
    boost::erase_all(s, "//");

    // trim whitespace at either end (incl. newlines)
    boost::trim(s);

    // Where a comment spans multiple lines and one of those lines is empty,
    // without even a comment marker, then reduce the comment string to just
    // the text after the last blank line.
    {
        auto iLastBlankLine = boost::find_last(s, "\n\n");

        if (iLastBlankLine.end() != s.end())
        {
            string sLastComment(iLastBlankLine.end(), s.end());
            if (!sLastComment.empty())
                s.swap(sLastComment);
        }
    }

    // Find the MessageText: bit and grab the text after it.
    // If we can't find MessageText:, don't bother stripping.
    {
        auto iMsgTextMarker = boost::ifind_first(s, "messagetext:");

        if (iMsgTextMarker.end() != s.end())
        {
            string sMsgText(iMsgTextMarker.end(), s.end());
            if (!sMsgText.empty())
                s.swap(sMsgText);
        }
    }

    // trim whitespace at either end (incl. newlines)
    boost::trim(s);
    
    return s;
}

strip_comment_winpsdk::strip_comment_winpsdk(const string& comment) :
    m_stripped_comment(strip_comment(comment))
{ }
