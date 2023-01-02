#include <iostream>
#include <exception>
#include <pasukim_config.h>
#include <memory>
#include <signal.h>
#include <boost/program_options.hpp>

#include <PasukFinder.hpp>


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
            ("Bereshit,B", po::value<std::vector<std::string>>()->multitoken(), "Bereshit");

        po::variables_map vm;
        po::store(parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if (vm.count("Bereshit")) {
            auto bPasuk = vm["Bereshit"].as<std::vector<std::string>>();
            
            int chapter = stoi(bPasuk[0]);
            std::string sverse = bPasuk[1];
            auto delim_it = sverse.find(":");
            pasuk myPasuk;
            PasukFinder myFinder;
            if (delim_it == std::string::npos) {
                myPasuk = {"Bereshit", chapter, stoi(sverse)};
            }
            else {
                int everse = stoi(sverse.substr(delim_it+1,sverse.size()));
                
                sverse = sverse.substr(0,delim_it);
                
                myPasuk = {"Bereshit", chapter, stoi(sverse), everse};
            }

            myFinder.setPasuk(myPasuk);
            myFinder.findPasuk();
            

        }
        if (vm.count("help")){
            std::cout << desc << '\n';
            return 0;
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }


    // ++++++++++++++++++++++++++++++++++++++++++++++++++






    return 0;
}

