/* lista_privado.h */

#include <string.h>
#include "ldde_publico.h"

typedef struct Nolista {
    void *dado;
    struct Nolista *proximo;
    struct Nolista *anterior;
    int used;
} Nolista;

typedef struct Lista {
    struct Nolista *inicio;
    struct Nolista *fim;
    int tInfo;
    int size;
    int blockSize;
} Lista;

