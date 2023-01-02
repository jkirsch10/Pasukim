#include <string>
#include <filesystem>

typedef struct {
    std::string sefer;
    int chapter, sverse;
    int everse = 0;
} pasuk;

class PasukFinder {

public:
    // Constructors
    //PasukFinder();
    //PasukFinder(pasuk);
    // Destructors
    //~PasukFinder() = default;

    void setPasuk(pasuk myPasuk);
    void findPasuk();
    


private:
    pasuk m_pasuk;
    std::filesystem::path m_seferPathE;
    std::filesystem::path m_seferPathH;

    void setSeferPath(std::string sefer);

    void readFromFile();

    
    

};