    #include <iostream>
    #include <cstdlib>
    #include <ctime>
    #include <vector>
    #include <cmath>
    #include "mapa.hpp"
    using namespace std;

    terreno::terreno(int n): dimensao(n) {
        srand(time(0));
        mapa.resize(n, vector<int>(n,0));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                mapa[i][j] = 0;
            }
        }
    }
    //s d s d
    void terreno::gerarTerreno(int n, float rug){
        long long tamanho = static_cast<long long>(pow(2,n)+1);
        cout << tamanho << endl;
        srand(time(0));
        std::vector<vector<long long>> mapaalt;

        mapa.resize(tamanho,vector<int>(tamanho));
        mapa[0][0] = rand() % 100;
        mapa[0][n-1] = rand() % 100;
        mapa[n-1][0] = rand() % 100;
        mapa[n-1][n-1] = rand() % 100;

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
                }
            }

        rug /= 2;
        step /= 2;
        }
    }

    int terreno::getAltitude(int x, int y){
    return mapa[x][y];
    }
