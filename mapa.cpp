#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include "mapa.hpp"
#include "paleta.cpp"
#include "imagem.cpp"
using namespace std;

terreno::terreno(int n): tamanho(static_cast<int>(pow(2, n)+1)) {
    srand(time(0));
    mapa = new int*[tamanho];

    for (int i = 0; i < tamanho; i++) {
        mapa[i] = new int[tamanho];

        for (int j = 0; j < tamanho; j++) {
            mapa[i][j] = 0;
        }
    }
}
//s d s d
void terreno::gerarTerreno(int maxalt){
    Paleta paleta;
    float rug = maxalt * 0.5;

    mapa[0][0] = rand() % maxalt;
    mapa[0][tamanho-1] = rand() % maxalt;
    mapa[tamanho-1][0] = rand() % maxalt;
    mapa[tamanho-1][tamanho-1] = rand() % maxalt;

    int step = tamanho - 1;
    while(step > 1){
        int half = step/2;

        for(int x = half; x < tamanho-1; x += step){ //diamond step.
            for(int y = half; y < tamanho-1; y+= step){
                int media = (mapa[x-half][y-half] + mapa[x-half][y+half] + mapa[x+half][y-half] + mapa[x+half][y+half])/4;
                int random = ((float)rand() / RAND_MAX) *2*rug - rug;
                mapa[x][y] = media + random;

                if (mapa[x][y] > maxalt) {
                    mapa[x][y] -= mapa[x][y]%maxalt;
                }
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

                if (mapa[x][y] > maxalt) {
                    mapa[x][y] -= mapa[x][y]%maxalt;
                }
            }
        }

    rug /= 2;
    step /= 2;
    }
}

int terreno::getAltitude(int x, int y){
    return mapa[x][y];
}

void terreno::gerarMapa(string arqpal, string arqimg, int dim){
    terreno T1(dim);
    Paleta paleta;
    

    paleta.definevalues(arqpal + ".txt");
    int maxalt = paleta.Valores[paleta.quantidade - 1];
    T1.gerarTerreno(maxalt);
    
    imagem img(tamanho, tamanho);

    for (int i = 0; i < tamanho; i++) {for (int j = 0; j < tamanho; j++) {
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