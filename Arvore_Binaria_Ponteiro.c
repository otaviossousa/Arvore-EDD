#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int conteudo;
    struct no *esquerda,*direita;
}No;

typedef struct {
    No *raiz;
}ArvB;

/*--------------Funcoes---------------*/
void inserir(ArvB *arv, int valor);
void inserirEsquerda(No *no,int valor);
void inserirDireita(No *no, int valor);
void imprimir(No *raiz);
/*------------------------------------*/

/* As funcoes que estao comentadas estao "corretas",
* porém permitem a insercao de um valor já inserido, desse modo
* as funcoes que estao em uso realizam esse tratamento.*/

/*------------------------------------------------------------*/

/*void inserirEsquerda(No *no,int valor){
    if(no->esquerda == NULL){
        No *novo = (No*) malloc(sizeof (No));
        novo->conteudo = valor;
        novo->esquerda =NULL;
        novo->direita = NULL;
        no->esquerda = novo;
    } else{
        if(valor < no->esquerda->conteudo)
            inserirEsquerda(no->esquerda,valor);
        else
            inserirDireita(no->esquerda,valor);
    }
}*/

void inserirEsquerda(No *no,int valor){
    if(no->esquerda == NULL){
        No *novo = (No*) malloc(sizeof (No));
        novo->conteudo = valor;
        novo->esquerda =NULL;
        novo->direita = NULL;
        no->esquerda = novo;
    } else{
        if(valor < no->esquerda->conteudo)
            inserirEsquerda(no->esquerda,valor);
        if(valor > no->esquerda->conteudo)
            inserirDireita(no->esquerda,valor);
    }
}

/*void inserirDireita(No *no, int valor){
    if(no->direita == NULL){
        No *novo = (No*) malloc(sizeof (No));
        novo->conteudo = valor;
        novo->esquerda =NULL;
        novo->direita = NULL;
        no->direita = novo;
    }else{
        if(valor > no->direita->conteudo)
            inserirDireita(no->direita,valor);
        else
            inserirDireita(no->direita,valor);
    }
}*/

void inserirDireita(No *no, int valor){
    if(no->direita == NULL){
        No *novo = (No*) malloc(sizeof (No));
        novo->conteudo = valor;
        novo->esquerda =NULL;
        novo->direita = NULL;
        no->direita = novo;
    }else{
        if(valor > no->direita->conteudo)
            inserirDireita(no->direita,valor);
        if(valor < no->direita->conteudo)
            inserirDireita(no->direita,valor);
    }
}

/*void inserir(ArvB *arv, int valor){
    if(arv->raiz == NULL){
        No *novo = (No*) malloc(sizeof (No));
        novo->conteudo = valor;
        novo->esquerda =NULL;
        novo->direita = NULL;
        arv->raiz = novo;
    }else{
        if(valor < arv->raiz->conteudo)
            inserirEsquerda(arv->raiz,valor);
        else
            inserirDireita(arv->raiz,valor);
    }
}*/

/*void inserir(ArvB *arv, int valor){
    if(arv->raiz == NULL){
        No *novo = (No*) malloc(sizeof (No));
        novo->conteudo = valor;
        novo->esquerda =NULL;
        novo->direita = NULL;
        arv->raiz = novo;
    }else{
        if(valor < arv->raiz->conteudo)
            inserirEsquerda(arv->raiz,valor);
        if(valor > arv->raiz->conteudo)
            inserirDireita(arv->raiz,valor);
    }
}*/

No* inserirNovaVersao(No *raiz, int valor){
    if(raiz == NULL) {
        No *novo = (No *) malloc(sizeof(No));
        novo->conteudo = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }else{
        if(valor < raiz->conteudo)
            raiz->esquerda = inserirNovaVersao(raiz->esquerda,valor);
        if(valor > raiz->conteudo)
            raiz->direita = inserirNovaVersao(raiz->direita,valor);
        return raiz;
    }
}



void imprimir(No *raiz){
    if(raiz != NULL){
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}


int main(){
    int op,valor;
    ArvB arv;
    arv.raiz = NULL;

    No *raiz = NULL;

    do {
        printf("\n0 - Sair\n1 - inserir\n2 - Imprimir\n");
        scanf("%d",&op);
        switch (op) {
            case 0:
                printf("\nSaindo....\n");
                break;
            case 1:
                printf("Digite um valor:");
                scanf("%d",&valor);
                raiz = inserirNovaVersao(raiz,valor);
                break;
            case 2:
                printf("\nImpressao da arvore binaria:\n");
                imprimir(raiz);
                printf("\n");
                break;
            default:
                printf("\n Opcao invalida!\n");
        }
    } while ( op != 0);

    return 0;
}