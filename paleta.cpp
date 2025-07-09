#include "paleta.hpp"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
void Paleta::definevalues(std::string arquivo){
    ifstream text(arquivo);
    string str;
    getline(text, str);
    int quantint = stoi(str);
    quantidade = quantint;
    Cores.resize(quantint);
    Valores.resize(quantint);
    int i = 0;
    while (getline(text, str)) {
        stringstream ss(str);
        vector<string> v;
        string temp;

        while(getline(ss, temp, ' ')) {
            v.push_back(temp);
        }

        Valores[i] = stoi(v[0]);
        Cores[i].R = stoi(v[1]);
        Cores[i].G = stoi(v[2]);
        Cores[i].B = stoi(v[3]);
        i++;
    }
}//b