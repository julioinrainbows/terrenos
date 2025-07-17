#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include "mapa.hpp"
#include "paleta.cpp"
#include "imagem.cpp"
using namespace std;



/**
 * A função para gerar o terreno inicialmente cria uma matriz de acordo com o valor de n inserido, ele cria dinamicamente um vetor de tamanho elementos onde tamanho é dado pela potência entre (2 e n)+1.
 * Depois que o vetor é gerado dentro de um laço todos os pontos são inicializados em 0, isso evitar acessar valores lixo quando fizermos as proximas etapas.
 * @param mapa Cria o vetor dinamicamente que sera utilizado para o mapa de altitudes
 */
terreno::terreno(int n): tamanho(static_cast<int>(pow(2, n)+1)) {
    srand(time(0));
    mapa = new int*[tamanho];

    for (int i = 0; i < tamanho; i++) {
        mapa[i] = new int[tamanho];

        for (int j = 0; j < tamanho; j++) {
            mapa[i][j] = 0;
        }
    }
}



/**      
 * Primeiro atribuimos valores aleatorios para os cantos do mapa de altitudes.
 * @param maxalt Indica o valor maximo que cada ponto do mapa pode assumir, visando o processo de gerar o terreno em PPM.
 * @param step Indica a distância entre os pontos a serem acessados pelos laços e os pontos extremos a eles, half surge dentro do laço para diminuir a cada iteração essa distância a metade.
 * @param half Indica metade da distância entre os valores ja acessados, assim permitindo calcular medias de acordo com os pontos que estão a half unidades de um determinado ponto.
 * Aqui iniciamos o diamond-square pelo diamond step onde se calcula as medias dos extremos e a atribui ao termo central, x = half indica qual linha da matriz o laço inciciara, assim, na primeira iteração o codigo começa a partir da linha central, e a cada interação step é dividido por 2 acessando assim, o termo entre os extremos e o termo central anterior. Ao mesmo tempo, y é acessado no interior por um laço interno, que percorre y = half até a ultima linha, nota-se que a cada iteração do laço externo(while) o numero de valores acessados de x e y é multiplicado por 2 pois dividimos step por 2, assim quando entramos no laço (x = half;x < tamanho; x+step) o laço completa o dobro de interações em relação ao anterior.
 * Dentro do codigo para calcularmos as medias definimos quais são os pontos extremos em relação ao centro de cada interação, por exemplo no primeiro passo temos que x = half, logo os pontos mais externos na primeira linha são [0][tamanho-1], [0][0], [tamanho-1][0], [tamanho-1][tamanho-1] (Os cantos da matriz), calculamos a media e atribuimos ao valor correspondente ao ponto central acrescido de uma rugosidade, o algoritmo da rugosidade se baseia em uma forma de limitar o valor no intervalo 0 a maxalt, assim facilitando a etapa de gerar o PPM da imagem.
 * @param media Calcula o a media dos valores extremos ao centro da interação.
 * @param random Calcula um valor aléatorio para a rugosidade em um intervalo de 0 a maxalt, baseado no parametro maxalt definido pelo usuario.      
 * Ao finalizar a etapa diamond, ou seja, o(s) valor(es) central(is) entre os extremos está definido, iniciamos a etapa square, a qual serve para definir novos valores ao redor do centro do ponto.
 * Nessa segunda parte do algoritmo iniciamos o processo no começo do mapa de altitudes[0][0], o laço finaliza ao alcançarmos o final do mapa [tamanho-1][tamanho-1]. 
 * No interior do laço há outro laço responsavel por acessar cada coluna em relação a linha atual, nessa etapa queremos prencher os valores entre os diamonds(Os centros que definimos no passo anterior), portanto temos que inicializar os centros dos lados dos quadrados definidos no diamond step, para isso devemos preencher os valores dos diamonds de forma intercalada, por exemplo na primeira etapa do square de um mapa 3x3, os valores que devemos preencher na primeira linha estao em posicoes pares de i e j, ja na segunda linha estão em posiçõoes impares, e novamente na terceira estão em posições pares. Ao tirarmos o resto da soma (x+half) por step garantimos que estejamos acessando somente valores pares ou impares do mapa de altitudes dependendo dos valores de x serem pares ou impares, isso é se a linha atual é par então somente preencheremos pontos com i e j pares, o mesmo para valores impares de x 
 * Aplicado isso garantimos que preencheremos valores de modo alternados no mapa de altitudes, assim permitindo gerar novos quadrados, o que é importante para não acessarmos pontos não inicializados na recursão.
 * Para inicializarmos os pontos nesse segundo passo temos que saber quantos pontos adjacentes temos em relação ao ponto que estamos tratando, ele pode ter 3 ou 4 pontos adjacentes que servirão como base para os valores da media a serem tomados, para isso:
 * @param soma Calcula a soma dos valores ja inicializados adjacentes ao ponto.
 * @param count Calcula quantos valores são adjacentes ao ponto.
 * Então a média é tirada por soma/count, e junto de uma rugosidade igual a do diamond step o valor é inicializado ao ponto.
 * Ao final do processo o valor inicializado é convertido para inteiro para evitar possiveis complicações para gerar o PPM do terreno.
 * Terminada o diamond step e o squarestep a rugosidade e step são divididos por 2 e o laço continua enquanto step>1(Até que todos os pontos do mapa de altitudes estejam inicializados.)
 * */
