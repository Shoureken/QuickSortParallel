/* lista_publico.h */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct Lista *pLista, **ppLista;
typedef struct Nolista *pNoLista, **ppNoLista;

int criarLista(ppLista pp, int tInfo, int blockSize);
int destruirLista(ppLista pp);
int reiniciarLista(ppLista pp);

int addFim(pLista p, void *elemento);

int buscaInicio(pLista p, void *elemento);

int tamanho(pLista p);
void toString(pLista p);
int acrescentarFim(pLista original, pLista acrescentar, ppLista result);
int acrescentarInicio(pLista original, pLista acrescentar);
int buscaNoPos(pLista p, ppNoLista pp, int pos);

//void swap(ppNoLista a, ppNoLista b);
void swap(pNoLista no, int posa, int posb, int tInfo);