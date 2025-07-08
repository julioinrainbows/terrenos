#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct Cor{
    int R, G, B;
};

class Paleta {
    public:
        int quantidade;
        std::vector<Cor> Cores;
        std::vector<int> Valores; //100 cores com 100 valores de referencia;
        
        void definevalues() {
            ifstream text ("Paleta.txt");
            string str;
            getline(text, str);
            int quantint = stoi(str);
    
            Paleta P1;
            P1.quantidade = quantint;
            P1.Cores.resize(quantint);
            P1.Valores.resize(quantint);

            int i = 0;
            while (getline(text, str)) {
                stringstream ss(str);
                vector<string> v;
                string temp;

                while(getline(ss, temp, ' ')) {
                    v.push_back(temp);
                }

                P1.Valores[i] = stoi(v[0]);
                P1.Cores[i].R = stoi(v[1]);
                P1.Cores[i].G = stoi(v[2]);
                P1.Cores[i].B = stoi(v[3]);
                i++;
            }
        }
};