void terreno::gerarTerreno(int maxalt){
    float rug = maxalt * 0.5;

    mapa[0][0] = rand() % maxalt;
    mapa[0][tamanho-1] = rand() % maxalt;
    mapa[tamanho-1][0] = rand() % maxalt;
    mapa[tamanho-1][tamanho-1] = rand() % maxalt;

    int step = tamanho - 1;
    while(step > 1){
        int half = step/2;

        for(int x = half; x < tamanho-1; x += step){ //diamond step.
            for(int y = half; y < tamanho-1; y+= step){
                int media = (mapa[x-half][y-half] + mapa[x-half][y+half] + mapa[x+half][y-half] + mapa[x+half][y+half])/4;
                int random = ((float)rand() / RAND_MAX) *2*rug - rug;
                mapa[x][y] = media + random;

                if (mapa[x][y] > maxalt) {
                    mapa[x][y] -= mapa[x][y]%maxalt;
                }
            }
        }

        for (int x = 0; x < tamanho; x += half) { // squarestep
            for (int y = (x + half) % step; y < tamanho; y += step) {
                int soma = 0;
                int cont = 0;
                if (x - half >= 0) { soma += mapa[x - half][y]; cont++; }
                if (x + half < tamanho) { soma += mapa[x + half][y]; cont++; }
                if (y - half >= 0) { soma += mapa[x][y - half]; cont++; }
                if (y + half < tamanho) { soma += mapa[x][y + half]; cont++; }
                int media = soma / cont;
                float random = ((float)rand() / RAND_MAX) * 2 * rug - rug;
                mapa[x][y] = static_cast<int>(media + random);

                if (mapa[x][y] > maxalt) {
                    mapa[x][y] -= mapa[x][y]%maxalt;
                }
            }
        }

    rug /= 2;
    step /= 2;
    }
}



/**
 * O método retorna o valor numérico atribuido a um determinado ponto a partir de suas coordenadas na matriz "mapa".
 */
int terreno::getAltitude(int x, int y){
    return mapa[x][y];

}



terreno::~terreno(){
    for(int i = 0; i < tamanho; i++){
        delete[] mapa[i];
    }
    delete[] mapa;
}



/**
 * Aqui a função para ler um mapa de altitudes a partir de um arquivo inicialmente desaloca possiveis valores do objeto mapa e então realoca a partir da criação de um novo mapa especifico do objeto(new)
 * Semelhante ao processo de leitura da paleta utilizamos uma string que armazenara o conteudo lido do arquivo e depois o aloca a um vetor, além disso após cada leitura de linha uma variavel é incrementada em 1 unidade, ela representa as dimensões do mapa de altitudes(matriz 2d).
 * @param str Recebe os dados do arquivo.
 * @param i Controle do while.
 * @param tamanhoarq Incrementado a cada leitura de linha, representa as dimensões do mapa a ser gerado.
 * @param vetor Vetor que armazenara os valores lidos do arquivo a partir do stoi.
 * @param temp String temporaria que recebe os dados do stringstream no laço interno.
 * Apos alocados os valores no vetor passamos esses valores para o mapa de altitudes dentro de um for, definindo a cada ciclo do laço externo a quantidade de colunas a partir de um new.
 */
void terreno::readTerreno(std::string arquivoler){
    std::ifstream arquivo(arquivoler);
    std::string str;
    std::vector<vector<int>> vetor;
    int i = 0;
    int tamanhoarq = 0;
    while(getline(arquivo,str)){
        stringstream ss(str);
        std::string temp;
        std::vector<int> linha;
        while(getline(ss,temp,' ')){
            linha.push_back(std::stoi(temp));
        }
        vetor.push_back(linha);
        tamanhoarq++;
    }
        tamanho = vetor.size(); //linhas
        int colunas = vetor.size();
        mapa = new int*[tamanho];
    for (int i = 0; i < tamanho; i++) {
        mapa[i] = new int[colunas];
        for (int j = 0; j < colunas; j++) {
            mapa[i][j] = vetor[i][j];
        }
    }
}



void terreno::gerarMapa(string arqpal, string arqimg, int dim){
    Paleta paleta;
    paleta.definevalues(arqpal + ".txt");
    int maxalt = paleta.Valores[paleta.quantidade - 1];
    gerarTerreno(maxalt);
    
    imagem img(tamanho, tamanho);

    for (int i = 0; i < tamanho; i++) {for (int j = 0; j < tamanho; j++) {
        int l = 0;
        for (int k : paleta.Valores) { 
            if (getAltitude(i, j) <= k) {
                img.colorir(i, j, paleta.Cores[l].R, paleta.Cores[l].G, paleta.Cores[l].B);
                break;
            }
            else {l++;}
        }
        if (i > 0 && j > 0 && getAltitude(i, j) < getAltitude(i-1, j-1)) {
            img.colorir(i, j, floor(img.consultar(i, j).R * 0.5), floor(img.consultar(i, j).G * 0.7), floor(img.consultar(i, j).B * 0.8));
        }
    }}

    img.criarPPM(arqimg + ".ppm");
}



/**
 * Para salvarmos as altitudes do terreno em um arquivo txt a função recebe o nome do arquivo, e então aloca em cada linha as altitudes de cada ponto, similar a uma real matriz de pontos.
 * @param arquivo É a variavel ofstream que encaminha os dados recebidos para o txt que possui o nome do arquivo recebido.
 */
void terreno::saveTerreno(std::string arquivosave){
    std::ofstream arquivo(arquivosave);
    for(int i = 0;i < tamanho; i++){
        for (int j = 0; j < tamanho; j++)
        {
            arquivo << mapa[i][j] << " ";
        }
        arquivo << "\n";
    }
    arquivo.close();
}
