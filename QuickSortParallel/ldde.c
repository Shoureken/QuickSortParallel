/* lista.c */

#include "ldde_privado.h"
#include "quicksort_publico.h"

/* CRIAR; DESTRUIR; REINICIAR */

int criarLista(ppLista pp, int tInfo, int blockSize) {
    pNoLista novo;
    (*pp) = (Lista *) malloc(sizeof (Lista));
    if ((*pp) == NULL) {
        return FALSE;
    }
    (*pp)->tInfo = tInfo;
    (*pp)->blockSize = blockSize;
    (*pp)->size = 0;
    novo = (pNoLista) malloc(sizeof (Nolista));
    if (novo == NULL) {
        //printf("[Novo] - Erro na alocação de um novo nó!\n");
        return FALSE;
    }
    novo->used = 0;
    novo->proximo = NULL;
    novo->anterior = NULL;
    novo->dado = malloc(tInfo * (blockSize+1));
    if (novo->dado == NULL) {
        //printf("[Novo->dado] - Erro na alocação em novo->dado!\n");
        return FALSE;
    }
    (*pp)->fim = novo;
    (*pp)->inicio = novo;
    //printf("[Lista] - Criação ok! blockSize = %i\n", blockSize);
    return TRUE;
}



int destruirLista(ppLista pp) {
    if ((*pp) == NULL) {
        return FALSE;
    }
    reiniciarLista(pp);
    free((*pp));
    (*pp) = NULL;
    //printf("[Lista] - Destruição ok!\n");
    return TRUE;
}

int reiniciarLista(ppLista pp) {
    Nolista *aux, *aux2;
    aux = (*pp)->inicio;
    while (aux != NULL) {
        aux2 = aux;
        free(aux->dado);
        free(aux);
        aux = aux2->proximo;
    }
    (*pp)->inicio = NULL;
    (*pp)->fim = NULL;
    //printf("[Lista] - Reinício ok!\n");
    return TRUE;
}

/* VAZIA - CHEIA */

