#include <iostream>
#include <vector>
using namespace std;

struct pixel{
    short R, G, B;
};

class imagem {
    int altura, largura;
    pixel pixels[256][256];

    public:
        imagem(int a, int l): altura(a), largura(l) {
            for (int i = 0; i < a; i++) {
                for (int j = 0; j < l; j++) {
                    pixels[i][j].R = 0;
                    pixels[i][j].G = 0;
                    pixels[i][j].B = 0;
                }
            }
        }
        pixel consultar(int x, int y, imagem img) {return img.pixels[x][y];}
        void colorir(int x, int y, imagem img, short Red, short Green, short Blue) {
            img.pixels[x][y].R = Red;
            img.pixels[x][y].G = Green;
            img.pixels[x][y].B = Blue;
        }
};

int main() {
    imagem img1(3, 4);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            img1.colorir(i, j, img1, 255, 255, 255);
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            cout << i << ", " << j << ": " << img1.consultar(i, j, img1).R << " " << img1.consultar(i, j, img1).G << " " << img1.consultar(i, j, img1).B << endl;
        }
    }
}