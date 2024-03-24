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

// Funcao para inserir na arvore
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

//Funçao para contar o nível da árvore
int tamanho(No *raiz){
    if(raiz == NULL)
        return 0;
    else
        return 1 + tamanho(raiz->esquerda) + tamanho(raiz->direita);
}

/*int buscar(No *raiz, int chave){
     if(raiz == NULL)
         return -1; // Retorno nao deve pertencer ao conjunto de elementos da arvore
     else{
         if(raiz->conteudo == chave)
             return raiz->conteudo;
         else{
             if(chave < raiz->conteudo)
                 return buscar(raiz->esquerda,chave);
             else
                 return buscar(raiz->direita,chave);
         }
     }
}*/

int buscar(No *raiz, int chave){
     if(raiz == NULL)
         return 0; // se o elemento nao estiver na arvore
     else{
         if(raiz->conteudo == chave)
             return 1; // se o elemento pertencer a arvore
         else{
             if(chave < raiz->conteudo)
                 return buscar(raiz->esquerda,chave);
             else
                 return buscar(raiz->direita,chave);
         }
     }
}

No* buscarNo(No *raiz, int chave){
    if(raiz == NULL)
        return NULL;
    else{
        if(raiz->conteudo == chave)
            return raiz;
        else{
            if(chave < raiz->conteudo)
                return buscarNo(raiz->esquerda,chave);
            else
                return buscarNo(raiz->direita,chave);
        }
    }
}

No* remover(No *raiz, int chave){
    if(raiz ==NULL){
        printf("Valor nao encontrado!\n");
        return NULL;
    }else{
        if(raiz->conteudo == chave){
            // Remove nós folhas
            if(raiz->esquerda == NULL && raiz->direita == NULL){
                free(raiz);
                return NULL;
            }else{
                // Remove nós que possuem apenas 1 filho
                if(raiz->esquerda == NULL || raiz->direita ==NULL){
                    No *aux;
                    if(raiz->esquerda != NULL)
                        aux = raiz->esquerda;
                    else
                        aux = raiz->direita;
                    free(raiz);
                    return aux;
                }else{
                    No* aux = raiz->esquerda;
                    while (aux->direita != NULL)
                        aux = aux->direita;
                    raiz->conteudo = aux->conteudo;
                    aux->conteudo = chave;
                    raiz->esquerda = remover(raiz->esquerda,chave);
                    return raiz;
                }
            }
        } else{
            if(chave < raiz->conteudo)
                raiz->esquerda = remover(raiz->esquerda,chave);
            else
                raiz->direita = remover(raiz->direita,chave);
            return raiz;
        }
    }
    return NULL;
}

//Funçao para imprimir os elementos da arvore
void imprimir(No *raiz){
    if(raiz != NULL){
        imprimir(raiz->esquerda);
        printf("%d ", raiz->conteudo);
        imprimir(raiz->direita);
    }
}

// Funcao para calcular a altura de uma árvore binária
int alturaArv(No *raiz){
    // se raiz for nula ou folha
    if(raiz == NULL || raiz->direita == NULL && raiz->esquerda == NULL)
        return 0;
    else{
        int esq = 1 + alturaArv(raiz->esquerda);
        int dir = 1 + alturaArv(raiz->direita);
        //retorna o maior
        if(esq > dir)
            return esq;
        else
            return dir;
    }
}

int alturaSubArv(No *raiz,int chave){
    No *no = buscarNo(raiz,chave);
    if(no)
        return alturaArv(no);
    else
        return -1;
}

int main(){
    int op,valor;
    No *raiz = NULL;

    do {
        printf("\n0 - Sair\n1 - inserir\n2 - Imprimir\n3 - Buscar\n4 - Remover\n5 - Altura\n6 - Altura subarvore\n");
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
                printf("Tamanho: %d\n", tamanho(raiz));
                break;
            case 4:
                printf("Digite um valor a ser removido:");
                scanf("%d",&valor);
                raiz = remover(raiz,valor);
                break;
            case 5:
                printf("A altura da arvore e: %d\n", alturaArv(raiz));
                break;
            case 6:
                printf("Qual o valor deseja calcular a altura? ");
                scanf("%d",&valor);
                printf("\nA altura e: %d\n", alturaSubArv(raiz,valor));
                break;
            default:
                printf("\n Opcao invalida!\n");
        }
    } while ( op != 0);

    return 0;
}