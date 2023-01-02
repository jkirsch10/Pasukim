#include <iostream>
#include "include/PasukFinder.hpp"
#include <fstream>
#include <algorithm>




void PasukFinder::readFromFile() {

    
    std::string chapter = "Chapter " + std::to_string(m_pasuk.chapter);

    std::filesystem::path root = std::filesystem::current_path();
    
    std::ifstream ifsE(root.string() + m_seferPathE.string());
    std::ifstream ifsH(root.string() + m_seferPathH.string());
    std::string line;

    std::cout << root.string() + m_seferPathE.string()<< std::endl;
    std::cout << chapter << std::endl;

    while (ifsE.good()) {
        while (std::getline(ifsE, line)){
            //std::cout << line << std::endl;
            if (line.find(chapter) == std::string::npos) continue;
            
            int verse = 1;
            while (verse <= m_pasuk.sverse){
                std::getline(ifsE, line);
                ++verse;
            }
            std::cout << line << std::endl;
        }
    }

    while (ifsH.good()) {
        while (std::getline(ifsH, line)){
            //std::cout << line << std::endl;
            if (line.find(chapter) == std::string::npos) continue;

            std::cout << line << std::endl;
            int verse = 1;
            while (verse <= m_pasuk.sverse){
                std::getline(ifsH, line);
                ++verse;
            }
            //std::reverse(line.begin(), line.end());
            std::cout << line << std::endl;
        }
    }
    

}

void PasukFinder::setSeferPath(std::string sefer){
    if (sefer == "Bereshit") {
        m_seferPathE = "/src/Tanakh/Bereshit/Koren_translation.txt";
        m_seferPathH = "/src/Tanakh/Bereshit/Nikkudim.txt";
    }
    else if (sefer == "Shemot") {
            std::cout << sefer << "not implemented yet" << std::endl;
            exit(0);
    }
}

void PasukFinder::findPasuk(){

    std::cout << m_pasuk.sefer <<  " " 
              << m_pasuk.chapter << ":" 
              << m_pasuk.sverse;
    if (m_pasuk.everse != 0) {
        std::cout << "-" << m_pasuk.everse;
    } 
    std::cout << std::endl;
    
    PasukFinder::setSeferPath(m_pasuk.sefer);
    PasukFinder::readFromFile();
}

void PasukFinder::setPasuk(pasuk myPasuk){
    m_pasuk = myPasuk;
}