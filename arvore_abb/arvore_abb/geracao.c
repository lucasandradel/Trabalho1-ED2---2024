#include "geracao.h"

// Função que gera números aleatórios e os salva em um arquivo
void gerar_numeros(int n, const char *nome_arquivo) {
    // Cria um espaço na memória para armazenar os números
    int *numeros = (int*)malloc(n * sizeof(int));
    if (numeros == NULL) {
        // Se não conseguiu criar o espaço na memória, mostra uma mensagem de erro
        fprintf(stderr, "Erro ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }

    // Gera n números aleatórios diferentes
    for (int i = 0; i < n; i++) {
        int novo_numero; // Variável para armazenar o número gerado
        int repetido;    // Variável para verificar se o número já foi gerado

        do {
            repetido = 0; // Assume que o número não é repetido
            // Gera um novo número aleatório entre 1 e 100000
            novo_numero = rand() % 100000 + 1;

            // Verifica se o número já foi gerado antes
            for (int j = 0; j < i; j++) {
                if (numeros[j] == novo_numero) {
                    repetido = 1; // Marca como repetido se o número já estiver na lista
                    break; // Sai do loop se encontrar um número repetido
                }
            }
        } while (repetido); // Continua gerando até encontrar um número único

        // Armazena o número gerado na lista
        numeros[i] = novo_numero;
    }

    // Abre o arquivo para escrever os números
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        // Se não conseguiu abrir o arquivo, mostra uma mensagem de erro
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        free(numeros); // Libera o espaço na memória antes de sair
        exit(EXIT_FAILURE);
    }

    // Escreve cada número no arquivo, um por linha
    for (int i = 0; i < n; i++) {
        fprintf(arquivo, "%d\n", numeros[i]);
    }

    // Fecha o arquivo e libera o espaço na memória
    fclose(arquivo);
    free(numeros);
}

