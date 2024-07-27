#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

// Definição da estrutura de um nó da árvore AVL
typedef struct tipo_no {
    int chave;   // Valor armazenado no nó
    int fb;      // Fator de balanceamento do nó
    int h;       // Altura do nó
    struct tipo_no *esq; // Ponteiro para o filho esquerdo
    struct tipo_no *dir; // Ponteiro para o filho direito
} tipo_no;

// Função que retorna o maior de dois inteiros
int maior(int x, int y) {
    return (x > y) ? x : y;
}

// Função que retorna a altura de um nó
int altura_no(tipo_no *no) {
    if (no == NULL) {
        return -1; // Altura de uma árvore vazia é -1
    }
    return no->h; // Altura armazenada no nó
}

// Função que calcula o fator de balanceamento de um nó
int FatorBalanceamento_no(tipo_no *no) {
    return altura_no(no->dir) - altura_no(no->esq);
}

// Função para realizar rotação simples à direita
tipo_no *Rotacao_direita(tipo_no *pt) {
    tipo_no *ptu = pt->esq; // ptu é o filho esquerdo de pt
    pt->esq = ptu->dir;     // Subárvore direita de ptu se torna a subárvore esquerda de pt
    ptu->dir = pt;          // pt se torna o filho direito de ptu
    // Atualizar as alturas após a rotação
    pt->h = maior(altura_no(pt->esq), altura_no(pt->dir)) + 1;
    ptu->h = maior(altura_no(ptu->esq), pt->h) + 1;
    return ptu; // ptu se torna a nova raiz
}

// Função para realizar rotação simples à esquerda
tipo_no *Rotacao_esquerda(tipo_no *pt) {
    tipo_no *ptu = pt->dir; // ptu é o filho direito de pt
    pt->dir = ptu->esq;     // Subárvore esquerda de ptu se torna a subárvore direita de pt
    ptu->esq = pt;          // pt se torna o filho esquerdo de ptu
    // Atualizar as alturas após a rotação
    pt->h = maior(altura_no(pt->esq), altura_no(pt->dir)) + 1;
    ptu->h = maior(altura_no(ptu->dir), pt->h) + 1;
    return ptu; // ptu se torna a nova raiz
}

// Função para realizar rotação dupla à direita
tipo_no *RotacaoDup_direita(tipo_no *pt) {
    pt->esq = Rotacao_esquerda(pt->esq); // Primeiro faz rotação à esquerda no filho esquerdo
    return Rotacao_direita(pt);          // Depois faz rotação à direita no próprio pt
}

// Função para realizar rotação dupla à esquerda
tipo_no *RotacaoDup_esquerda(tipo_no *pt) {
    pt->dir = Rotacao_direita(pt->dir); // Primeiro faz rotação à direita no filho direito
    return Rotacao_esquerda(pt);        // Depois faz rotação à esquerda no próprio pt
}

// Função para inserir um novo nó na árvore AVL
tipo_no *insere(tipo_no *no, int chave) {
    if (no == NULL) {
        // Cria um novo nó se a árvore estiver vazia
        no = (tipo_no *)malloc(sizeof(tipo_no));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
        no->h = 0;  // A altura do nó é 0 porque é uma folha
        no->fb = 0; // Fator de balanceamento inicial é 0
    } else if (chave < no->chave) {
        // Inserir na subárvore esquerda se a chave for menor
        no->esq = insere(no->esq, chave);
    } else if (chave > no->chave) {
        // Inserir na subárvore direita se a chave for maior
        no->dir = insere(no->dir, chave);
    } else {
        printf("Inserção inválida\n");
        return no;
    }

    // Atualizar a altura do nó após a inserção
    no->h = maior(altura_no(no->esq), altura_no(no->dir)) + 1;
    // Atualizar o fator de balanceamento
    no->fb = FatorBalanceamento_no(no);

    // Verificar e corrigir desbalanceamento
    if (no->fb <= -2) { // Subárvore esquerda mais alta
        if (FatorBalanceamento_no(no->esq) <= 0) {
            printf("ROTAÇÃO SIMPLES DIREITA (%d)\n", no->chave);
            no = Rotacao_direita(no);
        } else {
            printf("ROTAÇÃO DUPLA DIREITA (%d)\n", no->chave);
            no = RotacaoDup_direita(no);
        }
    } else if (no->fb >= 2) { // Subárvore direita mais alta
        if (FatorBalanceamento_no(no->dir) >= 0) {
            printf("ROTAÇÃO SIMPLES ESQUERDA (%d)\n", no->chave);
            no = Rotacao_esquerda(no);
        } else {
            printf("ROTAÇÃO DUPLA ESQUERDA (%d)\n", no->chave);
            no = RotacaoDup_esquerda(no);
        }
    }

    return no; // Retorna o novo nó raiz da subárvore
}

// Função para imprimir a árvore com indentação
void imprime(tipo_no *no, int tab) {
    if (no != NULL) {
        tab += 10; // Aumenta o nível de indentação
        imprime(no->dir, tab); // Imprime a subárvore direita
        printf("\n");
        for (int i = 10; i < tab; i++) printf(" ");
        printf("%d (%d)\n", no->chave, no->h); // Imprime o valor do nó e sua altura
        imprime(no->esq, tab + 2); // Imprime a subárvore esquerda
    }
}

int main() {
    tipo_no *arv = NULL;

    // Inserções na árvore AVL
    arv = insere(arv, 50);
    arv = insere(arv, 10);
    arv = insere(arv, 20);
    arv = insere(arv, 30);
    arv = insere(arv, 60);
    arv = insere(arv, 70);
    arv = insere(arv, 90);
    arv = insere(arv, 55);
    arv = insere(arv, 51);

    // Impressão da árvore
    imprime(arv, 0);

    return 0;
}
