#include "Geracao.h"

void gerar_numeros(int n, const char *nome_arquivo) {
    int *numeros = (int*)malloc(n * sizeof(int));
    if (numeros == NULL) {
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL));

    // Gera números aleatórios únicos
    for (int i = 0; i < n; i++) {
        int novo_numero;
        int repetido;
        do {
            repetido = 0;
            novo_numero = rand() % 100000 + 1; // Gera número entre 1 e 100000
            for (int j = 0; j < i; j++) {
                if (numeros[j] == novo_numero) {
                    repetido = 1;
                    break;
                }
            }
        } while (repetido);
        numeros[i] = novo_numero;
    }

    // Escreve os números no arquivo
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        free(numeros);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d\n", numeros[i]);
    }

    fclose(arquivo);
    free(numeros);
}


