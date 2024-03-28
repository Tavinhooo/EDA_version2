//es gay
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;


string* ler_ficheiro(const string& nomeFicheiro, int& numero_linhas) {
    ifstream myFile(nomeFicheiro);
    string* linhas = nullptr;
    string line;

    if (!myFile.is_open()) {
        cerr << "Unable to open file" << endl;
    } else {
        while (getline(myFile, line)) {
            numero_linhas++;
        }
        myFile.clear();
        myFile.seekg(0, ios::beg);
        linhas = new string[numero_linhas];
        int i = 0;
        while (getline(myFile, line)) {
            linhas[i++] = line;
        }
        myFile.close();
    }

    return linhas;
}


string chooseRandomLine(const string* lines, int& numero_linhas) {
    int randomIndex = rand() % numero_linhas;
    return lines[randomIndex];
}

string Marca_ou_categoria_aleatoria(const string& nomeFicheiro) {
    int numero_de_linhas = 0;
    string* linhas = ler_ficheiro(nomeFicheiro, numero_de_linhas);
    return chooseRandomLine(linhas,numero_de_linhas);
}
