#include "organizacao_Pecas.h"
#include <iostream>
#include "structs.h"
#include <algorithm>
#include <fstream>

using namespace std;


//3.1
void vendaManual(seccao* &armazem, int numero_de_seccoes, int &total_de_faturacao,peca *&lista_chegada, int &tamanho_lista_chegada) {
    int id_produto;char id_seccao;
    cout << "Indique a seccao que pretende entrar " << endl;
    cin >> id_seccao;
    cin.clear();
    cout << "Indique o id do produto que pretende vender " << endl;
    cin >> id_produto;
    cin.clear();
    int saiu = 0;
    int i = 0;
    while(i < numero_de_seccoes){ // Loop sobre todas as secções do armazém
        int j = 0;
        while(j < armazem[i].tamanho_da_seccao){ // Loop sobre todas as peças na secção atual
            if( armazem[i].pecas_aqui[j].numero_de_serie == id_produto){ // Verifica se encontrou o produto
                total_de_faturacao +=armazem[i].pecas_aqui[j].preco;
                armazem[i].faturacao_desta_seccao += armazem[i].pecas_aqui[j].preco;
                for(int k= 0; k<tamanho_lista_chegada;k++){
                    if (lista_chegada[k].categoria==armazem[i].pecas_aqui[j].categoria){
                        saiu = 1;
                        armazem[i].pecas_aqui[j]=lista_chegada[k];
                        cout << lista_chegada[k].categoria << endl;
                        apagar_peca(lista_chegada[k]);
                        cout << lista_chegada[k].categoria << endl;
                        ordenar_pecas_existentes(lista_chegada,k, tamanho_lista_chegada);
                        cout << lista_chegada[0].categoria << lista_chegada[1].categoria <<endl;
                        break;
                    }
                }
                if (!saiu){
                    apagar_peca(armazem[i].pecas_aqui[j]);
                    ordenar_pecas_existentes(armazem[i].pecas_aqui,j,armazem[i].quantidade_na_seccao);
                }
                break;
            }
            j++;
        }
        i++;
    }
    cin.clear();
}

//3.2
void promocao(seccao *&armazem,int &numero_de_seccoes,char &id_seccao_desconto,int &duracao,int &desconto) {
    bool seccao_encontrada = false;
    for (int i = 0; i < numero_de_seccoes; i++) {
        if (armazem[i].ID == id_seccao_desconto) {
            armazem[i].foi_aplicado_promocao_na_seccao = true;
            armazem[i].desconto_aqui_aplicado = desconto;
            cout << "ta aqui 1" << endl;
            armazem[i].duracao_aqui= duracao;
            cout << armazem[i].duracao_aqui << endl;
            for (int j = 0; j < armazem[i].quantidade_na_seccao; j++) {
                cout << "ta aqui 2" << endl;
                if (!armazem[i].pecas_aqui[j].foi_aplicado_promocao){
                    cout << armazem[i].pecas_aqui[j].probabilidade_de_ser_vendida << " " <<armazem[i].pecas_aqui[j].preco <<  endl;
                    armazem[i].pecas_aqui[j].preco = (armazem[i].pecas_aqui[j].preco * desconto)/100;
                    armazem[i].pecas_aqui[j].probabilidade_de_ser_vendida += 15;
                    armazem[i].pecas_aqui[j].foi_aplicado_promocao = true;
                    cout << armazem[i].pecas_aqui[j].probabilidade_de_ser_vendida << " " <<armazem[i].pecas_aqui[j].preco <<endl;
                }
            }
            armazem[i].duracao_aqui--;
            seccao_encontrada = true;
            break;
        }
    }
    if (!seccao_encontrada) {
        cout << "A seccao selecionada nao existe!" << endl;
    }
}

//3.3

void reseta_seccao(seccao seccao_do_armazem){
    for (int i = 0; i<seccao_do_armazem.quantidade_na_seccao;i++){
        apagar_peca(seccao_do_armazem.pecas_aqui[i]);
    }
}

