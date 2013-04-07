
#include "quicksort_privado.h"

void *separar(void *arg) {
    int i, comparacao;
    pNoLista atual = NULL;
    param_t *threadParameter = (param_t *) arg;
    printf("separar \n");



    criarLista(&threadParameter->maiores, threadParameter->dataSize);
    criarLista(&threadParameter->menores, threadParameter->dataSize);
    for (i = threadParameter->inicio; i <= threadParameter->fim; i++) {
        if (atual == NULL) {
            buscaPos(threadParameter->lista, atual, i);
        }
        comparacao = threadParameter->cmp(atual, threadParameter->pivo);
        if (comparacao >= 0) {
            addFim(threadParameter->maiores, atual);
        } else {
            addFim(threadParameter->menores, atual);
        }
    }
    return 0;
}

void ordenar(pLista p, int qtThreads, int (*cmp)(void *d1, void *d2)) {
    int qtDiv = (p->size - 1) / qtThreads;
    int qtIni = qtDiv + ((p->size - 1) % qtThreads);
    int i;

    pthread_t *threads;
    param_t *args;

    threads = (pthread_t *) malloc(qtThreads * sizeof (pthread_t));
    args = (param_t *) malloc(qtThreads * sizeof (param_t));
    pLista maiores1;
    pLista maiores2;
    pLista menores1;
    pLista menores2;






    printf("ordenar qtDiv = %d %d\n", qtDiv, qtIni);
    for (i = 0; i < qtThreads; i++) {
        args[i].threadId = i;
        args[i].cmp = cmp;
        args[i].dataSize = p->tInfo;
        args[i].pivo = p->inicio;
        args[i].lista = p;

        if (i == 0) {
            args[i].fim = qtIni;
            args[i].maiores = maiores1;
            args[i].menores = menores1;
        } else {
            args[i].fim = qtDiv;
            args[i].maiores = maiores2;
            args[i].menores = menores2;
        }
        pthread_create(&threads[i], NULL, separar, (void *) (args + i));
    }

    for (i = 0; i < qtThreads; i++) {
        pthread_join(threads[i], NULL);
    }
}
