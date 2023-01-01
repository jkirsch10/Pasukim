#include <iostream>
#include <exception>
#include <pasukim_config.h>
#ifdef USE_ADDER
    #include <adder.hpp>
#endif
#include <memory>
#include <signal.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options; 

void sigsegv_handler(int sig_num, siginfo_t *si, void *arg){
    printf("\nSIGSEGV(%d) at addr %p.\n", sig_num, si->si_addr);
    exit(0);
}


int main (int argc, char* argv[]){

    struct sigaction sa;
    sa.sa_sigaction = sigsegv_handler;
    sa.sa_flags   = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);

    std::cout << argv[0] << "\nWelcome to Pasukim " << pasukim_VERSION_MAJOR << "." << pasukim_VERSION_MINOR << std::endl;

    // Parse arguments
    try {
        po::options_description desc{"Options"};
        desc.add_options()
            ("help,h", "Help screen")
            ("Beresehit,B", "Bereshit");

        po::variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);
        notify(vm);
        if (vm.count("help"))
            std::cout << desc << '\n';
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }


    // ++++++++++++++++++++++++++++++++++++++++++++++++++






    return 0;
}

