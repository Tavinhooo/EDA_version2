//
// Created by octav on 08/03/2024.
//

#ifndef PROJETOEDA_STRUCTS_H
#define PROJETOEDA_STRUCTS_H
#include <string>
#include <stdlib.h>

using namespace std;

struct peca {
    string categoria;
    string marca;
    float preco;
    int numero_de_serie;
    int probabilidade_de_ser_vendida;
    bool foi_aplicado_promocao = false;
};
struct seccao {
    string categoria;
    char ID;
    int tamanho_da_seccao;
    peca *pecas_aqui;
    int quantidade_na_seccao = 0;
    int faturacao_desta_seccao = 0;
    int tamanho_numeros_de_serie_vendidos_aqui = 0;
    int *numeros_de_serie_vendidos_aqui = new int[100];
    bool foi_aplicado_promocao_na_seccao = false;
    int desconto_aqui_aplicado = 0;
    int duracao_aqui = 0;
};
#endif //PROJETOEDA_STRUCTS_H
