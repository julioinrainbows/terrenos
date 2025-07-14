#ifndef MAPA_HPP
#define MAPA_HPP
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

class terreno{
    int dimensao;
    vector<vector<int>> mapa;
    
    public:
        terreno(int n);
        void gerarTerreno(int n,float rug); 
        int getAltitude(int x, int y);
        int getLinhas(std::vector<vector<int>> mapaterreno);
        int getColunas(std::vector<vector<int>> mapaterreno);
        void saveTerreno(std::string arquivoterreno);
        void readTerreno(std::string arquivoterreno);
        int getTamanho();
        void gerarMapa(string paleta, string imagem, int dim);
};
#endif
