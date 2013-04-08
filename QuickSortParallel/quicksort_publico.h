/* 
 * File:   quicksort_publico.h
 * Author: shoureken
 *
 * Created on 6 de Abril de 2013, 19:27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ldde_publico.h"

#define TRUE 1
#define FALSE 0

typedef struct param_t *pParam_t, **ppParam_t;

void ordenar(pLista p, ppLista ordenada, int qtThreads, int (*cmp)(void *d1, void *d2));