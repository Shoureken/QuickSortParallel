/* 
 * File:   main.c
 * Author: shoureken
 *
 * Created on 6 de Abril de 2013, 18:45
 */

#include "main.h"
#include "ldde_privado.h"

int criarListaRandom(ppLista p, int size) {
    int i;
    criarLista(p, sizeof (int), size);
    for (i = 0; i < size; i++) {
        int value = rand()%30;
        addFim((*p), &value);
    }
    return TRUE;
}

int criarListaOrd(ppLista p, int size) {
    int i;
    criarLista(p, sizeof (int), size);
    for (i = 0; i < size; i++) {
        addFim((*p), &i);
    }
    return TRUE;
}

int cmpInt(void *d1, void *d2) {
    int result = 0;
    int *p1 = (int *) d1;
    int *p2 = (int *) d2;
    if (*(p1) > *(p2)) {
        result = 1;
    } else if (*(p1) < *(p2)) {
        result = -1;
    }
    //printf("Comparando %d e %d, result = %d\n",*(p1), *(p2), result);
    return result;
}

int main(int argc, char** argv) {
    //int a = 1, b = 2;
    pLista lista = NULL/*, lista2 = NULL, lista3 = NULL*/, ordenada = NULL;
    //pNoLista no;
    int size, qtThread;

    if ((argc != 3)) {
        printf("Uso: %s <tamanho do array> <threads>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    //printf("Resultado2 : %d\n", cmpInt(&a, &b));
    //printf("Resultado3 : %d\n", cmpInt(&b, &a));
    
    
    size = atoi(argv[1]); // tamanho do array
    criarListaRandom(&lista, size);
    
    //toString(lista);
    qtThread = atoi(argv[2]);
    ordenar(lista, &ordenada, qtThread, cmpInt);
    //toString(ordenada);
    
    
    /*
    criarLista(&lista, sizeof(int), 3);
    criarLista(&lista2, sizeof(int), 3);
    addFim(lista, &a);
    printf("Main -> ");
    toString(lista);
    a = 2;
    addFim(lista, &a);
    printf("Main -> ");
    toString(lista);
    a = 3;
    addFim(lista, &a);
    printf("Main -> ");
    toString(lista);
    a = 4;
    addFim(lista, &a);
    printf("Main -> ");
    toString(lista);
    a = 5;
    addFim(lista2, &a);
    printf("Main -> ");
    toString(lista2);
    a = 6;
    addFim(lista2, &a);
    printf("Main -> ");
    toString(lista2);
    a = 7;
    addFim(lista2, &a);
    printf("Main -> ");
    toString(lista2);
    
    
    buscaNoPos(lista, &no, 0);
    buscaNoPos(lista, &no, 1);
    buscaNoPos(lista, &no, 2);
    buscaNoPos(lista, &no, 3);
    buscaNoPos(lista, &no, 4);
    buscaNoPos(lista, &no, 5);
    buscaNoPos(lista, &no, 6);
    buscaNoPos(lista, &no, 7);
    buscaNoPos(lista, &no, 8);
    
    acrescentarFim(lista, lista2, &lista3);
    
    toString(lista3);
    
    destruirLista(&lista);
    */
    return 0;
}

