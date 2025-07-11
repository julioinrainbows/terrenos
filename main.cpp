    #include <iostream>
    #include <cstdlib>
    #include <ctime>
    #include <vector>
    #include <cmath>
    #include "mapa.hpp"

    int main(){
        terreno T1(0,0);
        T1.gerarTerreno(9,0);
        std::cout << T1.getAltitude(3,3);
    }
