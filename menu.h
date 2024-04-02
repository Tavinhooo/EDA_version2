//
// Created by octav on 17/03/2024.
//

#ifndef PROJETOEDA_MENU_H
#define PROJETOEDA_MENU_H
int menu(seccao *&armazem,int &numero_de_seccoes,peca *&lista_chegada,int &tamanho_lista_chegada,int *&numeros_saidos ,int &tamanho_dos_numeros_saidos, int &total_de_faturacao,int &chamadas_do_menu);
void sub_menu(seccao *&armazem,int numero_de_seccoes,peca *&lista_chegada,int tamanho_lista_chegada,int quantidade_para_adicionar, int *&numeros_saidos,int tamanho_dos_numeros_saidos,int total_de_faturacao,int chamadas_do_menu);

#endif //PROJETOEDA_MENU_H
