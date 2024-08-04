#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "arvRBN.h"
#include "Busca.h"
#include "Geracao.h"

// Variáveis globais para armazenar os resultados e o nome do arquivo inserido
Resultado resultado_atual;
char arquivo_inserido[256] = "";

int main() {
    tipo_no *arvore = NULL; // Inicializa a árvore RBN como vazia
    int opcao; // Opção escolhida pelo usuário no menu
    char nome_arquivo[256]; // Buffer para o nome do arquivo escolhido pelo usuário

    while (1) {
        // Mostra o menu de opções
        printf("\nEscolha uma opção:\n");
        printf("1. Gerar arquivos de saída\n");
        printf("2. Inserir na árvore\n");
        printf("3. Buscar amostra\n");
        printf("4. Gerar arquivo de saída para amostra\n");
        printf("5. Ver resultados\n");
        printf("6. Sair\n");
        printf("\nDigite a opção desejada: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                // Gerar arquivos de saída com números aleatórios
                printf("\n\t******************** Gerando arquivos de saída ********************...\n");
                gerar_numeros(5000, "arquivo_5000_1.txt");
                gerar_numeros(5000, "arquivo_5000_2.txt");
                gerar_numeros(5000, "arquivo_5000_3.txt");
                gerar_numeros(20000, "arquivo_20000_1.txt");
                gerar_numeros(20000, "arquivo_20000_2.txt");
                gerar_numeros(20000, "arquivo_20000_3.txt");
                printf("\nArquivos gerados com sucesso.\n");
                break;

            case 2:
                // Liberar a árvore atual antes de inserir novos dados
                if (arvore != NULL) {
                    liberarArvoreRB(arvore);
                    arvore = NULL;
                }

                // Inserir os números de um arquivo na árvore RBN
                printf("\nEscolha um arquivo para inserir na árvore:\n");
                printf("1. arquivo_5000_1.txt\n");
                printf("2. arquivo_5000_2.txt\n");
                printf("3. arquivo_5000_3.txt\n");
                printf("4. arquivo_20000_1.txt\n");
                printf("5. arquivo_20000_2.txt\n");
                printf("6. arquivo_20000_3.txt\n");
                printf("\nDigite o número do arquivo desejado: ");
                int escolha_arquivo;
                scanf("%d", &escolha_arquivo);

                // Define o nome do arquivo com base na escolha do usuário
                switch (escolha_arquivo) {
                    case 1: strcpy(nome_arquivo, "arquivo_5000_1.txt"); break;
                    case 2: strcpy(nome_arquivo, "arquivo_5000_2.txt"); break;
                    case 3: strcpy(nome_arquivo, "arquivo_5000_3.txt"); break;
                    case 4: strcpy(nome_arquivo, "arquivo_20000_1.txt"); break;
                    case 5: strcpy(nome_arquivo, "arquivo_20000_2.txt"); break;
                    case 6: strcpy(nome_arquivo, "arquivo_20000_3.txt"); break;
                    default:
                        printf("\n\t******************** Opção inválida. Retornando ao menu. ********************\n");
                        continue;
                }

                printf("*************************** Iniciando a inserção. O programa fará uma pausa de 3 segundos... ***************************\n\n");
                sleep(3);

                // Chama a função para ler os números do arquivo e inseri-los na árvore RBN
                arvore = ler_e_inserir(nome_arquivo, arvore, &contador_rotacoes);

                // Armazena o nome do arquivo inserido
                strcpy(arquivo_inserido, nome_arquivo);

                printf("\n *************************** Inserção concluída. O programa fará uma pausa de 2 segundos... ***************************\n");
                sleep(2);

                // Imprime a árvore RBN após a inserção dos números
                printf("\n *************************** Árvore RBN após inserção dos números: ***************************\n");
                imprime(arvore);

                break;

            case 3:
                // Buscar uma amostra de números na árvore RBN
                printf("\nEscolha um arquivo para buscar amostra:\n");
                printf("1. arquivo_5000_1.txt\n");
                printf("2. arquivo_5000_2.txt\n");
                printf("3. arquivo_5000_3.txt\n");
                printf("4. arquivo_20000_1.txt\n");
                printf("5. arquivo_20000_2.txt\n");
                printf("6. arquivo_20000_3.txt\n");
                printf("\nDigite o número do arquivo desejado: ");
                scanf("%d", &escolha_arquivo);

                // Define o nome do arquivo com base na escolha do usuário
                switch (escolha_arquivo) {
                    case 1: strcpy(nome_arquivo, "arquivo_5000_1.txt"); break;
                    case 2: strcpy(nome_arquivo, "arquivo_5000_2.txt"); break;
                    case 3: strcpy(nome_arquivo, "arquivo_5000_3.txt"); break;
                    case 4: strcpy(nome_arquivo, "arquivo_20000_1.txt"); break;
                    case 5: strcpy(nome_arquivo, "arquivo_20000_2.txt"); break;
                    case 6: strcpy(nome_arquivo, "arquivo_20000_3.txt"); break;
                    default:
                        printf("\n\t******************** Opção inválida. Retornando ao menu. ********************\n");
                        continue;
                }

                // Verifica se o arquivo escolhido é o mesmo que foi inserido na árvore
                if (strcmp(nome_arquivo, arquivo_inserido) != 0) {
                    printf("O arquivo escolhido para a busca não corresponde ao arquivo inserido na árvore.\n");
                    continue;
                }

                printf("\n*************************** Preparando para a busca. O programa fará uma pausa de 2 segundos... ***************************\n");
                sleep(2);

                int tamanho_amostra;
                // Lê os números do arquivo e seleciona uma amostra aleatória
                int *amostra = ler_numeros_e_selecionar_amostra(nome_arquivo, &tamanho_amostra);
                if (amostra == NULL) {
                    return EXIT_FAILURE;
                }

                // Nome do arquivo onde a amostra será salva
                const char *nome_arquivo_amostra = "amostra.txt";

                // Mostra os valores da amostra e salva em um arquivo
                mostrar_amostra_e_salvar(amostra, tamanho_amostra, nome_arquivo_amostra);

                printf("\n*************************** Iniciando a busca. O programa fará uma pausa de 2 segundos... ***************************\n");
                sleep(2);

                // Inicia a contagem do tempo de busca
                clock_t inicio_busca = clock();
                // Realiza a busca na árvore RBN usando a amostra e avalia o desempenho
                int num_comparacoes = busca_e_avaliar(arvore, amostra, tamanho_amostra);
                clock_t fim_busca = clock();
                // Calcula o tempo de busca
                double tempo_busca = (double)(fim_busca - inicio_busca) / CLOCKS_PER_SEC;

                // Preenche os resultados atuais
                strcpy(resultado_atual.nome_arquivo, nome_arquivo);
                resultado_atual.tempo_busca = tempo_busca;
                resultado_atual.num_comparacoes = num_comparacoes;
                resultado_atual.num_rotacoes = obter_contador_rotacoes();
                resultado_atual.altura_arvore = alturaRB(arvore);

                printf("\nNúmero total de rotações: %d\n", resultado_atual.num_rotacoes);
                printf("Altura total da árvore: %d\n", resultado_atual.altura_arvore);

                // Libera a memória alocada para a amostra
                free(amostra);
                break;

            case 4:
                // Gerar arquivo de saída para amostra
                printf("\nEscolha um arquivo para gerar saída da amostra:\n");
                printf("1. arquivo_5000_1.txt\n");
                printf("2. arquivo_5000_2.txt\n");
                printf("3. arquivo_5000_3.txt\n");
                printf("4. arquivo_20000_1.txt\n");
                printf("5. arquivo_20000_2.txt\n");
                printf("6. arquivo_20000_3.txt\n");
                printf("\nDigite o número do arquivo desejado: ");
                scanf("%d", &escolha_arquivo);

                // Define o nome do arquivo com base na escolha do usuário
                switch (escolha_arquivo) {
                    case 1: strcpy(nome_arquivo, "arquivo_5000_1.txt"); break;
                    case 2: strcpy(nome_arquivo, "arquivo_5000_2.txt"); break;
                    case 3: strcpy(nome_arquivo, "arquivo_5000_3.txt"); break;
                    case 4: strcpy(nome_arquivo, "arquivo_20000_1.txt"); break;
                    case 5: strcpy(nome_arquivo, "arquivo_20000_2.txt"); break;
                    case 6: strcpy(nome_arquivo, "arquivo_20000_3.txt"); break;
                    default:
                        printf("\n\t******************** Opção inválida. Retornando ao menu. ********************\n");
                        continue;
                }

                int tamanho_amostra_saida;
                // Lê os números do arquivo e seleciona uma amostra aleatória
                int *amostra_saida = ler_numeros_e_selecionar_amostra(nome_arquivo, &tamanho_amostra_saida);
                if (amostra_saida == NULL) {
                    return EXIT_FAILURE;
                }

                // Nome do arquivo onde a amostra será salva
                const char *nome_arquivo_amostra_saida = "amostra_saida.txt";
                // Mostra os valores da amostra e salva em um arquivo
                mostrar_amostra_e_salvar(amostra_saida, tamanho_amostra_saida, nome_arquivo_amostra_saida);

                // Libera a memória alocada para a amostra
                free(amostra_saida);
                break;

            case 5:
                // Ver resultados
                mostrar_resultados(resultado_atual);
                break;

            case 6:
                // Sair do programa
                printf("Saindo do programa.\n");
                liberarArvoreRB(arvore); // Certifique-se de liberar a árvore antes de sair
                return EXIT_SUCCESS;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }
}
