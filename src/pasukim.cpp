#include <iostream>
#include <cmake_tut_config.h>
#ifdef USE_ADDER
    #include <adder.hpp>
#endif
#include <memory>
#include <signal.h>

void sigsegv_handler(int sig_num, siginfo_t *si, void *arg){
    printf("\nSIGSEGV(%d) at addr %p.\n", sig_num, si->si_addr);
    exit(0);
}


int main (int argc, char* argv[]){

    struct sigaction sa;
    sa.sa_sigaction = sigsegv_handler;
    sa.sa_flags   = SA_SIGINFO;
    sigaction(SIGSEGV, &sa, NULL);

    std::cout << argv[0] << " Version " << cmake_tut_VERSION_MAJOR << "." << cmake_tut_VERSION_MINOR << std::endl;

    // ++++++++++++++++++++++++++++++++++++++++++++++++++






    return 0;
}

