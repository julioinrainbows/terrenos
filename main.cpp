#include <iostream>
#include "mapa.cpp"
#include "imagem.cpp"
#include "paleta.cpp"

int main(){
    int n;
    cin >> n;

    terreno T1(n);
    T1.gerarTerreno(n,50);
    int t = T1.getTamanho(); 
        
    Paleta paleta;
    imagem img(t, t);

    paleta.definevalues("Paleta.txt");

    for (int i = 0; i < t; i++) {for (int j = 0; j < t; j++) { //loop para cada pixel
        int l = 0;
        for (int k : paleta.Valores) { 
            if (T1.getAltitude(i, j) <= k) {
                img.colorir(i, j, paleta.Cores[l].R, paleta.Cores[l].G, paleta.Cores[l].B);
                break;
            }
            else {l++;}
        }
    }}

    img.criarPPM("imagem.PPM");
}