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

pixel imagem::consultar(int x, int y) {return pixels[x][y];}

void imagem::colorir(int x, int y, short R, short G, short B) {
    pixels[x][y].R = R;
    pixels[x][y].G = G;
    pixels[x][y].B = B;
}

void imagem::criarPPM(string arquivo){
    ofstream PPM(arquivo);
    PPM << "P3\n" << altura << " " << largura << "\n255\n";

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            PPM << pixels[i][j].R << " " << pixels[i][j].G << " " << pixels[i][j].B << " ";
        }
        PPM << "\n";
    }

    PPM.close();
}
