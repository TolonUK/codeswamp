#pragma once

#include "code_scanner.h"

namespace codeswamp {

class make_code_record
{
public:
    make_code_record(
        const CCodePreRecord& in);

    operator const CCodeRecord&() const
    { return m_cr; }

private:
    CCodeRecord m_cr;
};

} // namespace codeswamp
