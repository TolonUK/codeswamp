#include "code_scanner.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/function.hpp>
#include "make_code_record.h"
#include "harvester_program_options.h"

using namespace std;
using namespace codeswamp;
using namespace codeswamp::harvester;

static COptions s_options;

class MySink : public ICodePreRecordSink
{
public:
    virtual void operator()(const CCodePreRecord& cpr)
    {
        make_code_record mcr(cpr);
        CCodeRecord cr(mcr);

        cout << "========================================" << endl;
        if (s_options.DisplayPrerecord())
        {
            cout << cpr << endl;
            cout << "----------------------------------------" << endl;
        }
        cout << cr << endl;
    }
};

int main(int argc, const char** argv)
{
    s_options.parse_command_line(argc, argv);

    if (s_options.IsProgramRunnable())
    {
        code_scanner cs;
        MySink my_sink;
        //ifstream ifs("C:\\Program Files (x86)\\Microsoft SDKs\\Windows\\8.0CP\\Include\\shared\\WinError.h");
        ifstream ifs("C:\\Users\\alex paterson\\Documents\\GitHub\\codeswamp\\data\\sample.h");
        //ifstream ifs("C:\\Users\\alex paterson\\Documents\\GitHub\\codeswamp\\data\\newline_end.h");
        cs.parse(ifs, my_sink);
    }
}
