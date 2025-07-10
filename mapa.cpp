#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;



class terreno{
    int altura, largura;
    vector<vector<int>> mapa;

    public:
        terreno(int a, int l): altura(a), largura(l) {
            srand(time(0));

            for(int i = 0; i < altura; i++) {
                for(int j = 0; j < largura; j++) {
                    mapa[i][j] = 0;
                }
            }
        }

        void gerarTerreno(int max){
            if (mapa[0][0] == 0) {
                mapa[0][0] = rand() % max;
                mapa[0][largura - 1] = rand() % max;
                mapa[altura - 1][0] = rand() % max;
                mapa[altura - 1][largura - 1] = rand() % max;
            }

            
        }

};
