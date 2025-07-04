#include <iostream>
#include <fstream>
#include <vector>
#include "paleta.hpp"
int main(){
    
    Paleta Cores = {
        2,{{ 255, 0, 0 }, { 0, 255, 0 }},{0,10}
    };

    std::ifstream file("valores.txt");
    unsigned size;
    file >> size; // Pega o primeiro caractere que indica o numero de cores
    std::vector<int> values;
    values.reserve(size*4); // Define 4 espaços para cada cor da paleta. 1 do valor e 3 das quantidades.
    while(true) {
        int value;
        if (!(file >> value)){
            break;
        }
        values.push_back(value);
    }
    Paleta Cores_read{
        int quanti;
        std::vector<Cor> Cores;
        std::vector<int> Valores;//100 cores com 100 valores de referencia;
    };
    Cores_read.quantidade = size;
    for(int i = 1; i < size; i++){
        Cores_read.push_back(values[i]); 
}
