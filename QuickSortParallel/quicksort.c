
#include "quicksort_privado.h"

void *separar(void *arg) {
    int i, comparacao;
    pNoLista atual = NULL;
    param_t *tParam = (param_t *) arg;
    int pivoData = *((int *) tParam->pivo->dado);
    printf("Thread -> Separar id= %d, pivo= %d, inicio= %d, deslocamento= %d, \n", tParam->threadId, pivoData, tParam->inicio, tParam->deslocamento);
    criarLista(&tParam->maiores, tParam->dataSize);
    criarLista(&tParam->menores, tParam->dataSize);
    for (i = 0; i < tParam->deslocamento; i++) {
        if (atual == NULL) {
            buscaPos(tParam->lista, &atual, i);
        }
        comparacao = tParam->cmp(atual, tParam->pivo);
        if (comparacao >= 0) {
            addFim(tParam->maiores, atual);
        } else {
            addFim(tParam->menores, atual);
        }
    }
    return 0;
}

void ordenar(pLista p, ppLista ordenada, int qtThreads, int (*cmp)(void *d1, void *d2)) {
    int qtDiv = (p->size - 1) / qtThreads;
    int qtIni = qtDiv + ((p->size - 1) % qtThreads);
    int i;
    
    pthread_t *threads;
    param_t *args;
    
    pLista *maiores;
    pLista *menores;

    threads = (pthread_t *) malloc(qtThreads * sizeof (pthread_t));
    args = (param_t *) malloc(qtThreads * sizeof (param_t));
    maiores = (pLista *) malloc(qtThreads * sizeof(pLista));
    menores = (pLista *) malloc(qtThreads * sizeof(pLista));

    printf("ordenar qtDiv = %d %d\n", qtDiv, qtIni);
    for (i = 0; i < qtThreads; i++) {
        args[i].threadId = i;
        args[i].cmp = cmp;
        args[i].dataSize = p->tInfo;
        args[i].pivo = p->inicio;
        args[i].lista = p;
        args[i].maiores = maiores[i];
        args[i].menores = menores[i];
        if (i == 0) {
            args[i].inicio = 1;
            args[i].deslocamento = qtIni;    
        } else {
            args[i].inicio = 1+qtIni+((i-1)*qtDiv);
            args[i].deslocamento = qtDiv;
        }
        pthread_create(&threads[i], NULL, separar, (void *) (args + i));
    }

    for (i = 0; i < qtThreads; i++) {
        pthread_join(threads[i], NULL);
    }
}
