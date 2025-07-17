#ifndef MAPA_HPP
#define MAPA_HPP
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

class terreno{
    int tamanho;
    int** mapa;
    
    public:
        
        terreno(int n);
        void gerarTerreno(int maxalt); 
        int getAltitude(int x, int y);
        void desalocarTerreno();
        void saveTerreno(string imagem);
        void readTerreno(string imagem);
        void gerarMapa(string paleta, string imagem, int dim);
};
#endif
