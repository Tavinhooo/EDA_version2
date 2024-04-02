#include <iostream>
#include <cstdlib>
#include <ctime>
#include "structs.h"
#include <algorithm>
#include "menu.h"
#include "seccoes.h"
#include "organizacao_Pecas.h"
#include "Funcoes_de_impressao.h"
#define MAX_NUM 1000
#define MAX 50


using namespace std;
int main() {
    srand(time(0)); //
    int numero_de_seccoes = 0 , tamanho_dos_numeros_saidos = 0, tamanho_lista_chegada = 0,total_de_faturacao = 0;
    static int chamadas_do_menu = 0; //quantas chamadas do menu existiram
    criacao_de_numero_de_seccoes(numero_de_seccoes);
    seccao *armazem = new seccao[numero_de_seccoes];
    criar_seccao(numero_de_seccoes,armazem);
    int *numeros_saidos = new int[MAX_NUM];
    peca *lista_chegada= new peca[MAX];
    menu(armazem,numero_de_seccoes,lista_chegada,tamanho_lista_chegada,numeros_saidos ,tamanho_dos_numeros_saidos, total_de_faturacao,chamadas_do_menu);
    delete[] lista_chegada;
    delete[] armazem;
    delete[] numeros_saidos;
    return 0;
}






    /*for(int i = 0; i< 50; i++){
        if (!lista_chegada[i].marca.empty()){
            cout << lista_chegada[i].marca << endl;
        }
    }

    int tamanho_lista_chegada;
    tamanho_lista_chegada = calcula_tamanho(lista_chegada, tamanho_lista_chegada);
    ordenarPorMarca(lista_chegada, tamanho_lista_chegada);
    cout << lista_chegada[0].categoria << endl;
    cout << "A Lista de chegada e esta: " << endl;
    for (int index = 0; index < tamanho_lista_chegada; index++) {
        cout << "A Peca " << index+1 << " e da Categoria: " << lista_chegada[index].categoria << " e a Marca: "
             << lista_chegada[index].marca << endl;
    }
    peca lista_chegada[MAX];
    for (int index = 0; index < 10; index++) {
        lista_chegada[index] = criarPeca(numeros_saidos, tamanho);
    }
    int tamanho_lista_chegada;
    tamanho_lista_chegada = calcula_tamanho(lista_chegada, tamanho_lista_chegada);
    ordenarPorMarca(lista_chegada, tamanho_lista_chegada);
    cout << "A Lista de chegada e esta: " << endl;
    for (int index = 1; index < tamanho_lista_chegada; index++) {
        cout << "A Peca " << index << " e da Categoria: " << lista_chegada[index].categoria << " e a Marca: "
             << lista_chegada[index].marca << endl;
    }*/