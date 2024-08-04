#ifndef __BUSCA_H__
#define __BUSCA_H__

#include "arvore_abb.h"

void busca_e_avaliar(tipo_abb *raiz, int *chaves, int num_chaves);
int obter_contador_comparacoes();
void selecionar_amostra(int *chaves, int *amostra, int total, int amostra_size);
void mostrar_amostra(int *amostra, int tamanho);
tipo_abb *buscar(tipo_abb *raiz, int chave);


#endif // __BUSCA_H__