/* 
 * File:   quicksort_private.h
 * Author: shoureken
 *
 * Created on 6 de Abril de 2013, 19:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "quicksort_publico.h"
#include "ldde_privado.h"

typedef struct {
    int threadId;
    int dataSize;
    pLista lista;
    void* pivo;
    ppLista maiores;
    ppLista menores;
    int (*cmp)(void *d1, void *d2);
    int inicio;
    int deslocamento;
} PaThreadSeparar;

typedef struct {
    int threadId;
    int dataSize;
    pLista lista;
    void* pivo;
    int (*cmp)(void *d1, void *d2);
    int inicio;
    int deslocamento;
} PaThreadSozinho;