#include <iostream>
#include <fstream>
#include "imagem.hpp"
using namespace std;

imagem::imagem(int a, int l): altura(a), largura(l) {
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            pixels[i][j].R = 0;
            pixels[i][j].G = 0;
            pixels[i][j].B = 0;
        }
    }
}

pixel imagem::consultar(int x, int y, imagem img) {return img.pixels[x][y];}

void imagem::colorir(int x, int y, imagem &img, short R, short G, short B) {
    img.pixels[x][y].R = R;
    img.pixels[x][y].G = G;
    img.pixels[x][y].B = B;
}

void imagem::criarPPM(string arquivo, imagem &img, int a, int l){
    ofstream PPM(arquivo);
    PPM << "P3\n" << a << " " << l << "\n255\n";

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < l; j++) {
            PPM << img.pixels[i][j].R << " " << img.pixels[i][j].G << " " << img.pixels[i][j].B << " ";
        }
        PPM << "\n";
    }

    PPM.close();
}