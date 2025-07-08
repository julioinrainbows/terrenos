#include <iostream>
#include <fstream>
#include <vector>
#include "paleta.hpp"
int main(){
    Paleta P1;
    P1.definevalues("paleta.txt");
    std::cout << P1.Cores[0].R << std::endl;
    return 0;
}//z
