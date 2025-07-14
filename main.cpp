#include <iostream>
#include "mapa.cpp"

int main(){
    int n;
    string txt, ppm;
    cin >> n >> txt >> ppm;

    terreno T1(n);

    T1.gerarMapa(txt, ppm, n);
}