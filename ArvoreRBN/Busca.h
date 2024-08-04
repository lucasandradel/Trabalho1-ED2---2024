#ifndef BUSCA_H
#define BUSCA_H

#include "arvRBN.h"

typedef struct {
    char nome_arquivo[256];
    double tempo_busca;
    int num_comparacoes;
    int num_rotacoes;
    int altura_arvore;
} Resultado;

tipo_no* buscar_arv(tipo_no *raiz, int chave);
int busca_e_avaliar(tipo_no *raiz, int *chaves, int num_chaves);
int obter_contador_comparacoes();
void mostrar_resultados(Resultado res);

#endif // BUSCA_H
