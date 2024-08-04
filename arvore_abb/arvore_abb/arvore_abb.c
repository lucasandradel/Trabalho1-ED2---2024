#include "arvore_abb.h"

//Função que compara maior valor 

int max(int x, int y) {
    return (x > y) ? x : y;
}


//Função que retona altura da árvore 

int altura_no(tipo_abb *no) {
    if (no == NULL)
        return -1;
    else {
        int altura_esq = altura_no(no->esq);
        int altura_dir = altura_no(no->dir);
        return max(altura_esq, altura_dir) + 1; // calcula qual eh a altura maxima, se eh do ramd da esquerda ou do ramo da direita 
    }
}

// função que insere chave na arvore 

tipo_abb *insere(tipo_abb *no, int chave) {
    if (no == NULL) { // se a arvore for vazia, faça isso 
        tipo_abb *novo_no = (tipo_abb *)malloc(sizeof(tipo_abb));
        novo_no->chave = chave; // recebe chave 
        novo_no->esq = novo_no->dir = NULL; //aponta para nulo 
        return novo_no;
    }

    // caso a arvore nao seja vazia 
    if (chave < no->chave) { // verifica se a chave que queremos inserir eh menor que a chave do no atual 
        no->esq = insere(no->esq, chave); // se sim, inserimos na esquerda 
    } else if (chave > no->chave) {
        no->dir = insere(no->dir, chave); // analogamente, fazemos o menos a direita 
    }

    // se for igual nao faz nada porque nao podemos inserir chaves duplicadas

    return no;
}

// Busca noh  na arvore

tipo_abb *busca(tipo_abb *raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave) // se houver apenas a raiz na arvore
        return raiz; // caso base para a parada da recursao 
    if (chave < raiz->chave) 
        return busca(raiz->esq, chave); // chamada recursiva que percorre todo o ramo esquedo da árvore para em busca do noh 
    return busca(raiz->dir, chave); // chamada recursiva que percorre todo o ramo direito da árvore em busca do noh 
}



// Imprime arvore em ordem (percuso in-order)
void imprime(tipo_abb *no) {
    if (no != NULL) {
        imprime(no->esq); // chamada recursiva 
        printf("%d ", no->chave); // caso base 
        imprime(no->dir); // chamada recursiva 
    }
}

// Menu para o usuário interagir 
void menu_de_opcoes() {
    printf("\n*************************** O Espetacular Menu de Opções ***************************\n");
    printf("\n1) Gerar Arquivos\n");
    printf("\n2) Inserir na Árvore\n");
    printf("\n3) Buscar Dado na Árvore\n");
    printf("\n4) Imprimir Árvore\n");
    printf("\n5) Sair\n");
    printf("\nSelecione uma das opções acima: ");
}

// Função para ler números de um arquivo e inseri-los na árvore de busca binária

tipo_abb* ler_e_inserir(const char *nome_arquivo, tipo_abb *raiz) {
    // Abre o arquivo no modo de leitura
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        // Se não conseguir abrir o arquivo, mostra uma mensagem de erro e encerra o programa
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return NULL; // Encerra o programa com um código de erro
    }

    int numero;

    // lê cada número e insere na árvore
    while (fscanf(arquivo, "%d", &numero) == 1) {
            raiz = insere(raiz, numero);
    }
    fclose(arquivo); // Fecha o arquivo depois de ler todos os números
    
    // Retorna a raiz da árvore atualizada com todos os números inseridos
    return raiz; 
}








