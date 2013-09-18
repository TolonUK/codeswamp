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
