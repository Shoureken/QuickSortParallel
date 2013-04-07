/* lista_publico.h */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct ME *pME, **ppME;

int criarME(ppME pp, int tInfo);
int destruirME(ppME pp, pME p);
int reiniciarME(ppME pp, pME p);

int addInicioME(pME p);
int addPosME(pME p, int pos);
int addFimME(pME p);

int addInicioElementoInicio(pME p, void *elemento);
int addInicioElementoPos(pME p, void *elemento, int pos);
int addInicioElementoFim(pME p, void *elemento);
int addPosElementoInicio(pME p, void *elemento, int pos);
int addPosElementoPos(pME p, void *elemento, int pos, int pos2);
int addPosElementoFim(pME p, void *elemento, int pos);
int addFimElementoInicio(pME p, void *elemento);
int addFimElementoPos(pME p, void *elemento, int pos);
int addFimElementoFim(pME p, void *elemento);

int remInicioME(pME p, void *elemento);
int remPosME(pME p, void *elemento, int pos);
int remFimME(pME p, void *elemento);

int remInicioElementoInicio(pME p, void *elemento);
int remInicioElementoPos(pME p, void *elemento, int pos);
int remInicioElementoFim(pME p, void *elemento);
int remPosElementoInicio(pME p, void *elemento, int pos);
int remPosElementoPos(pME p, void *elemento, int pos, int pos2);
int remPosElementoFim(pME p, void *elemento, int pos);
int remFimElementoInicio(pME p, void *elemento);
int remFimElementoPos(pME p, void *elemento, int pos);
int remFimElementoFim(pME p, void *elemento);

int buscaInicioME(pME p, void *elemento);
int buscaPosME(pME p, void *elemento, int pos);
int buscaFimME(pME p, void *elemento);

int buscaInicioElementoInicio(pME p, void *elemento);
int buscaInicioElementoPos(pME p, void *elemento, int pos);
int buscaInicioElementoFim(pME p, void *elemento);
int buscaPosElementoInicio(pME p, void *elemento, int pos);
int buscaPosElementoPos(pME p, void *elemento, int pos, int pos2);
int buscaPosElementoFim(pME p, void *elemento, int pos);
int buscaFimElementoInicio(pME p, void *elemento);
int buscaFimElementoPos(pME p, void *elemento, int pos);
int buscaFimElementoFim(pME p, void *elemento);
