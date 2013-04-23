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
    criarLista(p, sizeof (int));
    for (i = 0; i < size; i++) {
        int value = rand();
        addFim((*p), &value);
    }
    return TRUE;
}

int criarListaOrd(ppLista p, int size) {
    int i;
    criarLista(p, sizeof (int));
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
//    printf("%d e %d\n",*(p1), *(p2));
    return result;
}

int main(int argc, char** argv) {
    //int a = 1, b = 2;
    pLista lista = NULL, ordenada = NULL;
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

    return 0;
}

