#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Busca.h"

// Variáveis globais para contagem de comparações
static int contador_comparacoes = 0;

// Função para buscar_arv um valor na árvore e contar comparações
tipo_no* buscar_arv(tipo_no *raiz, int chave) {
    if (raiz == NULL) {// Se raiz for nula
        return NULL; // Retorna NULL se o nó atual for vazio
    }

    contador_comparacoes++; // Conta a comparação do nó atual

    // Se a chave procurada for menor que a chave do nó atual, busca na subárvore esquerda
    if (chave < raiz->chave) {
        return buscar_arv(raiz->esq, chave);
    } 
    // Se a chave procurada for maior que a chave do nó atual, busca na subárvore direita
    else if (chave > raiz->chave) {
        return buscar_arv(raiz->dir, chave);
    } 
    // Se a chave procurada for igual à chave do nó atual, valor encontrado
    else {
        return raiz; // Retorna o nó atual se a chave for encontrada
    }
}

// Função para buscar_arv um conjunto de chaves na árvore e medir o tempo e comparações
int busca_e_avaliar(tipo_no *raiz, int *chaves, int num_chaves) {
    clock_t inicio = clock(); // Marca o tempo de início da busca

    // Realiza a busca para cada chave no conjunto
    for (int i = 0; i < num_chaves; i++) {
        buscar_arv(raiz, chaves[i]); // Busca a chave e conta as comparações
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

// Função para ler números de um arquivo e selecionar uma amostra
int* ler_numeros_e_selecionar_amostra(const char *nome_arquivo, int *tamanho_amostra) {
    // Abre o arquivo no modo de leitura
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        // Se não conseguir abrir o arquivo, mostra uma mensagem de erro e retorna NULL
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return NULL;
    }

    int total_numeros = 0; // Variável para contar o total de números no arquivo
    int numero; // Variável para ler cada número do arquivo

    // Conta quantos números estão no arquivo
    while (fscanf(arquivo, "%d", &numero) == 1) {
        total_numeros++; // Incrementa o contador para cada número lido
    }
    rewind(arquivo); // Volta o ponteiro do arquivo para o início

    // Aloca memória para armazenar todos os números lidos do arquivo
    int *numeros = (int*)malloc(total_numeros * sizeof(int));
    if (numeros == NULL) {
        // Se não conseguir alocar memória, mostra uma mensagem de erro, fecha o arquivo e retorna NULL
        fprintf(stderr, "Erro ao alocar memória.\n");
        fclose(arquivo);
        return NULL;
    }

    // Lê todos os números do arquivo e armazena no array 'numeros'
    int i = 0;
    while (fscanf(arquivo, "%d", &numero) == 1) {
        numeros[i++] = numero; // Armazena cada número no array
    }
    fclose(arquivo); // Fecha o arquivo após ler todos os números

    

    // Calcula 20% do total de números para a amostra
    *tamanho_amostra = total_numeros / 5;

    // Aloca memória para armazenar a amostra
    int *amostra = (int*)malloc(*tamanho_amostra * sizeof(int));
    if (amostra == NULL) {
        // Se não conseguir alocar memória para a amostra, mostra uma mensagem de erro, libera a memória usada e retorna NULL
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

    // Retorna a amostra selecionada
    return amostra;
}

// Função para mostrar os valores da amostra e salvar em um arquivo
void mostrar_amostra_e_salvar(int *amostra, int tamanho, const char *nome_arquivo) {
    // Abre o arquivo para escrita
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        // Se não conseguir abrir o arquivo, mostra uma mensagem de erro e retorna
        fprintf(stderr, "Erro ao abrir o arquivo %s para escrita.\n", nome_arquivo);
        return;
    }

    // Mensagem indicando a amostra selecionada
    printf("Amostra selecionada: \n");

    // Imprime cada valor da amostra em uma nova linha e grava no arquivo
    for (int i = 0; i < tamanho; i++) {
        printf("%d\n", amostra[i]);         // Imprime no console
        fprintf(arquivo, "%d\n", amostra[i]); // Grava no arquivo
    }

    // Fecha o arquivo após a gravação
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