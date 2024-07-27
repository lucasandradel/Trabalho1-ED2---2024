#ifndef __ARVOREBIN_C__
#define __ARVOREBIN_C__


#include <stdio.h>
#include <stdlib.h>



struct est_arv_bin
{
    int valor;
    struct est_arv_bin *esq;
    struct est_arv_bin *dir;
};
typedef struct  est_arv_bin tipo_arv_bin;

//prototipação
tipo_arv_bin *AlocaNo(int);
void InsereArvBin(tipo_arv_bin** , int);
void PercursoPreOrdem(tipo_arv_bin *);
void PercursoOrdem(tipo_arv_bin *);
void PercursoPosOrdem(tipo_arv_bin *);
tipo_arv_bin *BuscaValor(tipo_arv_bin *, int );
int qtd_valores_maiores_que(tipo_arv_bin *, int );
int AlturaArvBin(tipo_arv_bin*);
int ImprimeNivelArvBin(tipo_arv_bin*, int, int );
int ContabilizaNosArvBin(tipo_arv_bin*);
int ContabilizaNosFolhasArvBin(tipo_arv_bin*);
int ContabilizaNosComUmFilho(tipo_arv_bin *);
tipo_arv_bin * RemoveArvBin(tipo_arv_bin*, int);
tipo_arv_bin* ImprimeTipoNoh(tipo_arv_bin*);
tipo_arv_bin * IdentificaMenorValorArv (tipo_arv_bin*);
tipo_arv_bin * IdentificaMaiorValorArv (tipo_arv_bin*);




#endif
