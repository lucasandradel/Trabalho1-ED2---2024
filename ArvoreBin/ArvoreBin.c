#include "ArvoreBin.h"

tipo_arv_bin *AlocaNo(int vl){
    tipo_arv_bin *novo_no;
    novo_no = (tipo_arv_bin*) malloc(sizeof(tipo_arv_bin));
    novo_no -> valor = vl;
    novo_no -> esq = NULL;
    novo_no -> dir = NULL;
    return novo_no;
}

void InsereArvBin(tipo_arv_bin**arv , int valor ){
    if ((*arv) == NULL){//se não houver ninguguém na minha arvore, alocar um novo valor usando a função "AlocaNo"
        (*arv) = AlocaNo(valor);//Função "AlocaNo" para aderir um valor caso a arvore esteja vazia 

    }else{// se minha arvore não está vazia faça:
        if (valor < (*arv) -> valor){ //verifica se o valor que quero inserir é menor ou maior que o elemento 
            InsereArvBin(&(*arv) -> esq, valor);//se for menor, chama função recursiva e insere no ramo da esquerda
        }else{
            InsereArvBin (&(*arv)-> dir, valor);//senão for menor, chama função recursiva e insere no ramo da direita
        }
        
    }
   
}

//função que percore em pré ordem
/*
Passos:
-Imprimir
-Chamar recursão a esquerda
-Chamar recursão a direita
*/
void PercursoPreOrdem(tipo_arv_bin *arv){
    if (arv != NULL){
        printf (" %d ",  arv -> valor );
        PercursoPreOrdem(arv ->esq);
        PercursoPreOrdem(arv ->dir);
    }
}   

//função que percorre em ordem
/*
Passos:
-Chamar recursão a esquerda
-Imprimir
-Chamar recursão a direita
*/
void PercursoOrdem(tipo_arv_bin *arv){
    if (arv != NULL){
        PercursoOrdem(arv -> esq);
        printf(" %d ", arv -> valor);
        PercursoOrdem(arv -> dir);

    }
}

//função que percorre em pós ordem
/*
Passos:
-Chamar recursão a esquerda
-Chamar recursão a direita
-Imprimir
*/
void PercursoPosOrdem(tipo_arv_bin *arv){
    if (arv != NULL){
        PercursoPosOrdem(arv -> esq);
        PercursoPosOrdem(arv -> dir);
        printf(" %d ", arv -> valor);
        

    }
}

tipo_arv_bin *BuscaValor(tipo_arv_bin *arv, int valor ){
    if ((arv == NULL) || (arv -> valor == valor)){// verifica se a raiz é igual a nulo ou a raiz já é meu valor; pelo menos uma das opções tem que ser verdadeira  
        return arv;//se for, retornar raiz 
    }
    //se não for o valor da raiz:
    if (valor < arv -> valor){
        BuscaValor(arv -> esq, valor);
    }else{
        BuscaValor (arv -> dir, valor);
    }
}

//função que calcula quantos valores estão presentes na árvore que são maiores que o parâmetro valor
int qtd_valores_maiores_que(tipo_arv_bin *arv, int valor){
    int ContaMaiores = 0;
    if (arv == NULL){
        return 0;
    }else{
        if (arv -> valor > valor){
            ContaMaiores ++;
            printf(" %d " , arv -> valor);
        }
        ContaMaiores = ContaMaiores + qtd_valores_maiores_que(arv-> esq, valor);
        ContaMaiores = ContaMaiores + qtd_valores_maiores_que(arv-> dir, valor);
    }
    return ContaMaiores;

}

//Função que retorna a altura da árvore binária
/*

- Declarar duas variáveis para armazenar a quantidade de nós que tem na esquerda e na direita

- verificar se a raiz é nula, se for, retornar -1, SENÃO, fazer duas chamadas recursiva da função altura, para esquerda e para a direita da árvore

- comparar as duas variáveis esquerda e direita que foram armazenadas o valor e retornar a que for maior + 1
*/
int AlturaArvBin(tipo_arv_bin*arv){
    int esquerda, direita;

    if (arv == NULL){ 
        return -1;

    }else{
        esquerda = AlturaArvBin(arv -> esq);
        direita = AlturaArvBin (arv -> dir);

        if (esquerda > direita){

            return esquerda + 1;
        }else{
            return direita +1;
        }

    }
}

//Função que retorna a quantidade de nós da árvore binária
int ContabilizaNosArvBin(tipo_arv_bin* arv){
    if (arv == NULL){
        return 0;

    }else{
        return 1 + ContabilizaNosArvBin(arv -> esq) + ContabilizaNosArvBin (arv -> dir);
    }
}

//Função que retorna a quantidade de nós folhas da árvore binária
int ContabilizaNosFolhasArvBin(tipo_arv_bin* arv ){
    if (arv == NULL){
        return 0;
    }else if((arv -> esq == NULL) && (arv -> dir == NULL)){
        return 1;
    }else{
        return ContabilizaNosFolhasArvBin(arv -> esq) + ContabilizaNosFolhasArvBin (arv -> dir);
    }
}

