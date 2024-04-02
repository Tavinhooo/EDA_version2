#ifndef PROJETOEDA_GESTAO_H
#define PROJETOEDA_GESTAO_H
#include "structs.h"

void vendaManual(seccao* &armazem, int numero_de_seccoes, int &total_de_faturacao,peca *&lista_chegada, int &tamanho_lista_chegada);
void promocao(seccao *&armazem,int &numero_de_seccoes,char &id_seccao_desconto,int &duracao,int &desconto);
void alterar_categoria(seccao *&armazem, int &numero_de_seccoes);
void adicionar_seccao( int &numero_de_seccoes, seccao *&armazem);
void imprimir_lista_pecas(seccao* seccoes, int numero_seccoes, peca* lista_chegada, int tamanho_lista_chegada);
void imprimir_lista_pecas_preco(seccao* seccoes, int numero_seccoes, peca* lista_chegada, int tamanho_lista_chegada);
void gravar_armazem(seccao *&armazem, int &numero_de_seccoes, peca *&lista_chegada, int &tamanho_lista_chegada, int &chamadas_do_menu, int &total_de_faturacao, int *&numeros_saidos, int &tamanho_dos_numeros_saidos);

#endif //PROJETOEDA_GESTAO_H
