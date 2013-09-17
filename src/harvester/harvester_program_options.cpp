#include "harvester_program_options.h"
#include <boost/program_options.hpp>

using namespace codeswamp::harvester;
using namespace std;
using namespace boost;

namespace po = boost::program_options;

COptions::COptions() :
    m_bDisplayPrerecord(false),
    m_bProgramRunnable(true)
{ }

void COptions::parse_command_line(int ac, const char** av)
{
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("prerecord", po::value<bool>(), "display pre-records when processing data")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);    

    if (vm.count("help")) 
    {
        SetProgramRunnable(false);
        cout << desc << "\n";
        return;
    }

    if (vm.count("prerecord"))
        SetDisplayPrerecord(vm["prerecord"].as<bool>());
}
