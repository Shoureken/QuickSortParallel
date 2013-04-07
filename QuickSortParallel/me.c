/* lista.c */

#include "me_privado.h"

/* ESTRUTURAS BÁSICAS */
int criarME(ppME pp, int tInfo) {
    (*pp) = (ME *)malloc(sizeof(ME));
    if((*pp) == NULL)
        return FALSE;
    criarLista(&(*pp)->ldde, sizeof(pLista));
    (*pp)->tInfo = tInfo;
    return TRUE;
}

int destruirME(ppME pp, pME p) {
    if(reiniciarME(pp, p)) {
        destruirLista(&(*pp)->ldde);
        free(*pp);
        (*pp) = NULL;
        return TRUE;
    }
    return FALSE;
}

int reiniciarME(ppME pp, pME p) {
    pLista l;
    while(remInicioME(p, &l)) {
        destruirLista(&l);
    }
    if(reiniciarLista(&(*pp)->ldde))
        return TRUE;
    return FALSE;
}

/* INSERIR */
int addInicioME(pME p) {
    pLista l;
    criarLista(&l, p->tInfo);
    addInicio(p->ldde, &l);
    return TRUE;
}

int addPosME(pME p, int pos) {
    pLista l;
    criarLista(&l, p->tInfo);
    addPos(p->ldde, &l, pos);
    return TRUE;
}

int addFimME(pME p) {
    pLista l;
    criarLista(&l, p->tInfo);
    addFim(p->ldde, &l);
    return TRUE;
}

/* INSERIR SUBLISTA */
int addInicioElementoInicio(pME p, void *elemento) {
    pLista l;
    buscaInicio(p->ldde, &l);
    addInicio(l, elemento);
    return TRUE;
}

int addInicioElementoPos(pME p, void *elemento, int pos) {
    pLista l;
    buscaInicio(p->ldde, &l);
    addPos(l, elemento, pos);
    return TRUE;
}

int addInicioElementoFim(pME p, void *elemento) {
    pLista l;
    buscaInicio(p->ldde, &l);
    addFim(l, elemento);
    return TRUE;
}

int addPosElementoInicio(pME p, void *elemento, int pos) {
    pLista l;
    buscaPos(p->ldde, &l, pos);
    addInicio(l, elemento);
    return TRUE;
}

int addPosElementoPos(pME p, void *elemento, int pos, int pos2) {
    pLista l;
    buscaPos(p->ldde, &l, pos);
    addPos(l, elemento, pos2);
    return TRUE;
}

int addPosElementoFim(pME p, void *elemento, int pos) {
    pLista l;
    buscaPos(p->ldde, &l, pos);
    addFim(l, elemento);
    return TRUE;
}

int addFimElementoInicio(pME p, void *elemento) {
    pLista l;
    buscaFim(p->ldde, &l);
    addInicio(l, elemento);
    return TRUE;
}

int addFimElementoPos(pME p, void *elemento, int pos) {
    pLista l;
    buscaFim(p->ldde, &l);
    addPos(l, elemento, pos);
    return TRUE;
}

int addFimElementoFim(pME p, void *elemento) {
    pLista l;
    buscaFim(p->ldde, &l);
    addFim(l, elemento);
    return TRUE;
}


/* REMOVER */
int remInicioME(pME p, void *elemento) {
    if(remInicio(p->ldde, elemento))
        return TRUE;
    return FALSE;
}

int remPosME(pME p, void *elemento, int pos) {
    remPos(p->ldde, elemento, pos);
    return TRUE;
}

int remFimME(pME p, void *elemento) {
    remFim(p->ldde, elemento);
    return TRUE;
}

/* REMOVER SUBLISTA */
int remInicioElementoInicio(pME p, void *elemento) {
    pLista l;
    buscaInicio(p->ldde, &l);
    remInicio(l, elemento);
    return TRUE;
}

int remInicioElementoPos(pME p, void *elemento, int pos) {
    pLista l;
    buscaInicio(p->ldde, &l);
    remPos(l, elemento, pos);
    return TRUE;
}

int remInicioElementoFim(pME p, void *elemento) {
    pLista l;
    buscaInicio(p->ldde, &l);
    remFim(l, elemento);
    return TRUE;
}

int remPosElementoInicio(pME p, void *elemento, int pos) {
    pLista l;
    buscaPos(p->ldde, &l, pos);
    remInicio(l, elemento);
    return TRUE;
}

int remPosElementoPos(pME p, void *elemento, int pos, int pos2) {
    pLista l;
    buscaPos(p->ldde, &l, pos);
    remPos(l, elemento, pos2);
    return TRUE;
}

int remPosElementoFim(pME p, void *elemento, int pos) {
    pLista l;
    buscaPos(p->ldde, &l, pos);
    remFim(l, elemento);
    return TRUE;
}

int remFimElementoInicio(pME p, void *elemento) {
    pLista l;
    buscaFim(p->ldde, &l);
    remInicio(l, elemento);
    return TRUE;
}

int remFimElementoPos(pME p, void *elemento, int pos) {
    pLista l;
    buscaFim(p->ldde, &l);
    remPos(l, elemento, pos);
    return TRUE;
}

int remFimElementoFim(pME p, void *elemento) {
    pLista l;
    buscaFim(p->ldde, &l);
    remFim(l, elemento);
    return TRUE;
}

/* BUSCAR */
int buscaInicioME(pME p, void *elemento) {
    buscaInicio(p->ldde, &elemento);
    return TRUE;
}

int buscaPosME(pME p, void *elemento, int pos) {
    buscaPos(p->ldde, elemento, pos);
    return TRUE;
}

int buscaFimME(pME p, void *elemento) {
    buscaFim(p->ldde, elemento);
    return TRUE;
}

/* BUSCAR SUBLISTA */
int buscaInicioElementoInicio(pME p, void *elemento) {
    pLista l;
    buscaInicioME(p, &l);
    buscaInicio(l, elemento);
    return TRUE;
}

int buscaInicioElementoPos(pME p, void *elemento, int pos) {
    pLista l;
    buscaInicioME(p, &l);
    buscaPos(l, elemento, pos);
    return TRUE;
}

int buscaInicioElementoFim(pME p, void *elemento) {
    pLista l;
    buscaInicioME(p, &l);
    buscaFim(l, elemento);
    return TRUE;
}

int buscaPosElementoInicio(pME p, void *elemento, int pos) {
    pLista l;
    buscaPosME(p, &l, pos);
    buscaInicio(l, elemento);
    return TRUE;
}

int buscaPosElementoPos(pME p, void *elemento, int pos, int pos2) {
    pLista l;
    buscaPosME(p, &l, pos);
    buscaPos(l, elemento, pos2);
    return TRUE;
}

int buscaPosElementoFim(pME p, void *elemento, int pos) {
    pLista l;
    buscaPosME(p, &l, pos);
    buscaFim(l, elemento);
    return TRUE;
}

int buscaFimElementoInicio(pME p, void *elemento) {
    pLista l;
    buscaFimME(p, &l);
    buscaInicio(l, elemento);
    return TRUE;
}

int buscaFimElementoPos(pME p, void *elemento, int pos) {
    pLista l;
    buscaFimME(p, &l);
    buscaPos(l, elemento, pos);
    return TRUE;
}

int buscaFimElementoFim(pME p, void *elemento) {
    pLista l;
    buscaFimME(p, &l);
    buscaFim(l, elemento);
    return TRUE;
}
