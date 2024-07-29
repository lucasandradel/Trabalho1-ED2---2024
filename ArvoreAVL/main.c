#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArvoreAVL.h"
#include "Busca.h"
#include <unistd.h>  // Biblioteca para a função sleep, que faz o programa "dormir" por alguns segundos

int main() {
    tipo_no *arvore = NULL; // Inicializa a árvore AVL como vazia

    // Nome do arquivo de entrada 
    const char *nome_arquivo = "arquivo_5000_1.txt";
    
    // Pausa antes de começar a inserção
    printf("*************************** Iniciando a inserção. O programa fará uma pausa de 3 segundos... ***************************\n\n");
    sleep(3); // Pausa por 5 segundos
    
    // Chama a função para ler os números do arquivo e inseri-los na árvore AVL
    arvore = ler_e_inserir(nome_arquivo, arvore);

    // Faz uma pausa de 2 segundos após a inserção
    printf("\n *************************** Inserção concluída. O programa fará uma pausa de 2 segundos... ***************************\n");
    sleep(2);

    // Imprime a árvore AVL após a inserção dos números. Isso mostra todos os números na árvore.
    printf("\n ***************************Árvore AVL após inserção dos números: ***************************\n");
    imprime(arvore);

    // Faz outra pausa de 2 segundos
    printf("\n*************************** Preparando para a busca. O programa fará uma pausa de 2 segundos... ***************************\n");
    sleep(2);

    // Abre o arquivo para ler os números
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        // Se não conseguir abrir o arquivo, mostra uma mensagem de erro e encerra o programa
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return EXIT_FAILURE; // Encerra o programa com um código de erro
    }

    int total_numeros = 0;
    int numero;

    // Conta quantos números estão no arquivo
    while (fscanf(arquivo, "%d", &numero) == 1) {
        total_numeros++; // Conta cada número encontrado
    }
    rewind(arquivo); // Volta para o começo do arquivo para ler os números novamente

    // Cria um espaço na memória para guardar todos os números do arquivo
    int *numeros = (int*)malloc(total_numeros * sizeof(int));
    if (numeros == NULL) {
        // Se não conseguir alocar memória, mostra uma mensagem de erro e encerra o programa
        fprintf(stderr, "Erro ao alocar memória.\n");
        return EXIT_FAILURE;
    }

    // Lê todos os números do arquivo e os guarda no array 'numeros'
    int i = 0;
    while (fscanf(arquivo, "%d", &numero) == 1) {
        numeros[i++] = numero;
    }
    fclose(arquivo); // Fecha o arquivo depois de ler todos os números

    // Calcula 20% do total de números para a amostra
    int tamanho_amostra = total_numeros / 5;
    // Cria um espaço na memória para guardar a amostra
    int *amostra = (int*)malloc(tamanho_amostra * sizeof(int));
    if (amostra == NULL) {
        // Se não conseguir alocar memória para a amostra, mostra uma mensagem de erro e encerra o programa
        fprintf(stderr, "Erro ao alocar memória para a amostra.\n");
        free(numeros); // Libera a memória usada para os números
        return EXIT_FAILURE;
    }

    // Função para selecionar aleatoriamente uma amostra dos números
    selecionar_amostra(numeros, amostra, total_numeros, tamanho_amostra);

    // Mostra os números selecionados
    mostrar_amostra(amostra, tamanho_amostra);

    // Pausa antes de começar a busca
    printf("\n*************************** Iniciando a busca. O programa fará uma pausa de 2 segundos... ***************************\n");
    sleep(2);

    // Realiza a busca para cada número da amostra e avalia o desempenho
    busca_e_avaliar(arvore, amostra, tamanho_amostra);

    // Mostra o número total de rotações realizadas na árvore AVL
    printf("\nNúmero total de rotações: %d\n", obter_contador_rotacoes());
    // Mostra a altura total da árvore AVL
    printf("Altura total da árvore: %d\n", altura_no(arvore));

    // Libera a memória usada para os arrays
    free(numeros);
    free(amostra);

    return EXIT_SUCCESS; // Retorna 0 para indicar que o programa terminou com sucesso
}