void alterar_categoria(seccao *&armazem, int &numero_de_seccoes) {
    cout << "Qual seccao pertende alterar?" << endl;//pergunta ao utilizador qual a seccao que pertende alterar
    char id_local;//variavel para indentificar qual seccao
    cin >> id_local;//valor atribuido
    bool seccao_encontrada = false;//variavel para indicar se foi encontrada seccao ou nao
    for (int i = 0; i < numero_de_seccoes; i++) {//for para percorer seccao do array armazem
        if (armazem[i].ID == id_local) {//if para verificar se a seccao existe
            cout << "Nova categoria para a seccao " << id_local << ": "
                 << endl;//pergunta ao utilizador qual a nova categoria
            string nova_categoria;//variavel para nova categoria
            cin >> nova_categoria;//valor atribuido a variavel
            armazem[i].categoria = nova_categoria;//alterar a categoria
            reseta_seccao(armazem[i]);//chamar a funcao reseta_seccao
            armazem[i].quantidade_na_seccao = 0;//atribuir o tamanho da seccao a 0
            seccao_encontrada = true;//seccao encontrada
            break;
        }
    }
}
//3.4
void adicionar_seccao( int &numero_de_seccoes, seccao *&armazem) {
    char ID;//variavel para ID da seccao
    string categoria;//variavel para categoria
    int capacidade;//variavel para capacidade
    cout<<"ID para nova seccao:"<<endl;//pergunta o ID ao usuario
    cin>>ID;//atribui valor a variavel
    cout<<"categoria para nova seccao:"<<endl;//pergunta a categoria ao usuario
    cin.ignore();//limpar o buffer do cin
    getline(cin, categoria);//atribui valor a variavel
    cout<<"capacidade para nova seccao:"<<endl;//pergunta a capacidade ao usuario
    cin>>capacidade;//atribui valor para variavel
    cin.ignore();//limpar o buffer do cin
    numero_de_seccoes=numero_de_seccoes + 1;//adiciona uma seccao
    seccao *novo_armazem = new seccao[numero_de_seccoes];//cria um novo array
    for(int i =0;i<numero_de_seccoes-1;i++){//for para percorrer o array)
        novo_armazem[i].ID=armazem[i].ID;
        novo_armazem[i].categoria=armazem[i].categoria;
        novo_armazem[i].tamanho_da_seccao=armazem[i].tamanho_da_seccao;
        novo_armazem[i].quantidade_na_seccao=armazem[i].quantidade_na_seccao;
        novo_armazem[i].faturacao_desta_seccao=armazem[i].faturacao_desta_seccao;
        novo_armazem[i].numeros_de_serie_vendidos_aqui=armazem[i].numeros_de_serie_vendidos_aqui;
        novo_armazem[i].pecas_aqui=armazem[i].pecas_aqui;
    }//funçao para copiar o array
    armazem=novo_armazem;//o array armazem torna-se o novo_armazem
    armazem[numero_de_seccoes-1].ID=ID;//atribuir o novo ID para ultima posicao do array
    armazem[numero_de_seccoes-1].categoria=categoria;//atribuir a categoria para ultima posicao do array
    armazem[numero_de_seccoes-1].tamanho_da_seccao=capacidade;//atribuir a capacidade para ultima posicao do array
    armazem[numero_de_seccoes-1].pecas_aqui= new peca[capacidade];//novo array para a seccao
}

