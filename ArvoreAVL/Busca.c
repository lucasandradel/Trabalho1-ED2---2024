#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Busca.h"

// Variáveis globais para contagem de comparações
static int contador_comparacoes = 0;

// Função para buscar um valor na árvore e contar comparações
tipo_no* buscar(tipo_no *raiz, int chave) {
    if (raiz == NULL) {
        return NULL; // Retorna NULL se o nó atual for vazio
    }

    contador_comparacoes++; // Conta a comparação do nó atual

    if (chave < raiz->chave) {
        return buscar(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        return buscar(raiz->dir, chave);
    } else {
        return raiz; // Retorna o nó atual se a chave for encontrada
    }
}

// Função para buscar um conjunto de chaves na árvore e medir o tempo e comparações
int busca_e_avaliar(tipo_no *raiz, int *chaves, int num_chaves) {
    contador_comparacoes = 0; // Reinicializa o contador de comparações
    clock_t inicio = clock(); // Marca o tempo de início da busca

    // Realiza a busca para cada chave no conjunto
    for (int i = 0; i < num_chaves; i++) {
        buscar(raiz, chaves[i]); // Busca a chave e conta as comparações
    }

    clock_t fim = clock(); // Marca o tempo de fim da busca
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; // Calcula o tempo decorrido

    //printf("Tempo de busca: %f segundos\n", tempo);
    //printf("Número total de comparações: %d\n", contador_comparacoes);

    return contador_comparacoes; // Retorna o número total de comparações
}

// Função para obter o número total de comparações realizadas
int obter_contador_comparacoes() {
    return contador_comparacoes; // Retorna o valor do contador de comparações
}

// Função para selecionar uma amostra aleatória de chaves
void selecionar_amostra(int *chaves, int *amostra, int total, int amostra_size) {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios com base no tempo atual

    // Embaralha o array de chaves para garantir aleatoriedade
    for (int i = total - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Gera um índice aleatório
        int temp = chaves[i]; // Troca o elemento na posição i com o elemento na posição j
        chaves[i] = chaves[j];
        chaves[j] = temp;
    }

    // Seleciona os primeiros amostra_size elementos do array embaralhado para a amostra
    for (int i = 0; i < amostra_size; i++) {
        amostra[i] = chaves[i];
    }
}

// Função para ler números de um arquivo e selecionar uma amostra
int* ler_numeros_e_selecionar_amostra(const char *nome_arquivo, int *tamanho_amostra) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return NULL;
    }

    int total_numeros = 0;
    int numero;

    // Conta quantos números estão no arquivo
    while (fscanf(arquivo, "%d", &numero) == 1) {
        total_numeros++;
    }
    rewind(arquivo); // Volta o ponteiro do arquivo para o início

    // Aloca memória para armazenar todos os números lidos do arquivo
    int *numeros = (int*)malloc(total_numeros * sizeof(int));
    if (numeros == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        fclose(arquivo);
        return NULL;
    }

    // Lê todos os números do arquivo e armazena no array 'numeros'
    int i = 0;
    while (fscanf(arquivo, "%d", &numero) == 1) {
        numeros[i++] = numero;
    }
    fclose(arquivo);

    // Calcula 20% do total de números para a amostra
    *tamanho_amostra = total_numeros / 5;

    // Aloca memória para armazenar a amostra
    int *amostra = (int*)malloc(*tamanho_amostra * sizeof(int));
    if (amostra == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a amostra.\n");
        free(numeros);
        return NULL;
    }

    // Copia os primeiros 20% dos números para a amostra
    for (int i = 0; i < *tamanho_amostra; i++) {
        amostra[i] = numeros[i];
    }

    // Libera a memória usada para armazenar todos os números
    free(numeros);

    return amostra;
}

// Função para mostrar os valores da amostra e salvar em um arquivo
void mostrar_amostra_e_salvar(int *amostra, int tamanho, const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s para escrita.\n", nome_arquivo);
        return;
    }

    printf("Amostra selecionada: \n");

    // Imprime cada valor da amostra em uma nova linha e grava no arquivo
    for (int i = 0; i < tamanho; i++) {
        printf("%d\n", amostra[i]);
        fprintf(arquivo, "%d\n", amostra[i]);
    }

    fclose(arquivo);
}

// Função para exibir os resultados da busca
void mostrar_resultados(Resultado res) {
    printf("\nResultados para o arquivo %s:\n", res.nome_arquivo);
    printf("Tempo de busca: %.6f segundos\n", res.tempo_busca);
    printf("Número total de comparações: %d\n", res.num_comparacoes);
    printf("Número total de rotações: %d\n", res.num_rotacoes);
    printf("Altura total da árvore: %d\n", res.altura_arvore);
}
