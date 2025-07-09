#include <iostream>
#include <fstream>
using namespace std;

struct pixel{
    short R, G, B;
};

class imagem {
    int altura, largura;
    pixel pixels[256][256];

    public:
        imagem(int a, int l);
        pixel consultar(int x, int y, imagem img);
        void colorir(int x, int y, imagem &img, short R, short G, short B);
        void criarPPM(string arquivo, imagem &img, int a, int l);
};