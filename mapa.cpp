#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include "mapa.hpp"
#include "paleta.cpp"
#include "imagem.cpp"
using namespace std;

terreno::terreno(int n): dimensao(n) {
    srand(time(0));
    int tamanho = getTamanho();
    mapa.resize(tamanho,vector<int>(tamanho, 0));
}
//s d s d
void terreno::gerarTerreno(int n, float rug){
    int tamanho = getTamanho();

    mapa[0][0] = rand() % 100;
    mapa[0][tamanho-1] = rand() % 100;
    mapa[tamanho-1][0] = rand() % 100;
    mapa[tamanho-1][tamanho-1] = rand() % 100;

    int step = tamanho - 1;
    while(step > 1){
        int half = step/2;

        for(int x = half; x < tamanho-1; x += step){ //diamond step.
            for(int y = half; y < tamanho-1; y+= step){
                int media = (mapa[x-half][y-half] + mapa[x-half][y+half] + mapa[x+half][y-half] + mapa[x+half][y+half])/4;
                int random = ((float)rand() / RAND_MAX) *2*rug - rug;
                mapa[x][y] = media + random;
            }
        }

        for (int x = 0; x < tamanho; x += half) { // squarestep
            for (int y = (x + half) % step; y < tamanho; y += step) {
                int soma = 0;
                int cont = 0;
                if (x - half >= 0) { soma += mapa[x - half][y]; cont++; }
                if (x + half < tamanho) { soma += mapa[x + half][y]; cont++; }
                if (y - half >= 0) { soma += mapa[x][y - half]; cont++; }
                if (y + half < tamanho) { soma += mapa[x][y + half]; cont++; }
                int media = soma / cont;
                float random = ((float)rand() / RAND_MAX) * 2 * rug - rug;
                mapa[x][y] = static_cast<int>(media + random);

                if (mapa[x][y] > 100) {
                    mapa[x][y] -= mapa[x][y]%100;
                }
            }
        }

    rug /= 2;
    step /= 2;
    }
}

int terreno::getTamanho() {
    return static_cast<int>(pow(2, dimensao)+1);
}

int terreno::getAltitude(int x, int y){
    return mapa[x][y];
}

void terreno::gerarMapa(string arqpal, string arqimg, int dim){
    terreno T1(dim);
    T1.gerarTerreno(dim, 80);
    int t = T1.getTamanho(); 
        
    Paleta paleta;
    imagem img(t, t);

    paleta.definevalues(arqpal + ".txt");

    for (int i = 0; i < t; i++) {for (int j = 0; j < t; j++) {
        int l = 0;
        for (int k : paleta.Valores) { 
            if (T1.getAltitude(i, j) <= k) {
                img.colorir(i, j, paleta.Cores[l].R, paleta.Cores[l].G, paleta.Cores[l].B);
                break;
            }
            else {l++;}
        }
        if (i > 0 && j > 0 && T1.getAltitude(i, j) < T1.getAltitude(i-1, j-1)) {
            img.colorir(i, j, floor(img.consultar(i, j).R * 0.5), floor(img.consultar(i, j).G * 0.7), floor(img.consultar(i, j).B * 0.8));
        }
    }}

    img.criarPPM(arqimg + ".ppm");
}