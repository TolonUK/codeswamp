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
#ifndef CODESWAMP__HARVESTER_PROGRAM_OPTIONS_H
#define CODESWAMP__HARVESTER_PROGRAM_OPTIONS_H

#include <string>

namespace codeswamp { namespace harvester {

class COptions
{
public:
    COptions();
    void parse_command_line(int argc, const char** argv);

    void SetProgramRunnable(bool b)
    { m_bProgramRunnable = b; }

    bool IsProgramRunnable() const
    { return m_bProgramRunnable; }

    void SetSource(const std::string& s)
    { m_source = s; }

    bool HasSource() const
    { return !m_source.empty(); }

    void SetDest(const std::string& s)
    { m_dest = s; }

    bool HasDest() const
    { return !m_dest.empty(); }

    void ShowFormats(bool b)
    { m_bShowFormats = b; }

    bool ShowFormats() const
    { return m_bShowFormats; }

private:
    bool m_bProgramRunnable;
    bool m_bShowFormats;
    std::string m_source;
    std::string m_dest;
};

}} // namespace codeswamp::harvester

#endif
