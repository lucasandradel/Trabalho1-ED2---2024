#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // para função usleep
#include "geracao.h"
#include "arvore_abb.h"
#include "busca.h"

// comando para executar a main:  gcc main.c geracao.c -o out


int main(int argc, char *argv[]) {

    tipo_abb *arvore = NULL; //iniciacilazando arvore como nula 

    srand(time(NULL));

    // Define os tamanhos dos arquivos e os nomes dos arquivos a serem gerados
    int tamanhos[] = {5000, 5000, 5000, 20000, 20000, 20000};

    const char *nome_arquivo = "arquivo_5000_1.txt"; // testando apenas um arquivo de numeros 

    // Chama menu para o usuário interagir 

int opcao;

// Laço infinito para sempre voltar ao espetacular menu de opções
do {

    menu_de_opcoes();

    scanf("%d", &opcao);

    switch(opcao) {
        case 1: // gerar arquivos de números  
            printf("\n*************************** Gerando arquivos... ***************************\n");
            sleep(0.5);
            for (int i = 0; i < 1; i++) {
                usleep(500000); // 0.5 segundos
                printf("\rArquivo n° %d gerado", i + 1);
                fflush(stdout); // para printar o numero de arquivos em uma so linha 
                usleep(500000);
                gerar_numeros(tamanhos[i], nome_arquivo); // gera 3 arquivos de tamanho 5000 e 3 arquivos de tamanho 20000
            }
            printf("\n*************************** 6 Arquivos gerados com sucesso!... ***************************\n");
            sleep(0.5);
            break;

        case 2: // inserir na árvore 
             printf("*************************** Iniciando a inserção. O programa fará uma pausa de 3 segundos... ***************************\n\n");
             sleep(3); // Pausa por 5 segundos
             arvore = ler_e_inserir(nome_arquivo, arvore); // entregando o nome do arquivo e a raiz para inserir
             printf("\n*************************** Dados Inseridos na Árvore com Sucesso... ***************************\n");
             sleep(1);
            break;

        case 3: 
            // buscar na árvore 

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

            // Mostra o número total de rotações realizadas na árvore ABB
            //printf("\nNúmero total de rotações: %d\n", obter_contador_comparacoes());
            // Mostra a altura total da árvore AVL
            printf("Altura total da árvore: %d\n", altura_no(arvore));

            // Libera a memória usada para os arrays
            free(numeros);
            free(amostra);
 
            break;
        case 4: // imprimir árvore 
            printf("\n*************************** Imprimindo a Árvore... ***************************\n");
            sleep(2);
            imprime(arvore);
            break;
        case 5: // matar programa
            printf("\n*************************** Finalizando Programa... ***************************\n");
            sleep(1);
            break;

        default: // caso usuário não entre com uma opção válida 
            printf("\n[ERRO]: Insira apenas uma das opção acima\n");
             sleep(2);
    }

} while(opcao != 5); // mostrar menu até oção não ser 5
    

    return 0;
}
