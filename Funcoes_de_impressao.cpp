#include <iostream>
#include <string>
#include "structs.h"
#define MAX 50

using namespace std;


void primeira_impressao(seccao *&armazem, peca *lista_chegada, int numero_seccoes, int &tamanho_lista_chegada, int &total_de_faturacao){ //imprime o modelo do armazem 
    cout << "\t\t*************************************************\t" << endl;
    cout << "\t\t***** Armazem EDA " << "|" << " Total Faturacao " << total_de_faturacao << " Euros " << "*****\t" << endl;
    cout << "\t\t*************************************************\t" << endl;

    for (int i=0; i < numero_seccoes; i++){ //imprimir as seccoes (ID, capacidade, quantidade e faturacao) enquanto i for menor que o numero de seccoes do armazem
        cout << "Seccao " << armazem[i].ID << " | Categoria " << armazem[i].categoria << " | Capacidade :" << armazem[i].tamanho_da_seccao << " | Quantidade :" << armazem[i].quantidade_na_seccao << " | Faturacao " << armazem[i].faturacao_desta_seccao<< endl;

        for (int j=0; j < armazem[i].quantidade_na_seccao; j++){ // imprimir as pecas dentro da respetiva seccao (marca, categoria, nºserie e preco) enquanto i for menor que a quantidade de pecas dentro de casa seccao
            cout << "\t" << armazem[i].pecas_aqui[j].marca << " | " << armazem[i].pecas_aqui[j].categoria << " | " << armazem[i].pecas_aqui[j].numero_de_serie << " | " << armazem[i].pecas_aqui[j].preco << " Euros" << endl;
        }
    }

    cout << "\t******************************************\t" << endl;
    cout << "\t************ Lista de Chegada ************\t" << endl;

    for (int i=0; i < tamanho_lista_chegada; i++){//imprime as pecas já presentes dentro da lista de chegada (marca, categoria, nºserie e preco) enquanto i for menor que a quantidade de pecas dentro da lista de chegada
        cout << "\t" << lista_chegada[i].categoria << " | " << lista_chegada[i].marca << " | " << lista_chegada[i].numero_de_serie << " | " << lista_chegada[i].preco << " Euros " << endl;
    }

    cout << "Dia (s)eguinte *********** (g)estao" << endl;//dia seguinte (s) e menu gestor (g)
    cout << "Selecione a sua opcao:" << endl;

}

//void aplicar_promocao(seccao *armazem, )
