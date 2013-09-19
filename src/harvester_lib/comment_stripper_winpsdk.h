#pragma once

#include "harvester_lib.h"
#include <string>

class strip_comment_winpsdk
{
public:
    strip_comment_winpsdk(const std::string& comment);

    operator const std::string&() const
    { return m_stripped_comment; }

private:
    std::string m_stripped_comment;
};
