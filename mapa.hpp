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
        terreno(int n); //Construtor da classe terreno
        void gerarTerreno(int maxalt); 
        int getAltitude(int x, int y);
        ~terreno(); //Destrutor da classe terreno
        void saveTerreno(string imagem);
        void readTerreno(string imagem);
        void gerarMapa(string paleta, string imagem, int dim); //Cria uma imagem a partir do mapa de altitudes e dos valores definidos na paleta.
};
#endif
