/* 
 * File:   main.c
 * Author: shoureken
 *
 * Created on 6 de Abril de 2013, 18:45
 */

#include "main.h"
#include "ldde_privado.h"

int criarListaRandom(ppLista p, int size){
    int i;
    criarLista(p, sizeof(int));
    for (i = 0; i < size; i++){
        int value = rand();
        addFim((*p), &value);
    }
    return TRUE;
}

int cmpInt(void *d1, void *d2){
    int result = 0;
    int *p1 = (int *) d1;
    int *p2 = (int *) d2;
    if (&p1 > &p2){
        result = 1;
    } else if (&p1 < &p2){
        result = -1;
    } 
    return result;
}

int main(int argc, char** argv) {
    pLista lista = NULL;
    int size;

    if ((argc != 2)) {
        printf("Uso: %s <tamanho do array>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    size = atoi(argv[1]); // tamanho do array
    criarListaRandom(&lista, size);
    toString(lista);
    ordenar(lista, 2, cmpInt);
    
    return 0;
}

