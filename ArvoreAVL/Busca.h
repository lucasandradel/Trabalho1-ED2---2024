#ifndef __BUSCA_H__
#define __BUSCA_H__

#include "ArvoreAVL.h"

// Estrutura para armazenar os resultados da busca
typedef struct {
    char nome_arquivo[256];  // Nome do arquivo de entrada
    double tempo_busca;      // Tempo gasto na busca
    int num_comparacoes;     // Número de comparações feitas durante a busca
    int num_rotacoes;        // Número de rotações feitas na árvore AVL
    int altura_arvore;       // Altura da árvore AVL
} Resultado;


int busca_e_avaliar(tipo_no *raiz, int *chaves, int num_chaves);
int obter_contador_comparacoes();
void selecionar_amostra(int *chaves, int *amostra, int total, int amostra_size);
void mostrar_amostra_e_salvar(int *amostra, int tamanho, const char *nome_arquivo);
int* ler_numeros_e_selecionar_amostra(const char *nome_arquivo, int *tamanho_amostra);
void mostrar_resultados(Resultado res);


#endif // __BUSCA_H__
