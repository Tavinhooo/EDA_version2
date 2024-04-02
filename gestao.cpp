#include "organizacao_Pecas.h"
#include <iostream>
#include "structs.h"
#include <algorithm>

using namespace std;
//3.1
void vendaManual(seccao* &armazem, int numero_de_seccoes, int &total_de_faturacao,peca *&lista_chegada, int tamanho_lista_chegada) {
    int id_produto;char id_seccao;
    cout << "Indique a seccao que pretende entrar " << endl;
    cin >> id_seccao;
    cout << "Indique o id do produto que pretende vender " << endl;
    cin >> id_produto;
    int saiu = 0;
    int i = 0;
    while(i < numero_de_seccoes){ // Loop sobre todas as secções do armazém
        int j = 0;
        while(j < armazem[i].tamanho_da_seccao){ // Loop sobre todas as peças na secção atual
            if( armazem[i].pecas_aqui[j].numero_de_serie == id_produto){ // Verifica se encontrou o produto
                total_de_faturacao += armazem[i].pecas_aqui[j].preco; //total de faturacao do armazem é adicionado o nova valor vendido
                armazem[i].faturacao_desta_seccao += armazem[i].pecas_aqui[j].preco;//total de faturacao da seccao é adicionado o nova valor vendido
                saiu = 0;
                for(int k= 0; k<tamanho_lista_chegada;k++){
                    if (lista_chegada[k].categoria==armazem[i].pecas_aqui[j].categoria){ //verifica se a peça vendida tem a mesma categoria que uma peça na lista de chegada
                        saiu = 1;
                        armazem[i].pecas_aqui[j]=lista_chegada[k]; //verifica se tem uma peça na lista de chegada igual à peça vendida
                        apagar_peca(lista_chegada[k]);
                        ordenar_pecas_existentes(lista_chegada,k, tamanho_lista_chegada);
                        cout << "entrou neste loop" << endl;
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
    if (!saiu){
        cout << "Id ou seccao nao valida " << endl;
    }
    cin.clear();
}

//3.3

void reseta_seccao(seccao seccao_do_armazem){
    for (int i = 0; i<seccao_do_armazem.quantidade_na_seccao;i++){
        apagar_peca(seccao_do_armazem.pecas_aqui[i]);
    }
}

void alterar_categoria(seccao *&armazem, int &numero_de_seccoes) {
    cout<<"Qual seccao pertende alterar?" << endl;
    char id_local;
    cin >> id_local;
    bool seccao_encontrada = false;
    for (int i = 0; i < numero_de_seccoes; i++) {
        if (armazem[i].ID == id_local) {
            cout << "Nova categoria para a seccao " << id_local << ": " << endl;
            string nova_categoria;
            cin >> nova_categoria;
            armazem[i].categoria = nova_categoria;
            reseta_seccao(armazem[i]);
            armazem[i].quantidade_na_seccao = 0;
            seccao_encontrada = true;
            break;
        }
    }
    if (!seccao_encontrada) {
        cout << "A seccao selecionada nao existe!" << endl;
    }
}
//3.4
void add_seccao( int &numero_de_seccoes, seccao *&armazem) {
    char ID;
    string categoria;
    int capacidade;
    cout<<"ID para nova seccao:"<<endl;
    cin>>ID;
    cout<<"categoria para nova seccao:"<<endl;
    cin.ignore();
    getline(cin, categoria);
    cout<<"capacidade para nova seccao:"<<endl;
    cin>>capacidade;
    cin.ignore();
    numero_de_seccoes=numero_de_seccoes + 1;
    seccao *novo_armazem = new seccao[numero_de_seccoes];
    for(int i =0;i<numero_de_seccoes-1;i++){
        novo_armazem[i].ID=armazem[i].ID;
        novo_armazem[i].categoria=armazem[i].categoria;
        novo_armazem[i].tamanho_da_seccao=armazem[i].tamanho_da_seccao;
        novo_armazem[i].quantidade_na_seccao=armazem[i].quantidade_na_seccao;
        novo_armazem[i].faturacao_desta_seccao=armazem[i].faturacao_desta_seccao;
        novo_armazem[i].numeros_de_serie_vendidos_aqui=armazem[i].numeros_de_serie_vendidos_aqui;
        novo_armazem[i].pecas_aqui=armazem[i].pecas_aqui;
    }
    armazem=novo_armazem;
    armazem[numero_de_seccoes-1].ID=ID;
    armazem[numero_de_seccoes-1].categoria=categoria;
    armazem[numero_de_seccoes-1].tamanho_da_seccao=capacidade;
    armazem[numero_de_seccoes-1].pecas_aqui= new peca[capacidade];
}





































//3.7.1
void imprimir_lista_pecas(seccao* seccoes, int numero_seccoes, peca* lista_chegada, int tamanho_lista_chegada) {
    int tamanho_total = 0;
    for (int i = 0; i < numero_seccoes; ++i) { //loop que percorre todas as secções
        tamanho_total += seccoes[i].quantidade_na_seccao; //adiciona a quantidade de peças em cada secção ao tamanho total
    }
    tamanho_total += tamanho_lista_chegada; //adiciona o tamanho da lista de chegada ao tamanho total
    peca* todas_pecas = new peca[tamanho_total]; //aloca um array dinamico de peça com o tamanho total já calculado
    int i = 0;
    for (int i = 0; i < numero_seccoes; ++i) { //loops responsaveis por copiar todas as peças das secções para o array todas_pecas 
        for (int j = 0; j < seccoes[i].quantidade_na_seccao; ++j) {
            todas_pecas[i++] = seccoes[i].pecas_aqui[j];
        }
    }
    for (int i = 0; i < tamanho_lista_chegada; ++i) { //loop responsavel por copiar todas as peças da lista de chegada para o array todas_pecas
        todas_pecas[i++] = lista_chegada[i];
    }
    sort(todas_pecas, todas_pecas + tamanho_total, [](const peca& p1, const peca& p2) { //as peças são ordenadas por ordem alfabética da marca
        return p1.marca < p2.marca;
    });
    cout << "Lista de todas as pecas presentes no armazem, seccoes e lista de chegada (por ordem alfabetica da marca):" << endl;
    for (int i = 0; i < tamanho_total; ++i) { //loop que permite a impressão de todas as informações de todas as peças presentes no armazem, secções e lista de chegada
        cout << "- Marca: " << todas_pecas[i].marca << " | Categoria: " << todas_pecas[i].categoria << " | Preco: " << todas_pecas[i].preco << endl;
    }
    delete[] todas_pecas; //liberta a memória alocada

}
//3.7.2
void imprimir_lista_pecas_preco(seccao* seccoes, int numero_seccoes, peca* lista_chegada, int tamanho_lista_chegada) {
    int tamanho_total = 0;
    for (int i = 0; i < numero_seccoes; ++i) { //loop que percorre todas as secções
        tamanho_total += seccoes[i].quantidade_na_seccao; //adiciona a quantidade de peças em cada secção ao tamanho total
    }
    tamanho_total += tamanho_lista_chegada; //adiciona o tamanho da lista de chegada ao tamanho total
    peca* todas_pecas = new peca[tamanho_total]; //aloca um array dinamico de peça com o tamanho total já calculado
    int i = 0;
    for (int i = 0; i < numero_seccoes; ++i) { //loops responsaveis por copiar todas as peças das secções para o array todas_pecas 
        for (int j = 0; j < seccoes[i].quantidade_na_seccao; ++j) {
            todas_pecas[i++] = seccoes[i].pecas_aqui[j];
        }
    }
    for (int i = 0; i < tamanho_lista_chegada; ++i) {  //loop responsavel por copiar todas as peças da lista de chegada para o array todas_pecas
        todas_pecas[i++] = lista_chegada[i];
    }
    sort(todas_pecas, todas_pecas + tamanho_total, [](const peca& p1, const peca& p2) { //as peças são ordenadas por preço (do mais barato para o mais caro)
        return p1.preco < p2.preco;
    });
    cout << "Lista de todas as pecas presentes no armazem, seccoes e lista de chegada (por precos):" << endl;
    for (int i = 0; i < tamanho_total; ++i) { //loop que permite a impressão de todas as informações de todas as peças presentes no armazem, secções e lista de chegada
        cout << "- Marca: " << todas_pecas[i].marca << " | Categoria: " << todas_pecas[i].categoria << " | Preco: " << todas_pecas[i].preco << endl;
    }
    delete[] todas_pecas; //liberta a memória alocada 
}
