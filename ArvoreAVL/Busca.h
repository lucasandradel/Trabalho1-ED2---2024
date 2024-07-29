#ifndef __BUSCA_H__
#define __BUSCA_H__

#include "ArvoreAVL.h"

void busca_e_avaliar(tipo_no *raiz, int *chaves, int num_chaves);
int obter_contador_comparacoes();
void selecionar_amostra(int *chaves, int *amostra, int total, int amostra_size);
void mostrar_amostra(int *amostra, int tamanho);


#endif // __BUSCA_H__
