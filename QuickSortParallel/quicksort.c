
#include "quicksort_privado.h"

void *separar(void *arg) {
    int i, comparacao;
    Nolista *atual;
    param_t *tParam = (param_t *) arg;
    int pivoData = *((int *) tParam->pivo->dado);
    atual = (Nolista *) malloc(sizeof (Nolista));
    atual->dado = malloc(tParam->dataSize);
    
    printf("Thread -> Separar id= %d, pivo= %d, inicio= %d, deslocamento= %d, \n", tParam->threadId, pivoData, tParam->inicio, tParam->deslocamento);
    criarLista(&tParam->maiores, tParam->dataSize);
    criarLista(&tParam->menores, tParam->dataSize);
    buscaPos(tParam->lista, atual->dado, tParam->inicio);
    printf("%d - Buscando : %d\n", tParam->threadId, *((int *) atual->dado));
    
    for (i = 0; i < tParam->deslocamento; i++) {
        printf("%d - Comparando : %d - %d\n", tParam->threadId, *((int *) atual->dado), *((int *) tParam->pivo->dado));
        comparacao = tParam->cmp(atual->dado, tParam->pivo->dado);
        printf("%d - Resultado : %d\n", tParam->threadId, comparacao);
        if (comparacao > 0) {
            addFim(tParam->maiores, atual->dado);
        } else {
            addFim(tParam->menores, atual->dado);
        }
        atual = atual->proximo;
    }
    return NULL;
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
    maiores = (pLista *) malloc(qtThreads * sizeof (pLista));
    menores = (pLista *) malloc(qtThreads * sizeof (pLista));

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
            args[i].inicio = 2;
            args[i].deslocamento = qtIni;
        } else {
            args[i].inicio = 2 + qtIni + ((i - 1) * qtDiv);
            args[i].deslocamento = qtDiv;
        }
        pthread_create(&threads[i], NULL, separar, (void *) (args + i));
    }

    for (i = 0; i < qtThreads; i++) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
    free(args);
    for (i = 1; i < qtThreads; i++) {
        acrescentarFim(maiores[0], maiores[i]);
        acrescentarFim(menores[0], menores[i]);
    }

    toString(maiores[0]);
    toString(menores[0]);
}
