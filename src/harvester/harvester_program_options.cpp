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
#include "harvester_program_options.h"
#include <iostream>
#include <boost/program_options.hpp>

using namespace codeswamp::harvester;
using namespace std;
using namespace boost;

namespace po = boost::program_options;

COptions::COptions() :
    m_bProgramRunnable(false)
{ }

void COptions::parse_command_line(int ac, const char** av)
{
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("formats", "list source and sink formats")
        ("src", po::value<string>(), "source data file path")
        ("dest", po::value<string>(), "destination, one of stdout, sqlite. If sqlite, follow with database file path, e.g. sqlite:c:\\test.db")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);    

    if (vm.count("help")) 
    {
        cout << desc << "\n";
        return;
    }

    if (vm.count("formats"))
        ShowFormats(true);

    if (vm.count("src"))
        SetSource(vm["src"].as<string>());
    else
        SetSource("C:\\Program Files (x86)\\Microsoft SDKs\\Windows\\8.0CP\\Include\\shared\\WinError.h"); // temporary default

    if (vm.count("dest"))
        SetDest(vm["dest"].as<string>());
    else
        SetDest("sqlite:C:\\codeswamp.sqlite"); // temporary default output

    SetProgramRunnable(HasSource() && HasDest());
}
