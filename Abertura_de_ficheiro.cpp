#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;


string* ler_ficheiro(const string& nomeFicheiro, int& numero_linhas) {
    ifstream myFile(nomeFicheiro);
    string* linhas = nullptr;//criacao de um apontador linhas
    string line;//string linha para servir como ajuda

    if (!myFile.is_open()) {//se nao foi possivel abrir
        cerr << "Nao foi possivel a abertura do ficheiro" << endl;
    } else {
        while (getline(myFile, line)) {//ciclo que recebe linhas do ficheiro e posteriormente temos uma variavel que é encrementada(para contar as linhas)
            numero_linhas++;
        }
        myFile.clear();//limpar buffer
        myFile.seekg(0, ios::beg);
        linhas = new string[numero_linhas];
        int i = 0;//index
        while (getline(myFile, line)) {
            linhas[i++] = line;
        }
        myFile.close();//fecho do ficheiro
    }

    return linhas;
}


string chooseRandomLine(const string* lines, int& numero_linhas) {
    int randomIndex = rand() % numero_linhas;//variavel que faz com que seja um numero random atraves do numero de linhas
    return lines[randomIndex];//retoruna a linha "vencedora"
}
/*
 * esta funcao podemos tanto usar o ficheiro marca.txt ou tanto a categorias.txt, pois achamos que assim pouparia nos uma funcao
 */
string Marca_ou_categoria_aleatoria(const string& nomeFicheiro) {
    int numero_de_linhas = 0;//inicializacao da variavel para contar o numero de linhas
    string* linhas = ler_ficheiro(nomeFicheiro, numero_de_linhas);//criacao de um apontador linhas que conta com a quantidade de linhas
    return chooseRandomLine(linhas,numero_de_linhas);//redireciona para criar a outra funcao
}