int ContabilizaNosComUmFilho(tipo_arv_bin *arv){
    if (arv == NULL){
        return 0;
    }else{
        if ((arv -> esq != NULL) && (arv -> dir == NULL) || (arv -> esq == NULL) && (arv -> dir != NULL)){
            return 1;
        }
    }
    return ContabilizaNosComUmFilho (arv ->esq) + ContabilizaNosComUmFilho(arv -> dir);

}

tipo_arv_bin* ImprimeTipoNoh(tipo_arv_bin *arv){
    if (arv == NULL){
        //printf("[ÁRVORE NULA]\n");
        return NULL;
    }else{
        if((arv ->esq == NULL) && (arv-> dir == NULL)){
            printf("Elemento Folha: %d\n", arv -> valor);

        }else if((arv -> esq != NULL) && (arv -> dir != NULL)){
            printf("Elemento com dois filhos: %d\n",arv->valor);
            
        }else{
            printf("Elemento com apenas um filho: %d\n", arv-> valor);
        }
        ImprimeTipoNoh(arv -> esq);
        ImprimeTipoNoh(arv -> dir);
        
    }
}

int ImprimeNivelArvBin(tipo_arv_bin* arv, int nivel, int contador) {
    if (arv == NULL) {
        return 0 ;
    }
    
    int vl = arv->valor;
    if (contador == nivel) {
        printf("%d ", vl);
        return 1;
    }

    // Chama recursivamente para os nós filhos com contador incrementado
    ImprimeNivelArvBin(arv->esq, nivel, contador + 1);
    ImprimeNivelArvBin(arv->dir, nivel, contador + 1);
 
}

tipo_arv_bin * IdentificaMenorValorArv (tipo_arv_bin* arv){
    if (arv == NULL){
        return NULL;
    }else{

        if (arv -> esq == NULL){
            printf("----- O menor valor da arvore eh: %d -----\n\n", arv -> valor);
        }else{
            IdentificaMenorValorArv(arv-> esq);
        }

        return arv;
    }
}

tipo_arv_bin * IdentificaMaiorValorArv (tipo_arv_bin* arv){
    if (arv == NULL){
        return NULL;
    }else{
        
        if (arv -> dir == NULL){
            printf("----- O maior valor da arvore Binaria eh: %d -----\n\n", arv -> valor);
        }else{
            IdentificaMaiorValorArv(arv -> dir);
        }
        return arv;
    }
}

tipo_arv_bin* RemoveArvBin(tipo_arv_bin* arv, int chave){
    if (arv == NULL){//se não houver elementos na árvore binária:
        printf("Arvore vazia ou Valor inexiste\n");
        return NULL;
    }else{//se houver elementos na árvore binária faça:
        if(arv -> valor == chave){//verifico se a chave é a raiz, se for:

            //remoção de nó folha
            if((arv->esq == NULL) && (arv -> dir == NULL)){//verifico se os ponteiros esquerdo e direito(filhos), são nulos, se for:
                
                free (arv);//removo o nó
                printf("Elemento folha removido: %d\n\n", chave);

                return NULL;

            }else{//remoção de nós com dois filhos:
                
                //verificação se o elemento tem dois filhos 
                if((arv -> esq != NULL) && (arv-> dir != NULL)){
                    tipo_arv_bin *aux;
                    aux = arv -> esq;
                    
                    while (aux -> dir!= NULL)
                    {
                        aux = aux -> dir;
                    }
                    arv -> valor = aux -> valor;
                    aux -> valor = chave;
                    printf("Elemento com dois filhos %d trocado \n\n", chave);
                    arv -> esq = RemoveArvBin(arv -> esq, chave);
                    return arv;
                    

                }else{//nó com apenas um filho
                       //remoção de nó com um filho

                    tipo_arv_bin *aux; //criação de um ponteiro auxiliar para guardar o nó filho do elemento que irá ser removido e retornar como filho do pai do elemento que irá ser removido
                    if(arv-> esq != NULL){
                        aux = arv -> esq;//guardando o filho esquerdo em auxiliar, caso o filho esquerdo seja diferente de nulo
                    }else{
                        aux = arv -> dir;//guardando o filho direito em auxiliar, caso o filho esquerdo seja diferente de nulo
                    }
                    free(arv);//removendo o elemento que tem apenas um filho
                    printf("Elemento com um filho removido: %d \n\n ", chave);

                    return aux;//retornando o filho do cara que foi removido como filho do pai do cara que foi removido no lugar do cara que foi removido
                }
                
            }

        }else{//se a chave não for igual a a raiz faça:
            if(chave < arv -> valor){//verifico se a chave é menor que a raiz, se for faça:
                arv -> esq = RemoveArvBin(arv -> esq, chave);//recursão da função a esquerda até achar o nó 
                return arv;
            }else{
                arv ->dir = RemoveArvBin(arv -> dir, chave);//recursão a direita até achar o nó
                return arv;
            }

        }
    }

}


