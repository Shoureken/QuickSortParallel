/* lista_publico.h */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Lista *pLista, **ppLista;

int criarLista(ppLista pp, int tInfo);
int destruirLista(ppLista pp);
int reiniciarLista(ppLista pp);

int addInicio(pLista p, void *elemento);
int addPos(pLista p, void *elemento, int pos);
int addFim(pLista p, void *elemento);

int remInicio(pLista p, void *elemento);
int remPos(pLista p, void *elemento, int pos);
int remFim(pLista p, void *elemento);

int buscaInicio(pLista p, void *elemento);
int buscaPos(pLista p, void *elemento, int pos);
int buscaFim(pLista p, void *elemento);

