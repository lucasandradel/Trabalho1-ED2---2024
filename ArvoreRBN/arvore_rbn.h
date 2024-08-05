#ifndef __ARVRBN_H__
#define __ARVRBN_H__

typedef enum { VERMELHO, PRETO } Cor;
typedef struct tipo_no {
    int chave;
    Cor cor;
    struct tipo_no *esq, *dir, *pai;
} tipo_no;

tipo_no* AlocaNo(int chave);
void rotacaoesq(tipo_no **raiz, tipo_no *x);
void rotacaodir(tipo_no **raiz, tipo_no *y);
void corrigirInsercao(tipo_no **raiz, tipo_no *z);
void inserir(tipo_no **raiz, int chave);
tipo_no* ler_e_inserir(const char* nome_arquivo, tipo_no* arvore);
tipo_no* busca_arv(tipo_no* raiz, int chave, int *comparacoes);
int alturaRB(tipo_no* no);
void percursoEmOrdem(tipo_no *raiz);
void liberarArvoreRB(tipo_no *raiz);
void imprime(tipo_no *raiz); 
int obter_contador_rotacoes();

#endif // ARVRBN_H
