#ifndef MAPA_HPP
#define MAPA_HPP
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

class terreno{
    int altura, largura;
    vector<vector<int>> mapa;
    
    public:
        terreno(int a,int l);
        void gerarTerreno(int n,float rug); 
        int getAltitude(int x, int y);
        int getLinhas(std::vector<vector<int>> mapaterreno);
        int getColunas(std::vector<vector<int>> mapaterreno);
        void saveTerreno(std::string arquivoterreno);
        void readTerreno(std::string arquivoterreno);

};
#endif
