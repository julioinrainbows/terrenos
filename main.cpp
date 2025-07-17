#include <iostream>
#include "mapa.hpp"

int main(){
    int n;
    string txt, ppm;
    cin >> n;

    terreno T1(n);
    T1.readTerreno("a.txt");
    std::cout << T1.getAltitude(2,2);
    return 0;
}
