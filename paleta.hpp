#ifndef PALETA_HPP
#define PALETA_HPP
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Cor{ //Contém os valores RGB de cada cor na paleta.
    int R, G, B;
};

class Paleta { 
    public:
        int quantidade;
        std::vector<Cor> Cores; //Vetor que armazena os valores RGB.
        std::vector<int> Valores; //Vetor que armazena os valores numéricos de referência.
        
        void definevalues(std::string arquivo); //Lê um arquivo .txt e atribui os valores e cores a seus respectivos vetores.
}; //a
#endif
