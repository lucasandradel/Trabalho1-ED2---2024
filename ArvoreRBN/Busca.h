#ifndef __BUSCA_H__
#define __BUSCA_H__

#include "arvore_rbn.h"

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
int* ler_numeros_e_selecionar_amostra(const char* nome_arquivo, int *tamanho_amostra);
void mostrar_amostra_e_salvar(int *amostra, int tamanho, const char *nome_arquivo);

#endif // BUSCA_H
