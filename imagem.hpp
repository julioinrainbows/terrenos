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
        imagem(int a, int l);
        pixel consultar(int x, int y);
        void colorir(int x, int y, short R, short G, short B);
        void criarPPM(string arquivo);
        ~imagem();
};
#endif