//3.5
void gravar_armazem(seccao *&armazem, int &numero_de_seccoes, peca *&lista_chegada, int &tamanho_lista_chegada, int &chamadas_do_menu, int &total_de_faturacao, int *&numeros_saidos, int &tamanho_dos_numeros_saidos){
    string caminho = "armazem.txt";
    ofstream ficheiro(caminho); //serve como output para oque vamos fazer
    //se estiver aberto entao o if executa
    if(ficheiro.is_open()){
        //aqui decidimos fazer o output desta maneira
        ficheiro << chamadas_do_menu << " | ";
        ficheiro << total_de_faturacao << " | ";
        ficheiro << numero_de_seccoes << " | ";

        for (int i = 0; i < tamanho_dos_numeros_saidos; i++) {
            ficheiro << numeros_saidos[i] << " ";
        }
        ficheiro << "| ";
        ficheiro << tamanho_dos_numeros_saidos << " | ";
        for (int i = 0; i < numero_de_seccoes; i++){
            ficheiro << "Seccao: " << armazem[i].ID << " | ";
            ficheiro << "Categoria:"<<armazem[i].categoria << " | ";
            ficheiro << "Capacidade: "<< armazem[i].tamanho_da_seccao << " | ";
            ficheiro << "Quantidade: "<<armazem[i].quantidade_na_seccao << " | ";
            ficheiro << "Faturacao: "<<armazem[i].faturacao_desta_seccao << " | ";

            ficheiro << "Numeros de series aqui vendidos:"<<armazem[i].numeros_de_serie_vendidos_aqui << " \n";

            for (int j = 0; j < armazem[i].quantidade_na_seccao; j++) {
                ficheiro << armazem[i].pecas_aqui[j].preco << " | ";
                ficheiro << armazem[i].pecas_aqui[j].categoria << " | ";
                ficheiro << armazem[i].pecas_aqui[j].probabilidade_de_ser_vendida << " | ";
                ficheiro << armazem[i].pecas_aqui[j].numero_de_serie << " | ";
                ficheiro << armazem[i].pecas_aqui[j].marca << " \n";
            }
        }

        ficheiro << tamanho_lista_chegada << " \n";

        for (int k = 0; k < tamanho_lista_chegada; k++){
            ficheiro << lista_chegada[k].preco << " | ";
            ficheiro << lista_chegada[k].numero_de_serie << " | ";
            ficheiro << lista_chegada[k].marca << " | ";
            ficheiro << lista_chegada[k].probabilidade_de_ser_vendida << " | ";
            ficheiro << lista_chegada[k].categoria<< " \n";
        }
        ficheiro.close();
    }
    else{
        cout << "Erro ao abrir o ficheiro" << endl;
    }
}


//3.7.1
void imprimir_lista_pecas(seccao* seccoes, int numero_seccoes, peca* lista_chegada, int tamanho_lista_chegada) {
    int tamanho_total = 0;
    for (int i = 0; i < numero_seccoes; ++i) {
        tamanho_total += seccoes[i].quantidade_na_seccao;
    }
    tamanho_total += tamanho_lista_chegada;
    peca* todas_pecas = new peca[tamanho_total];
    int index = 0;
    for (int i = 0; i < numero_seccoes; ++i) {
        for (int j = 0; j < seccoes[i].quantidade_na_seccao; ++j) {
            todas_pecas[index++] = seccoes[i].pecas_aqui[j];
        }
    }
    for (int i = 0; i < tamanho_lista_chegada; ++i) {
        todas_pecas[index++] = lista_chegada[i];
    }
    sort(todas_pecas, todas_pecas + tamanho_total, [](const peca& p1, const peca& p2) {
        return p1.marca < p2.marca;
    });
    cout << "Lista de todas as pecas presentes no armazem, seccoes e lista de chegada (por ordem alfabetica da marca):" << endl;
    for (int i = 0; i < tamanho_total; ++i) {
        cout << "- Marca: " << todas_pecas[i].marca << " | Categoria: " << todas_pecas[i].categoria << " | Preco: " << todas_pecas[i].preco << endl;
    }
    delete[] todas_pecas;

}
//3.7.2
void imprimir_lista_pecas_preco(seccao* seccoes, int numero_seccoes, peca* lista_chegada, int tamanho_lista_chegada) {
    int tamanho_total = 0;
    for (int i = 0; i < numero_seccoes; ++i) {
        tamanho_total += seccoes[i].quantidade_na_seccao;
    }
    tamanho_total += tamanho_lista_chegada;
    peca *todas_pecas = new peca[tamanho_total];
    int index = 0;
    for (int i = 0; i < numero_seccoes; ++i) {
        for (int j = 0; j < seccoes[i].quantidade_na_seccao; ++j) {
            todas_pecas[index++] = seccoes[i].pecas_aqui[j];
        }
    }
    for (int i = 0; i < tamanho_lista_chegada; ++i) {
        todas_pecas[index++] = lista_chegada[i];
    }
    sort(todas_pecas, todas_pecas + tamanho_total, [](const peca &p1, const peca &p2) {
        return p1.preco < p2.preco;
    });
    cout << "Lista de todas as pecas presentes no armazem, seccoes e lista de chegada (por precos):" << endl;
    for (int i = 0; i < tamanho_total; ++i) {
        cout << "- Marca: " << todas_pecas[i].marca << " | Categoria: " << todas_pecas[i].categoria << " | Preco: "
             << todas_pecas[i].preco << endl;
    }
    delete[] todas_pecas;
}