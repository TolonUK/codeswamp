#include <code_scanner.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/function.hpp>
#include <make_code_record.h>
#include "harvester_program_options.h"

using namespace std;
using namespace codeswamp;
using namespace codeswamp::harvester;

class MySink : public ICodePreRecordSink
{
public:
    virtual void operator()(const CCodePreRecord& cpr)
    {
        make_code_record mcr(cpr);
        CCodeRecord cr(mcr);

        cout << "========================================" << endl;
        cout << cr << endl;
    }
};

int main(int argc, const char** argv)
{
    cout << "codeswamp harvester, copyright (c) 2013 Alex Paterson (alex@tolon.co.uk)" << endl;
    cout << "------------------------------------------------------------------------" << endl;

    COptions options;
    options.parse_command_line(argc, argv);

    if (options.ListFormats())
    {
        CCodeSourceFactory src_factory;
        CCodeSinkFactory sink_factory;

        cout << "sources:" << endl;
        src_factory.print_members(cout);

        cout << "sinks:" << endl;
        sink_factory.print_members(cout);
    }

    if (options.IsProgramRunnable())
    {
        //! \todo re-enable parsing code
        /*code_scanner cs;
        MySink my_sink;
        ifstream ifs();
        cs.parse(ifs, my_sink);*/
    }
}
