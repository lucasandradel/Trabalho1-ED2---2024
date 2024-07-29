#ifndef __ARVORE_AVL_H__
#define __ARVORE_AVL_H__

#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da árvore AVL
typedef struct tipo_no {
    int chave;   // Valor armazenado no nó
    int fb;      // Fator de balanceamento do nó
    int h;       // Altura do nó
    struct tipo_no *esq; // Ponteiro para o filho esquerdo
    struct tipo_no *dir; // Ponteiro para o filho direito
} tipo_no;

// Prototipagem das funções
int maior(int x, int y);
int altura_no(tipo_no *no);
int FatorBalanceamento_no(tipo_no *no);
tipo_no *Rotacao_direita(tipo_no *pt);
tipo_no *Rotacao_esquerda(tipo_no *pt);
tipo_no *RotacaoDup_direita(tipo_no *pt);
tipo_no *RotacaoDup_esquerda(tipo_no *pt);
tipo_no *insere(tipo_no *no, int chave);
void imprime(tipo_no *no);
tipo_no* ler_e_inserir(const char *nome_arquivo, tipo_no *raiz);
int obter_contador_rotacoes();

#endif // __ARVORE_AVL_H__
