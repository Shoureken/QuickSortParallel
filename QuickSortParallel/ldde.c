/* lista.c */

#include "ldde_privado.h"

/* CRIAR; DESTRUIR; REINICIAR */

int criarLista(ppLista pp, int tInfo) {
    (*pp) = (Lista *)malloc(sizeof(Lista));
    if((*pp) == NULL)
        return FALSE;
    (*pp)->tInfo = tInfo;
    (*pp)->inicio = NULL;
    (*pp)->fim = NULL;
    printf("[Lista] - Criação ok!\n");
    return TRUE;
}

int destruirLista(ppLista pp) {
    if((*pp) == NULL)
        return FALSE;
    reiniciarLista(pp);
    free((*pp));
    (*pp) = NULL;
    printf("[Lista] - Destruição ok!\n");
    return TRUE;
}

int reiniciarLista(ppLista pp) {
    Nolista *aux, *aux2;
    aux = (*pp)->inicio;
    while(aux != NULL) {
        aux2 = aux;
        free(aux);
        aux = aux2->proximo;
    }
    (*pp)->inicio = NULL;
    (*pp)->fim = NULL;
    printf("[Lista] - Reinício ok!\n");
    return TRUE;
}

/* VAZIA - CHEIA */

int vazia(pLista p) {
    if(p->inicio == NULL && p->fim == NULL) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/* INSERIR */

int addInicio(pLista p, void *elemento) {
    Nolista *novo;
    if(p == NULL) {
        printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    novo = (Nolista *)malloc(sizeof(Nolista));
    if(novo == NULL) {
        printf("[Novo] - Erro na alocação de um novo nó!\n");
        return FALSE;
    }
    novo->dado = malloc(p->tInfo);
    if(novo->dado == NULL) {
        printf("[Novo->dado] - Erro na alocação em novo->dado!\n");
        return FALSE;
    }
    memcpy(novo->dado, elemento, p->tInfo);
    novo->anterior = NULL;
    novo->proximo = p->inicio;
    if(vazia(p)) {
        p->fim = novo;
    }
    else {
        p->inicio->anterior = novo;
    }
    p->inicio = novo;
    printf("[INSERIR] - Início - Ok!\n");
    return TRUE;
}

int addPos(pLista p, void *elemento, int pos) {
    Nolista *novo, *aux;
    int count = 1, n = 0;
    if(p == NULL) {
        printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if(pos == 1) {
        if(addInicio(p, elemento) == TRUE)
            return TRUE;
        else
            return FALSE;
    }
    aux = p->inicio;
    while(aux != NULL) {
        aux = aux->proximo;
        n++;
    }
    if(pos > (n+1)) {
        printf("[INSERIR] - Posição - Essa posição é inválida!\n");
        return FALSE;
    } else if(pos == (n+1)) {
        if(addFim(p, elemento))
            return TRUE;
        else
            return FALSE;
    }
    novo = (Nolista *)malloc(sizeof(Nolista));
    if(novo == NULL) {
        printf("[Novo] - Erro na alocação de um novo nó!\n");
        return FALSE;
    }
    novo->dado = malloc(p->tInfo);
    if(novo->dado == NULL) {
        printf("[Novo->dado] - Erro na alocação em novo->dado!\n");
        return FALSE;
    }
    memcpy(novo->dado, elemento, p->tInfo);
    aux = p->inicio;
    while(count < pos) {
        aux = aux->proximo;
        count++;
    }
    aux->anterior->proximo = novo;
    novo->anterior = aux->anterior;
    aux->anterior = novo;
    novo->proximo = aux;
    printf("[INSERIR] - Posição - Ok!\n");
    return TRUE;
}

int addFim(pLista p, void *elemento) {
    Nolista *novo;
    if(p == NULL) {
        printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if(vazia(p)) {
        if(addInicio(p, elemento))
            return TRUE;
        else
            return FALSE;
    }
    
    novo = (Nolista *)malloc(sizeof(Nolista));
    if(novo == NULL) {
        printf("[Novo] - Erro na alocação de um novo nó!\n");
        return FALSE;
    }
    novo->dado = malloc(p->tInfo);
    if(novo->dado == NULL) {
        printf("[Novo->dado] - Erro na alocação em novo->dado!\n");
        return FALSE;
    }
    memcpy(novo->dado, elemento, p->tInfo);
    novo->proximo = NULL;
    p->fim->proximo = novo;
    novo->anterior = p->fim;
    p->fim = novo;
    printf("[INSERIR] - Fim - Ok!\n");
    return TRUE;
}

/* REMOVER */

int remInicio(pLista p, void *elemento) {
    Nolista *aux;
    if(p == NULL) {
        printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if(vazia(p)) {
        printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }
    
    aux = p->inicio;
    p->inicio = aux->proximo;
    if(p->inicio == NULL) {
        p->fim = NULL;
    }
    else {
        p->inicio->anterior = NULL;
    }
    aux->proximo = NULL;
    memcpy(elemento, aux->dado, p->tInfo);
    free(aux->dado);
    free(aux);
    printf("[REMOVER] - Início - Ok!\n");
    return TRUE;
}

int remPos(pLista p, void *elemento, int pos) {
    int count = 1, n = 0;
    Nolista *aux;
    if(p == NULL) {
        printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if(vazia(p)) {
        printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }
    if(pos < 1 || (pos > 1 && p->inicio->proximo == NULL)) {
        printf("[REMOVER] - Posição - Posição inválida!\n");
        return FALSE;
    } else if(pos == 1) {
        if(remInicio(p, elemento))
            return TRUE;
        else
            return FALSE;
    }
    
    
    aux = p->inicio;
    while(aux != NULL) {
        aux = aux->proximo;
        n++;
    }
    if(pos > n) {
        printf("[REMOVER] - Posição - Posição inválida!\n");
        aux = NULL;
        free(aux);
        return FALSE;
    } else if(pos == n) {
        if(remFim(p, elemento))
            return TRUE;
        else
            return FALSE;
    }
    aux = p->inicio;
    while(count < pos) {
        aux = aux->proximo;
        count++;
    }
    aux->anterior->proximo = aux->proximo;
    aux->proximo->anterior = aux->anterior;
    memcpy(elemento, aux->dado, p->tInfo);
    free(aux->dado);
    free(aux);
    printf("[REMOVER] - Posição - Ok!\n");
    return TRUE;
}

int remFim(pLista p, void *elemento) {
    Nolista *aux;
    if(p == NULL) {
        printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if(vazia(p)) {
        printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }
    
    aux = p->fim;
    if(aux->anterior == NULL) {
        p->inicio = NULL;
        p->fim = NULL;
    }
    else {
        p->fim = aux->anterior;
        p->fim->proximo = NULL;
        aux->anterior = NULL;
    }
    memcpy(elemento, aux->dado, p->tInfo);
    free(aux->dado);
    free(aux);
    printf("[REMOVER] - Fim - Ok!\n");
    return TRUE;
}

/* BUSCAS */

int buscaInicio(pLista p, void *elemento) {
    if(p == NULL) {
        printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if(vazia(p)) {
        printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }
    memcpy(elemento, p->inicio->dado, p->tInfo);
    printf("[BUSCAR] - Inicio - Ok!\n");
    return TRUE;
}

int buscaPos(pLista p, void *elemento, int pos) {
    Nolista *aux;
    int count = 1;
    if(pos < 1) {
        printf("[BUSCAR] - Posição - Posição inválida!\n");
        return FALSE;
    }
    if(p == NULL) {
        printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if(vazia(p)) {
        printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }
    
    aux = p->inicio;
    while(count < pos) {
        if(aux->proximo == NULL) {
            printf("[BUSCAR] - Posição - Posição inválida!\n");
            return FALSE;
        }
        aux = aux->proximo;
        count++;
    }
    memcpy(elemento, aux->dado, p->tInfo);
    printf("[BUSCAR] - Posição - Ok!\n");
    return TRUE;
}

int buscaFim(pLista p, void *elemento) {
    if(p == NULL) {
        printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if(vazia(p)) {
        printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }
    memcpy(elemento, p->fim->dado, p->tInfo);
    printf("[BUSCAR] - Fim - Ok!\n");
    return TRUE;
}