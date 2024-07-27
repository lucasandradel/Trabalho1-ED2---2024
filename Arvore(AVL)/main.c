#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Geracao.h"
#include "ArvoreAVL.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <número de valores> <nome do arquivo>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n = atoi(argv[1]);
    const char *nome_arquivo = argv[2];

    gerar_numeros(n, nome_arquivo);

    return EXIT_SUCCESS;
}