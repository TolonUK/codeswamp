#pragma once

namespace codeswamp { namespace harvester {

class COptions
{
public:
    COptions();
    void parse_command_line(int argc, const char** argv);

    void SetDisplayPrerecord(bool b)
    { m_bDisplayPrerecord = b; }

    bool DisplayPrerecord() const
    { return m_bDisplayPrerecord; }

    void SetProgramRunnable(bool b)
    { m_bProgramRunnable = b; }

    bool IsProgramRunnable() const
    { return m_bProgramRunnable; }

private:
    bool m_bDisplayPrerecord;
    bool m_bProgramRunnable;
};

}} // namespace codeswamp::harvester
