#ifndef PALETA_HPP
#define PALETA_HPP
#include "cor.hpp"
#include <vector>
class Paleta {
    public:
        int quantidade;
        std::vector<Cor> Cores;
        std::vector<int> Valores;//100 cores com 100 valores de referencia;
};
#endif
