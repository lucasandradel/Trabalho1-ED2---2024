#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arvore_abb.h"
#include "busca.h"


// Variáveis globais para contagem de comparações
static int contador_comparacoes = 0;

// Função para buscar um valor na árvore e contar comparações
tipo_abb* buscar(tipo_abb *raiz, int chave) {
    if (raiz == NULL) {
        return NULL; // Retorna NULL se o nó atual for vazio
    }

    contador_comparacoes++; // Conta a comparação do nó atual

    // Se a chave procurada for menor que a chave do nó atual, busca na subárvore esquerda
    if (chave < raiz->chave) {
        return buscar(raiz->esq, chave);
    } 
    // Se a chave procurada for maior que a chave do nó atual, busca na subárvore direita
    else if (chave > raiz->chave) {
        return buscar(raiz->dir, chave);
    } 
    // Se a chave procurada for igual à chave do nó atual, valor encontrado
    else {
        return raiz; // Retorna o nó atual se a chave for encontrada
    }
}

// Função para buscar um conjunto de chaves na árvore e medir o tempo e comparações
void busca_e_avaliar(tipo_abb *raiz, int *chaves, int num_chaves) {
    clock_t inicio = clock(); // Marca o tempo de início da busca

    // Realiza a busca para cada chave no conjunto
    for (int i = 0; i < num_chaves; i++) {
        buscar(raiz, chaves[i]); // Busca a chave e conta as comparações
    }

    clock_t fim = clock(); // Marca o tempo de fim da busca
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; // Calcula o tempo decorrido

    // Mostra o tempo total de busca e o número total de comparações realizadas
    printf("Tempo de busca: %f segundos\n", tempo);
    printf("Número total de comparações: %d\n", contador_comparacoes);
}

// Função para obter o número total de comparações realizadas
int obter_contador_comparacoes() {
    return contador_comparacoes; // Retorna o valor do contador de comparações
}

// Função para selecionar uma amostra aleatória de chaves
void selecionar_amostra(int *chaves, int *amostra, int total, int amostra_size) {
    // Inicializa o gerador de números aleatórios com base no tempo atual
    srand(time(NULL));

    // Embaralha o array de chaves para garantir aleatoriedade
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Gera um índice aleatório
        int temp = chaves[i]; // Troca o elemento na posição i com o elemento na posição j
        chaves[i] = chaves[j];
        chaves[j] = temp;//
    }

    // Seleciona os primeiros amostra_size elementos do array embaralhado para a amostra
    for (int i = 0; i < amostra_size; i++) {
        amostra[i] = chaves[i];
    }
}

// Função para mostrar os valores da amostra
void mostrar_amostra(int *amostra, int tamanho) {
    printf("Amostra selecionada: \n"); // Mensagem indicando a amostra selecionada
    // Imprime cada valor da amostra em uma nova linha
    for (int i = 0; i < tamanho; i++) {
        printf("%d\n", amostra[i]);
    }
}
