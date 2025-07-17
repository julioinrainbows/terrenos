#include <iostream>
#include "mapa.cpp"

int main() {
    int n;
    std::string txt, ppm;
    std::cin >> n >> ppm >> txt;
    terreno T2(n);
    T2.gerarMapa(ppm,txt,n);
    T2.saveTerreno("b.txt");
    T2.readTerreno("a.txt");
    std::cout << T2.getAltitude(1,1) << endl;
    return 0;
}
