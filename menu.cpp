#include <iostream>
#include "structs.h"
#include "organizacao_Pecas.h"
#include "Funcoes_de_impressao.h"
#include "gestao.h"
#include <fstream>
using namespace std;

int menu(seccao *&armazem,int &numero_de_seccoes,peca *&lista_chegada,int &tamanho_lista_chegada,int *&numeros_saidos ,int &tamanho_dos_numeros_saidos, int &total_de_faturacao,int &chamadas_do_menu);

void sub_menu(seccao *&armazem,int &numero_de_seccoes,peca *&lista_chegada,int &tamanho_lista_chegada,int quantidade_para_adicionar, int *&numeros_saidos,int tamanho_dos_numeros_saidos,int &total_de_faturacao,int &chamadas_do_menu){
    deposito_de_pecas_na_lista_de_chegada(lista_chegada,quantidade_para_adicionar,numero_de_seccoes, armazem,numeros_saidos,tamanho_dos_numeros_saidos,tamanho_lista_chegada);
    remocao_de_peca_para_o_armazem(armazem,lista_chegada,8,numero_de_seccoes,tamanho_lista_chegada);
    vendas(armazem,numero_de_seccoes,total_de_faturacao);
    primeira_impressao(armazem, lista_chegada,numero_de_seccoes,tamanho_lista_chegada,total_de_faturacao);
    chamadas_do_menu++;
    menu(armazem,numero_de_seccoes,lista_chegada,tamanho_lista_chegada,numeros_saidos ,tamanho_dos_numeros_saidos, total_de_faturacao,chamadas_do_menu);
}

int menu(seccao *&armazem,int &numero_de_seccoes,peca *&lista_chegada,int &tamanho_lista_chegada,int *&numeros_saidos ,int &tamanho_dos_numeros_saidos, int &total_de_faturacao,int &chamadas_do_menu) {
    int sair = 0;
    if (chamadas_do_menu == 0) {
        sub_menu(armazem, numero_de_seccoes, lista_chegada, tamanho_lista_chegada, 10, numeros_saidos,
                 tamanho_dos_numeros_saidos, total_de_faturacao, chamadas_do_menu);
    } else {
        char dia_seguinte_ou_gestão;
        cin >> dia_seguinte_ou_gestão;
        cin.clear();

        if (dia_seguinte_ou_gestão == 's') {
            for (int i = 0; i < numero_de_seccoes; i++) {
                if (!armazem[i].foi_aplicado_promocao_na_seccao) {
                    promocao(armazem, numero_de_seccoes, armazem[i].ID, armazem[i].duracao_aqui,armazem[i].desconto_aqui_aplicado);
                    cout << "promocao novamente aplicada" << endl;
                }
            }
            sub_menu(armazem, numero_de_seccoes, lista_chegada, tamanho_lista_chegada, 5, numeros_saidos,
                     tamanho_dos_numeros_saidos, total_de_faturacao, chamadas_do_menu);
            return 0;
        } else if (dia_seguinte_ou_gestão == 'g') {
            cout
                    << "\t*******************************************\n\t***** Armazem EDA | Total Faturacao "<<total_de_faturacao <<" *****\n\t*******************************************";
            int opcao;
            cout << "\n ***** Bem Vindo Gestor *****\n";
            cout << "(1).Venda Manual\n";
            cout << "(2).Promocao\n";
            cout << "(3).Alterar Categoria\n";
            cout << "(4).Adicionar Seccao\n";
            cout << "(5).Gravar Armazem\n";
            cout << "(6).Carregar Armazem\n";
            cout << "(7).Imprimir Armazem por ordem alfabetica da marca da peca\n";
            cout << "(8).Imprimir Armazem por preco\n";
            cout << "(9).Fechar Armazem\n";
            cout << "Selecione a sua opcao:";
            cin >> opcao;
            switch (opcao) {
                case 1:
                    vendaManual(armazem, numero_de_seccoes, total_de_faturacao, lista_chegada, tamanho_lista_chegada);
                    break;
                case 2:
                    char id_seccao_desconto;
                    int desconto;
                    int duracao;
                    cout << "Qual seccao pretende aplicar o desconto?" << endl;
                    cin >> id_seccao_desconto;
                    cout << "Aplicar o desconto" << endl;
                    cin >> desconto;
                    cout << "Qual a duracao do desconto compadre" << endl;
                    cin >> duracao;
                    cin.clear();
                    promocao(armazem, numero_de_seccoes, id_seccao_desconto, duracao, desconto);
                    cout << " logo depois da promocao" << endl;
                    break;
                case 3:
                    alterar_categoria(armazem, numero_de_seccoes);
                    break;
                case 4:
                    adicionar_seccao(numero_de_seccoes, armazem);
                    break;
                case 5:
                    cout << "A gravar...\n"<< endl;
                    gravar_armazem(armazem, numero_de_seccoes, lista_chegada, tamanho_lista_chegada, chamadas_do_menu, total_de_faturacao, numeros_saidos,tamanho_dos_numeros_saidos);
                    cout << "Gravacao completa \n" <<endl;
                    break;
                case 6:
                    cout << "A carregar...\n";
                    break;
                case 7:
                    cout << "A imprimir...\n";
                    imprimir_lista_pecas(armazem, numero_de_seccoes,lista_chegada,tamanho_lista_chegada);
                    break;
                case 8:
                    cout << "A imprimir...\n";
                    imprimir_lista_pecas_preco(armazem, numero_de_seccoes,lista_chegada,tamanho_lista_chegada);
                    break;
                case 9:
                    cout << "A fechar armazem\n";
                    sair = 1;
                    break;
                default:
                    cout << "\nEscolha uma opcao valida\n";
            }
        }
        if (sair){
            cout << "Foi corretamente fechado" << endl;
        }else{
            menu(armazem, numero_de_seccoes, lista_chegada, tamanho_lista_chegada, numeros_saidos,tamanho_dos_numeros_saidos, total_de_faturacao, chamadas_do_menu);
        }
    }
}
