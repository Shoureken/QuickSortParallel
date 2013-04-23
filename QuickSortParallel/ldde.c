/* lista.c */

#include "ldde_privado.h"
#include "quicksort_publico.h"

/* CRIAR; DESTRUIR; REINICIAR */

int criarLista(ppLista pp, int tInfo) {
    (*pp) = (Lista *) malloc(sizeof (Lista));
    if ((*pp) == NULL) {
        return FALSE;
    }
    (*pp)->tInfo = tInfo;
    (*pp)->inicio = NULL;
    (*pp)->fim = NULL;
    //printf("[Lista] - Criação ok!\n");
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
    if (p->inicio == NULL && p->fim == NULL) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* INSERIR */

int addInicio(pLista p, void *elemento) {
    Nolista *novo;
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    novo = (Nolista *) malloc(sizeof (Nolista));
    if (novo == NULL) {
        //printf("[Novo] - Erro na alocação de um novo nó!\n");
        return FALSE;
    }
    novo->dado = malloc(p->tInfo);
    if (novo->dado == NULL) {
        //printf("[Novo->dado] - Erro na alocação em novo->dado!\n");
        return FALSE;
    }
    memcpy(novo->dado, elemento, p->tInfo);
    novo->anterior = NULL;
    novo->proximo = p->inicio;
    if (vazia(p)) {
        p->fim = novo;
    } else {
        p->inicio->anterior = novo;
    }
    p->inicio = novo;
    p->size++;
    //printf("[INSERIR] - Início - Ok!\n");
    return TRUE;
}

int addPos(pLista p, void *elemento, int pos) {
    Nolista *novo, *aux;
    int count = 1, n = 0;
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (pos == 1) {
        if (addInicio(p, elemento) == TRUE)
            return TRUE;
        else
            return FALSE;
    }
    aux = p->inicio;
    while (aux != NULL) {
        aux = aux->proximo;
        n++;
    }
    if (pos > (n + 1)) {
        //printf("[INSERIR] - Posição - Essa posição é inválida!\n");
        return FALSE;
    } else if (pos == (n + 1)) {
        if (addFim(p, elemento))
            return TRUE;
        else
            return FALSE;
    }
    novo = (Nolista *) malloc(sizeof (Nolista));
    if (novo == NULL) {
        //printf("[Novo] - Erro na alocação de um novo nó!\n");
        return FALSE;
    }
    novo->dado = malloc(p->tInfo);
    if (novo->dado == NULL) {
        //printf("[Novo->dado] - Erro na alocação em novo->dado!\n");
        return FALSE;
    }
    memcpy(novo->dado, elemento, p->tInfo);
    aux = p->inicio;
    while (count < pos) {
        aux = aux->proximo;
        count++;
    }
    aux->anterior->proximo = novo;
    novo->anterior = aux->anterior;
    aux->anterior = novo;
    novo->proximo = aux;
    p->size++;
    //printf("[INSERIR] - Posição - Ok!\n");
    return TRUE;
}

int addFim(pLista p, void *elemento) {
    Nolista *novo;
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (vazia(p)) {
        if (addInicio(p, elemento))
            return TRUE;
        else
            return FALSE;
    }

    novo = (Nolista *) malloc(sizeof (Nolista));
    if (novo == NULL) {
        //printf("[Novo] - Erro na alocação de um novo nó!\n");
        return FALSE;
    }
    novo->dado = malloc(p->tInfo);
    if (novo->dado == NULL) {
        //printf("[Novo->dado] - Erro na alocação em novo->dado!\n");
        return FALSE;
    }
    memcpy(novo->dado, elemento, p->tInfo);
    novo->proximo = NULL;
    p->fim->proximo = novo;
    novo->anterior = p->fim;
    p->fim = novo;
    p->size++;
    //printf("[INSERIR] - Fim - Ok!\n");
    return TRUE;
}

/* REMOVER */

int remInicio(pLista p, void *elemento) {
    Nolista *aux;
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (vazia(p)) {
        //printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }

    aux = p->inicio;
    p->inicio = aux->proximo;
    if (p->inicio == NULL) {
        p->fim = NULL;
    } else {
        p->inicio->anterior = NULL;
    }
    aux->proximo = NULL;
    memcpy(elemento, aux->dado, p->tInfo);
    free(aux->dado);
    free(aux);
    p->size--;
    //printf("[REMOVER] - Início - Ok!\n");
    return TRUE;
}

int remPos(pLista p, void *elemento, int pos) {
    int count = 1, n = 0;
    Nolista *aux;
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (vazia(p)) {
        //printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }
    if (pos < 1 || (pos > 1 && p->inicio->proximo == NULL)) {
        //printf("[REMOVER] - Posição - Posição inválida!\n");
        return FALSE;
    } else if (pos == 1) {
        if (remInicio(p, elemento))
            return TRUE;
        else
            return FALSE;
    }


    aux = p->inicio;
    while (aux != NULL) {
        aux = aux->proximo;
        n++;
    }
    if (pos > n) {
        //printf("[REMOVER] - Posição - Posição inválida!\n");
        aux = NULL;
        free(aux);
        return FALSE;
    } else if (pos == n) {
        if (remFim(p, elemento))
            return TRUE;
        else
            return FALSE;
    }
    aux = p->inicio;
    while (count < pos) {
        aux = aux->proximo;
        count++;
    }
    aux->anterior->proximo = aux->proximo;
    aux->proximo->anterior = aux->anterior;
    memcpy(elemento, aux->dado, p->tInfo);
    free(aux->dado);
    free(aux);
    p->size--;
    //printf("[REMOVER] - Posição - Ok!\n");
    return TRUE;
}

int remFim(pLista p, void *elemento) {
    Nolista *aux;
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (vazia(p)) {
        //printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }

    aux = p->fim;
    if (aux->anterior == NULL) {
        p->inicio = NULL;
        p->fim = NULL;
    } else {
        p->fim = aux->anterior;
        p->fim->proximo = NULL;
        aux->anterior = NULL;
    }
    memcpy(elemento, aux->dado, p->tInfo);
    free(aux->dado);
    free(aux);
    p->size--;
    //printf("[REMOVER] - Fim - Ok!\n");
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

int buscaPos(pLista p, void *elemento, int pos) {
    Nolista *aux;
    int count = 1;
    if (pos < 1) {
        //printf("[BUSCAR] - Posição - Posição inválida!\n");
        return FALSE;
    }
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (vazia(p)) {
        //printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }

    aux = p->inicio;
    while (count < pos) {
        if (aux->proximo == NULL) {
            //printf("[BUSCAR] - Posição - Posição inválida!\n");
            return FALSE;
        }
        aux = aux->proximo;
        count++;
    }
    memcpy(elemento, aux->dado, p->tInfo);
    //printf("[BUSCAR] - Posição %d - Ok!\n", pos);
    return TRUE;
}

int buscaFim(pLista p, void *elemento) {
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (vazia(p)) {
        //printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }
    memcpy(elemento, p->fim->dado, p->tInfo);
    //printf("[BUSCAR] - Fim - Ok!\n");
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
    int dest = 0;
    aux = p->inicio;
    printf("Lista - %d --->   ", p->size);
    while (aux != NULL) {
        memcpy(&dest, aux->dado, p->tInfo);
        printf("%i,", dest);
        aux = aux->proximo;
    }
    printf("\n");
}

int acrescentarFim(pLista original, pLista acrescentar) {

    //printf("AcrescentarFim\n");
    //toString(original);
    //toString(acrescentar);

    //printf("%d + %d = ", original->size, acrescentar->size);


    if (vazia(original)) {
        if (vazia(acrescentar)) {
            //printf("Ambas Vazias\n");
            return TRUE;
        }
        original->inicio = acrescentar->inicio;
        original->fim = acrescentar->fim;
        original->size = acrescentar->size;
        //printf("%d\n", original->size);
        //printf("Aqui\n");
        return TRUE;
    }
    if (vazia(acrescentar)) {
        return TRUE;
    }
    original->fim->proximo = acrescentar->inicio;
    acrescentar->inicio->anterior = original->fim;
    original->fim = acrescentar->fim;


    original->size += acrescentar->size;
    //printf("%d\n", original->size);
    //printf("\n");
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
    int count = 1;
    if (pos < 1) {
        //printf("[BUSCAR] - Posição - Posição inválida!\n");
        return FALSE;
    }
    if (p == NULL) {
        //printf("[Lista] - Lista é NULL!\n");
        return FALSE;
    }
    if (vazia(p)) {
        //printf("[Lista] - Lista está vazia!\n");
        return FALSE;
    }

    aux = p->inicio;
    while (count < pos) {
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

void swap(ppNoLista a, ppNoLista b) {
    void *aux = (*a)->dado;
    (*a)->dado = (*b)->dado;
    (*b)->dado = aux;
}