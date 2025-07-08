#ifndef PALETA_HPP
#define PALETA_HPP
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Cor{
    int R, G, B;
};

class Paleta {
    public:
        int quantidade;
        std::vector<Cor> Cores;
        std::vector<int> Valores; //100 cores com 100 valores de referencia;
        
        void definevalues(std::string arquivo);
}; //a
#endif
