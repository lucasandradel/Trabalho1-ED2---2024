#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

int main() {
    tipo_no *arvore = NULL; // Inicializa a árvore AVL como vazia

    // Nome do arquivo de entrada (substitua pelo caminho do arquivo desejado)
    const char *nome_arquivo = "arquivo_5000_1.txt";

    // Chama a função para ler os números do arquivo e inseri-los na árvore AVL
    arvore = ler_e_inserir(nome_arquivo, arvore);
    // Imprime a árvore AVL após a inserção
    printf("Árvore AVL após inserção dos números:\n");
    imprime(arvore);
    
    printf("\n\nNúmero total de rotações: %d\n", obter_contador_rotacoes());
    printf("Altura total da árvore: %d\n", altura_no(arvore));



    return EXIT_SUCCESS; // Retorna 0 para indicar que o programa terminou com sucesso
}
