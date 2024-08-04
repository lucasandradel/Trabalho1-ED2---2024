#ifndef __ARVORE_ABB_H
#define __ARVORE_ABB_H

#include <time.h> // para funções de rand 
#include <unistd.h>  // para a função sleep 
#include <stdio.h>
#include <stdlib.h>


typedef struct est_abb {
    int valor;
    int chave;
    struct est_abb *esq;
    struct est_abb *dir;
} tipo_abb;

//prototipação de funções
int max(int x, int y);

int altura_no(tipo_abb *no);

tipo_abb *insere(tipo_abb *no, int chave);

int obter_contador_rotacoes();

void imprime(tipo_abb *no);

tipo_abb* ler_e_inserir(const char *nome_arquivo, tipo_abb *arvore);

void busca_e_avaliar(tipo_abb *raiz, int *chaves, int num_chaves);

void selecionar_amostra(int *chaves, int *amostra, int total, int amostra_size);

void mostrar_amostra(int *amostra, int tamanho);

void menu_de_opcoes();


#endif
