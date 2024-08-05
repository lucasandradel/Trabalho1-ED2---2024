#include <stdio.h>
#include <stdlib.h>
#include "arvore_rbn.h"

// Contador global para rotações
static int contador_rotacoes = 0;

tipo_no* AlocaNo(int chave) {
    tipo_no* no = (tipo_no*)malloc(sizeof(tipo_no));
    if (no == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        exit(1);
    }
    no->chave = chave;
    no->cor = VERMELHO;
    no->esq = no->dir = no->pai = NULL;
    return no;
}

void rotacaoesq(tipo_no **raiz, tipo_no *x) {
    tipo_no *y = x->dir;
    x->dir = y->esq;
    if (y->esq != NULL)
        y->esq->pai = x;
    y->pai = x->pai;
    if (x->pai == NULL)
        *raiz = y;
    else if (x == x->pai->esq)
        x->pai->esq = y;
    else
        x->pai->dir = y;
    y->esq = x;
    x->pai = y;
    contador_rotacoes++;
}

void rotacaodir(tipo_no **raiz, tipo_no *y) {
    tipo_no *x = y->esq;
    y->esq = x->dir;
    if (x->dir != NULL)
        x->dir->pai = y;
    x->pai = y->pai;
    if (y->pai == NULL)
        *raiz = x;
    else if (y == y->pai->dir)
        y->pai->dir = x;
    else
        y->pai->esq = x;
    x->dir = y;
    y->pai = x;
    contador_rotacoes++;
}

void corrigirInsercao(tipo_no **raiz, tipo_no *z) {
    while (z != *raiz && z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esq) {
            tipo_no *y = z->pai->pai->dir;
            if (y != NULL && y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    rotacaoesq(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaodir(raiz, z->pai->pai);
            }
        } else {
            tipo_no *y = z->pai->pai->esq;
            if (y != NULL && y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    rotacaodir(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotacaoesq(raiz, z->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO;
}

void inserir(tipo_no **raiz, int chave) {
    tipo_no *z = AlocaNo(chave);
    tipo_no *y = NULL;
    tipo_no *x = *raiz;

    while (x != NULL) {
        y = x;
        if (z->chave < x->chave)
            x = x->esq;
        else
            x = x->dir;
    }
    z->pai = y;
    if (y == NULL)
        *raiz = z;
    else if (z->chave < y->chave)
        y->esq = z;
    else
        y->dir = z;

    z->esq = z->dir = NULL;
    z->cor = VERMELHO;
    corrigirInsercao(raiz, z);
}

tipo_no* ler_e_inserir(const char* nome_arquivo, tipo_no* arvore) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        perror("Não foi possível abrir o arquivo");
        return arvore;
    }

    int valor;
    while (fscanf(arquivo, "%d", &valor) != EOF) {
        inserir(&arvore, valor);
    }

    fclose(arquivo);
    return arvore;
}

tipo_no* busca_arv(tipo_no* raiz, int chave, int *comparacoes) {
    (*comparacoes)++;
    if (raiz == NULL || raiz->chave == chave)
        return raiz;

    if (raiz->chave < chave)
        return busca_arv(raiz->dir, chave, comparacoes);

    return busca_arv(raiz->esq, chave, comparacoes);
}

int alturaRB(tipo_no* no) {
    if (no == NULL)
        return -1;
    else {
        int alturaesq = alturaRB(no->esq);
        int alturadir = alturaRB(no->dir);
        return (alturaesq > alturadir ? alturaesq : alturadir) + 1;
    }
}

void percursoEmOrdem(tipo_no *raiz) {
    if (raiz != NULL) {
        percursoEmOrdem(raiz->esq);
        printf("%d \n", raiz->chave);
        percursoEmOrdem(raiz->dir);
    }
}

void liberarArvoreRB(tipo_no *raiz) {
    if (raiz != NULL) {
        liberarArvoreRB(raiz->esq);
        liberarArvoreRB(raiz->dir);
        free(raiz);
    }
}

void imprime(tipo_no* raiz) {
    if (raiz != NULL) {
        imprime(raiz->esq);
        printf("%d (%s) ", raiz->chave, raiz->cor == VERMELHO ? "Vermelho" : "Preto");
        imprime(raiz->dir);
    }
}

int obter_contador_rotacoes() {
    return contador_rotacoes;
}
