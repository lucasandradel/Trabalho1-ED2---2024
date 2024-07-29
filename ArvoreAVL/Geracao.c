#include "Geracao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// Função principal que executa o programa
int main() {
    // Inicializa o gerador de números aleatórios com a hora atual
    srand(time(NULL));

    // Define os tamanhos dos arquivos e os nomes dos arquivos a serem gerados
    int tamanhos[] = {5000, 5000, 5000, 20000, 20000, 20000};
    // Lista de nomes de arquivos onde os números serão salvos
    const char *nomes_arquivos[] = {
        "arquivo_5000_1.txt",
        "arquivo_5000_2.txt",
        "arquivo_5000_3.txt",
        "arquivo_20000_1.txt",
        "arquivo_20000_2.txt",
        "arquivo_20000_3.txt"
    };

    // Loop para gerar os arquivos com números aleatórios
    for (int i = 0; i < 6; i++) {
        // Chama a função gerar_numeros para criar o arquivo com números aleatórios
        gerar_numeros(tamanhos[i], nomes_arquivos[i]);
    }

    // Mensagem para indicar que os arquivos foram gerados com sucesso
    printf("Arquivos gerados com sucesso.\n");

    // Retorna 0 para indicar que o programa terminou sem erros
    return EXIT_SUCCESS;
}
