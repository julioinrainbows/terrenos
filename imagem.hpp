#ifndef IMAGEM_HPP
#define IMAGEM_HPP
#include <iostream>
#include <fstream>
using namespace std;

struct pixel{
    short R, G, B;
};

class imagem {
    int altura, largura;
    pixel** pixels;

    public:
        imagem(int a, int l); //Construtor da classe imagem.
        pixel consultar(int x, int y); //Retorna os valores RGB de um determinado pixel.
        void colorir(int x, int y, short R, short G, short B); //Modifica os valores RGB de um determinado pixel.
        void criarPPM(string arquivo); //Cria um arquivo PPM baseado nos valores dos pixels definidos previamente na matriz "pixels".
        ~imagem(); //Destrutor da classe imagem
};
#endif
