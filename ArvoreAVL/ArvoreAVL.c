#include "ArvoreAVL.h"


// Contador global para rotações
static int contador_rotacoes = 0;

// Função que retorna o maior de dois inteiros
int maior(int x, int y) {
    return (x > y) ? x : y;
}

// Função que retorna a altura de um nó
int altura_no(tipo_no *no) {
    if (no == NULL) {
        return -1; // Altura de uma árvore vazia é -1
    }
    return no->h; // Altura armazenada no nó
}

// Função que calcula o fator de balanceamento de um nó
int FatorBalanceamento_no(tipo_no *no) {
    return altura_no(no->dir) - altura_no(no->esq);
}

// Função para realizar rotação simples à direita
tipo_no *Rotacao_direita(tipo_no *pt) {
    tipo_no *ptu = pt->esq; // ptu é o filho esquerdo de pt
    pt->esq = ptu->dir;     // Subárvore direita de ptu se torna a subárvore esquerda de pt
    ptu->dir = pt;          // pt se torna o filho direito de ptu
    // Atualizar as alturas após a rotação
    pt->h = maior(altura_no(pt->esq), altura_no(pt->dir)) + 1;
    ptu->h = maior(altura_no(ptu->esq), pt->h) + 1;
    return ptu; // ptu se torna a nova raiz
    //Incrementar o contador de rotações
    contador_rotacoes++;
    return ptu; // ptu se torna a nova raiz
}

// Função para realizar rotação simples à esquerda
tipo_no *Rotacao_esquerda(tipo_no *pt) {
    tipo_no *ptu = pt->dir; // ptu é o filho direito de pt
    pt->dir = ptu->esq;     // Subárvore esquerda de ptu se torna a subárvore direita de pt
    ptu->esq = pt;          // pt se torna o filho esquerdo de ptu
    // Atualizar as alturas após a rotação
    pt->h = maior(altura_no(pt->esq), altura_no(pt->dir)) + 1;
    ptu->h = maior(altura_no(ptu->dir), pt->h) + 1;
    // Incrementar o contador de rotações
    contador_rotacoes++;
    return ptu; // ptu se torna a nova raiz
}

// Função para realizar rotação dupla à direita
tipo_no *RotacaoDup_direita(tipo_no *pt) {
    pt->esq = Rotacao_esquerda(pt->esq); // Primeiro faz rotação à esquerda no filho esquerdo
    // Incrementar o contador de rotações
    contador_rotacoes++;
    return Rotacao_direita(pt);// Depois faz rotação à direita no próprio pt
}

// Função para realizar rotação dupla à esquerda
tipo_no *RotacaoDup_esquerda(tipo_no *pt) {
    pt->dir = Rotacao_direita(pt->dir); // Primeiro faz rotação à direita no filho direito
    // Incrementar o contador de rotações
    contador_rotacoes++;
    return Rotacao_esquerda(pt);        // Depois faz rotação à esquerda no próprio pt
}

// Função para inserir um novo nó na árvore AVL
tipo_no *insere(tipo_no *no, int chave) {
    if (no == NULL) {
        // Cria um novo nó se a árvore estiver vazia
        no = (tipo_no *)malloc(sizeof(tipo_no));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
        no->h = 0;  // A altura do nó é 0 porque é uma folha
        no->fb = 0; // Fator de balanceamento inicial é 0
    } else if (chave < no->chave) {
        // Inserir na subárvore esquerda se a chave for menor
        no->esq = insere(no->esq, chave);
    } else if (chave > no->chave) {
        // Inserir na subárvore direita se a chave for maior
        no->dir = insere(no->dir, chave);
    } else {
        printf("Inserção inválida\n");
        return no;
    }

    // Atualizar a altura do nó após a inserção
    no->h = maior(altura_no(no->esq), altura_no(no->dir)) + 1;
    // Atualizar o fator de balanceamento
    no->fb = FatorBalanceamento_no(no);

    // Verificar e corrigir desbalanceamento
    if (no->fb <= -2) { // Subárvore esquerda mais alta
        if (FatorBalanceamento_no(no->esq) <= 0) {
            printf("ROTAÇÃO SIMPLES DIREITA (%d)\n", no->chave);
            no = Rotacao_direita(no);
        } else {
            printf("ROTAÇÃO DUPLA DIREITA (%d)\n", no->chave);
            no = RotacaoDup_direita(no);
        }
    } else if (no->fb >= 2) { // Subárvore direita mais alta
        if (FatorBalanceamento_no(no->dir) >= 0) {
            printf("ROTAÇÃO SIMPLES ESQUERDA (%d)\n", no->chave);
            no = Rotacao_esquerda(no);
        } else {
            printf("ROTAÇÃO DUPLA ESQUERDA (%d)\n", no->chave);
            no = RotacaoDup_esquerda(no);
        }
    }

    return no; // Retorna o novo nó raiz da subárvore
}

// Função para imprimir a árvore com indentação
void imprime(tipo_no *no) {
    if (no != NULL) {
        // Imprime a subárvore direita
        imprime(no->dir);

        // Imprime o valor do nó e sua altura
        printf("%d h -> (%d)\n", no->chave, no->h);
        
        // Imprime a subárvore esquerda
        imprime(no->esq);
    }
}

// Função para ler números de um arquivo e inseri-los na árvore AVL
tipo_no* ler_e_inserir(const char *nome_arquivo, tipo_no *raiz) {
    FILE *arquivo = fopen(nome_arquivo, "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return raiz; // Retorna a árvore sem alterações se o arquivo não puder ser aberto
    }

    int numero;
    while (fscanf(arquivo, "%d", &numero) == 1) { // Lê números do arquivo até o final
        raiz = insere(raiz, numero); // Insere o número na árvore AVL
    }

    fclose(arquivo); // Fecha o arquivo após a leitura
    return raiz; // Retorna a árvore com os números inseridos
}

int obter_contador_rotacoes() {
    return contador_rotacoes;
}