int vazia(pLista p) {
    if ((p->inicio == NULL && p->fim == NULL) || p->size == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* INSERIR */

int addFim(pLista p, void *elemento) {
    Nolista *novo;
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (vazia(p) || p->fim->used == p->blockSize){
        //printf("Criando novo bloco para lista!\n");
        novo = (Nolista *) malloc(sizeof (Nolista));
        if (novo == NULL) {
            //printf("[Novo] - Erro na alocação de um novo nó!\n");
            return FALSE;
        }
        novo->used = 0;
        novo->proximo = NULL;
        novo->anterior = NULL;
        novo->dado = malloc(p->tInfo * (p->blockSize+1));
        if (novo->dado == NULL) {
            //printf("[Novo->dado] - Erro na alocação em novo->dado!\n");
            return FALSE;
        }
        if (vazia(p)){
            p->fim = novo;
            p->inicio = novo;
        } else {
            novo->anterior = p->fim;
            p->fim->proximo = novo;
            p->fim = novo;
        }
    } else {
        novo = p->fim;
    }
    memcpy(novo->dado+(novo->used*p->tInfo), elemento, p->tInfo);
    p->fim->used++;
    p->size++;
    //printf("[INSERIR] - Fim - Ok!\n");
    return TRUE;
}

/* BUSCAS */

int buscaInicio(pLista p, void *elemento) {
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (vazia(p)) {
        //printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }
    memcpy(elemento, p->inicio->dado, p->tInfo);
    //printf("[BUSCAR] - Inicio - Ok!\n");
    return TRUE;
}

int tamanho(pLista p) {
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    return p->size;
}

void toString(pLista p) {
    Nolista *aux;
    int dest = 0, i;
    aux = p->inicio;
    printf("Lista - %d --->   [", p->size);
    while (aux != NULL) {
        printf("[");
        for(i = 0; i < aux->used; i++){
            memcpy(&dest, aux->dado+(i*p->tInfo), p->tInfo);
            printf("%i,", dest);
        }
        printf("]");
        aux = aux->proximo;
    }
    printf("]\n");
}

int acrescentarFim(pLista original, pLista acrescentar, ppLista result) {
    pNoLista no;
    if (vazia(acrescentar)) {
        //printf("acrescentar Vazias\n");
        (*result) = original;
        return TRUE;
    }
    if (vazia(original)) {
        //printf("original Vazias\n");
        (*result) = acrescentar;
        return TRUE;
    }
    //printf("AcrescentarFim original = %i, acrescentar = %i\n", original->size, acrescentar->size);
    
    criarLista(result, original->tInfo, original->size+acrescentar->size);
    
    no = original->inicio;
    while (no != NULL) {
        memcpy((*result)->inicio->dado+(original->tInfo*(*result)->inicio->used), no->dado, original->tInfo*no->used);
        (*result)->size = (*result)->size + no->used;
        (*result)->inicio->used += no->used;
        no = no->proximo;
    }
    
    no = acrescentar->inicio;
    while (no != NULL) {
        memcpy((*result)->inicio->dado+(acrescentar->tInfo*(*result)->inicio->used), no->dado, acrescentar->tInfo*no->used);
        (*result)->size = (*result)->size + no->used;
        (*result)->inicio->used += no->used;
        no = no->proximo;
    }
    return TRUE;
}

int acrescentarInicio(pLista original, pLista acrescentar) {
    //printf("AcrescentarInicio\n");
    //toString(original);
    //toString(acrescentar);

    if (vazia(original)) {
        if (vazia(acrescentar)) {
            //printf("Ambas Vazias\n");
            return TRUE;
        }
        original->inicio = acrescentar->inicio;
        original->fim = acrescentar->fim;
        original->size = acrescentar->size;
        return TRUE;
    }
    if (vazia(acrescentar)) {
        return TRUE;
    }
    original->inicio->anterior = acrescentar->fim;
    acrescentar->fim->proximo = original->inicio;
    original->inicio = acrescentar->inicio;
    original->size += acrescentar->size;
    
    
    //printf("%d\n", original->size);
    //printf("\n");
    return TRUE;
}

int buscaNoPos(pLista p, ppNoLista pp, int pos) {
    Nolista *aux;
    int count = 0, bloco = 0;
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (vazia(p)) {
        //printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }
    if (pos < 1) {
        //printf("[BUSCAR] - Posição - Posição inválida!\n");
        return FALSE;
    }
    if (pos > p->size) {
        //printf("[Lista] - Posição %i maior que a lista %i!\n", pos, p->size);
        return FALSE;
    }
    bloco = (pos-1)/p->blockSize;
    //printf("[BUSCAR] - buscaNoPos - bloco = %i\n", bloco);
    aux = p->inicio;
    while (count < bloco) {
        if (aux->proximo == NULL) {
            //printf("[BUSCAR] - Posição - Posição inválida!\n");
            return FALSE;
        }
        aux = aux->proximo;
        count++;
    }
    (*pp) = aux;
    //printf("[BUSCAR] - Posição %d - Ok!\n", pos);
    return TRUE;
}
/*
void swap(ppNoLista a, ppNoLista b) {
    void *aux = (*a)->dado;
    (*a)->dado = (*b)->dado;
    (*b)->dado = aux;
}
*/
void swap(pNoLista no, int posa, int posb, int tInfo) {
    //printf("swap  %d <-> %d - Ok!\n", *((int *) (no->dado+(posa*tInfo))),  *((int *) (no->dado+(posb*tInfo)))   );
    
    memcpy((no->dado+((no->used+1)*tInfo)), (no->dado+(posa*tInfo)), tInfo);
    //printf("swap  %d - Ok!\n", *((int *)  (no->dado+((no->used+1)*tInfo))  ));
    memcpy((no->dado+(posa*tInfo)), (no->dado+(posb*tInfo)), tInfo);
    memcpy((no->dado+(posb*tInfo)), (no->dado+((no->used+1)*tInfo)), tInfo);
}