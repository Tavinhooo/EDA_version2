#include "organizacao_Pecas.h"
#include <iostream>
#include <cstdlib>
#include "structs.h"
#include "Abertura_de_ficheiro.h"
#include <algorithm>
#define MAX 50
using namespace std;

bool serie_existe(int *numeros_de_series_ja_saidos, int &numero_da_serie) { 
    for (int i = 0; numeros_de_series_ja_saidos[i] != 0; i++) { //loop sobre todos os números já saídos diferentes de 0 
        if (numeros_de_series_ja_saidos[i] == numero_da_serie) { //verifica se o número de série é igual a um número de série que já saiu
            return true; //se tal se verificar, retorna verdadeiro 
        }
    }
    return false; //caso contrário retorna falso
}
int criar_serie(int *numeros_de_series_ja_saidos, int &tamanho) {
    int numero_da_serie = (rand() % 9000) + 1000;//gera um número aleatório entre 1000 e 9999
    while (serie_existe(numeros_de_series_ja_saidos, numero_da_serie)) {  //loop que verifica se o número de série já saiu
        numero_da_serie = (rand() % 9000) + 1000; //caso já exista, gera outro número aleatório 
    }
    tamanho++;
    numeros_de_series_ja_saidos[tamanho-1] = numero_da_serie;  //adiciona o novo número de série à ultima posição do array
    return numeros_de_series_ja_saidos[tamanho-1]; //retorna o último número de série adicionado ao array
}
int preco_peca (){ //gera o preço da peça 
    return ((rand()%179) + 2) * 5; //gera um número aleatório entre 10-900 e limita esse número entre 0 e 178; adiciona 2, deslocando o intervalo de 2-180; multiplica por 5 para dar multiplos de 5, entre 10 e 900 
}
int atribuicao_de_probabilade() {
    int probabilidade = rand() % 46 + 5; // [0,45] -> [5,50]
    return probabilidade;
}
peca criarPeca_de_categoria_seccao(int numeros_de_series_ja_saidos[], int &tamanho, string categoria_da_seccao) {
    peca novaPeca;
    novaPeca.categoria = categoria_da_seccao;
    novaPeca.marca = Marca_ou_categoria_aleatoria("marcas.txt");
    novaPeca.preco = preco_peca ();
    novaPeca.numero_de_serie = criar_serie(numeros_de_series_ja_saidos,tamanho);
    novaPeca.probabilidade_de_ser_vendida = atribuicao_de_probabilade();
    return novaPeca;
}

int existe_categoria(peca *lista_chegada,int &tamanho_da_lista_de_chegada,peca peca_criada){
    int tamanho_auxiliar = tamanho_da_lista_de_chegada;
    for(; tamanho_auxiliar>0;tamanho_auxiliar--){
        if (lista_chegada[tamanho_auxiliar-1].categoria == peca_criada.categoria){
            return tamanho_auxiliar;
        }
    }
    return -1;
}
void inserir_peca_ordenada(peca *&lista_chegada,int &tamanho_da_lista_de_chegada,peca peca_criada,int n_peca){
    peca *auxiliar = new peca[MAX];
    //copiar informacao de array anterior até à nova peca
    for(int index = 0;index< n_peca;index++){
        auxiliar[index] = lista_chegada[index];
    }
    auxiliar[n_peca] = peca_criada;
    for(int j = n_peca+1;j<=tamanho_da_lista_de_chegada;j++){
        auxiliar[j] = lista_chegada[j-1];
    }
    for(int i = 0; i<= tamanho_da_lista_de_chegada;i++){
        lista_chegada[i] = auxiliar[i];
    }
    delete[] auxiliar;
}
void deposito_de_pecas_na_lista_de_chegada(peca *&lista_chegada,int quantidade_de_pecas, int &numero_de_seccoes, seccao *&armazem,int* &numeros_saidos,int &tamanho_dos_numeros_saidos,int &tamanho_da_lista_de_chegada){
    for (int index = 0; index < quantidade_de_pecas; index++){
        int a = rand()%numero_de_seccoes;
        peca peca_criada = criarPeca_de_categoria_seccao(numeros_saidos,tamanho_dos_numeros_saidos,armazem[a].categoria);
        int n_peca = existe_categoria(lista_chegada,tamanho_da_lista_de_chegada,peca_criada);
        if (n_peca== -1 || tamanho_da_lista_de_chegada==0){
            lista_chegada[tamanho_da_lista_de_chegada]= peca_criada;
        }else{
            inserir_peca_ordenada(lista_chegada,tamanho_da_lista_de_chegada,peca_criada,n_peca);
        }
        tamanho_da_lista_de_chegada++;
    }
}
bool foi_vendido_ou_nao(int probabilidade){
    bool foi_vendido_ou_nao = (probabilidade >= rand()%101);
    return foi_vendido_ou_nao;
}
void apagar_peca(peca &uma_peca){
    uma_peca.preco = 0;
    uma_peca.probabilidade_de_ser_vendida = 0;
    uma_peca.categoria = "";
    uma_peca.marca = "";
    uma_peca.numero_de_serie = 0;
}
void ordenar_pecas_existentes(peca *&lista_de_pecas,int indice, int &quantidade_da_seccao){
    for(;indice< quantidade_da_seccao-1; indice++){
        lista_de_pecas[indice] = lista_de_pecas[indice+1];
    }
    quantidade_da_seccao--;
}

void vendas(seccao *armazem,int numero_de_seccoes, int &total_de_faturacao){
    for (int index = 0; index< numero_de_seccoes;index++){
        //entrou na seccao
        for (int j = 0; j <armazem[index].quantidade_na_seccao; j++){
            //entrou na lista de pecas
            if(foi_vendido_ou_nao(armazem[index].pecas_aqui[j].probabilidade_de_ser_vendida)){
                //foi vendido
                total_de_faturacao += armazem[index].pecas_aqui[j].preco;
                int auxiliar_n_serie = armazem[index].tamanho_numeros_de_serie_vendidos_aqui;
                armazem[index].numeros_de_serie_vendidos_aqui[auxiliar_n_serie] = armazem[index].pecas_aqui[j].numero_de_serie;
                armazem[index].tamanho_numeros_de_serie_vendidos_aqui++;
                armazem[index].faturacao_desta_seccao += armazem[index].pecas_aqui[j].preco;
                apagar_peca(armazem[index].pecas_aqui[j]);
                ordenar_pecas_existentes(armazem[index].pecas_aqui,j,armazem[index].quantidade_na_seccao);

            }
        }
    }
}
void remocao_de_peca_para_o_armazem(seccao *&armazem,peca *&lista_de_pecas,int n_de_pecas_para_entrar,int numero_de_seccoes, int &tamanho_lista_chegada){
    for(int i= 0; i<n_de_pecas_para_entrar;i++){
        for(int j = 0; j<numero_de_seccoes;j++){
            if(lista_de_pecas[i].categoria == armazem[j].categoria && armazem[j].quantidade_na_seccao<armazem[j].tamanho_da_seccao){
                int quantidade_aqui = armazem[j].quantidade_na_seccao;
                armazem[j].pecas_aqui[quantidade_aqui] = lista_de_pecas[i];
                armazem[j].quantidade_na_seccao++;
                apagar_peca(lista_de_pecas[i]);
                ordenar_pecas_existentes(lista_de_pecas,i, tamanho_lista_chegada);
                i--;
                n_de_pecas_para_entrar--;
                break;
            }
        }
    }
}