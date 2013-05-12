
#include "quicksort_privado.h"

void *separar(void *arg) {
    int i, comparacao;
    Nolista *atual;
    PaThreadSeparar *tParam = (PaThreadSeparar *) arg;
    //int pivoData = *((int *) tParam->pivo->dado);
    //printf("Thread -> Separar id= %d, pivo= %d, inicio= %d, deslocamento= %d, \n", tParam->threadId, pivoData, tParam->inicio, tParam->deslocamento);
    criarLista(tParam->maiores, tParam->dataSize);
    criarLista(tParam->menores, tParam->dataSize);
    if (tParam->deslocamento == 0){
        return NULL;
    }
    buscaNoPos(tParam->lista, &atual, tParam->inicio);
    // printf("%d - Buscando : %d, Pivo : %d\n", tParam->threadId, *((int *) atual->dado), *((int *) tParam->pivo->dado));
    for (i = 0; i < tParam->deslocamento; i++) {
        //// printf("%d - Comparando : %d - %d\n", tParam->threadId, *((int *) atual->dado), *((int *) tParam->pivo->dado));

        comparacao = tParam->cmp(atual->dado, tParam->pivo->dado);
        //// printf("%d - Resultado : %d\n", tParam->threadId, comparacao);
        if (comparacao > 0) {
            addFim(*tParam->maiores, atual->dado);
        } else {
            addFim(*tParam->menores, atual->dado);
        }
        atual = atual->proximo;
    }
    //printf("%d - Maiores -> ", tParam->threadId);
    //toString(*tParam->maiores);
    //printf("%d - Menores -> ", tParam->threadId);
    //toString(*tParam->menores);
    return NULL;
}

void ordenarSozinho(pLista p, ppLista ordenada, int (*cmp)(void *d1, void *d2), pNoLista m, pNoLista n, int i, int j) {
    pNoLista pivo = m;
    int ii = i, jj = j;
    Nolista *inicio, *fim;
    // printf("------> Ordenar sozinho\n");
    if(i >= j) return;
    inicio = m->proximo;
    fim = n;
//    criarLista(ordenada, p->tInfo);
    i++;
    
//    if(p->size == 1) {
//        acrescentarInicio((*ordenada), p);
//        return;
//    }
    
//    // printf("condicao inicial | %d <= %d\n",i,j);
    while(i <= j) {
//        // printf("> ville pai\n");
        while((i <= jj) && (cmp(inicio->dado, pivo->dado) <= 0)) {
            if((inicio != NULL))
                inicio = inicio->proximo;
            i++;
        }
        while((j >= ii) && (cmp(fim->dado, pivo->dado) > 0)) {
            if((fim != NULL))
                fim = fim->anterior;
            j--;
        }
//        // printf(">> ville == %d - %d\n", i, j);
        if(i < j) {
            swap(&inicio, &fim);
        }
        
    }
    swap(&m, &fim);
    ordenarSozinho(p, ordenada, cmp, m, fim->anterior, ii, j-1);
    ordenarSozinho(p, ordenada, cmp, fim->proximo, n, j+1, jj);
    (*ordenada) = p;
//    toString(p);
}

void ordenarMultiThread(pLista p, ppLista ordenada, int qtThreads, int (*cmp)(void *d1, void *d2)) {
    int qtDiv = (p->size - 1) / qtThreads;
    int qtIni = qtDiv + ((p->size - 1) % qtThreads);
    int i;

    pthread_t *threads;
    PaThreadSeparar *args;

    pLista *maiores, *menores, maioresJuntos, menoresJuntos, ordenadaMenores, ordenadaMaiores;

    threads = (pthread_t *) malloc(qtThreads * sizeof (pthread_t));
    args = (PaThreadSeparar *) malloc(qtThreads * sizeof (PaThreadSeparar));
    maiores = (pLista *) malloc(qtThreads * sizeof (pLista));
    menores = (pLista *) malloc(qtThreads * sizeof (pLista));

//    printf("Ordenar qtThreads = %d, qtDiv = %d, qtIni = %d\n", qtThreads, qtDiv, qtIni);
    for (i = 0; i < qtThreads; i++) {
        args[i].threadId = i;
        args[i].cmp = cmp;
        args[i].dataSize = p->tInfo;
        args[i].pivo = p->inicio;
        args[i].lista = p;
        args[i].maiores = &maiores[i];
        args[i].menores = &menores[i];
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
    
    maioresJuntos = maiores[0];
    menoresJuntos = menores[0];
    
    for (i = 1; i < qtThreads; i++) {
        //toString(maioresJuntos);
        //toString(maiores[i]);
        acrescentarFim(maioresJuntos, maiores[i]);
        //printf("Somado Maiores -> ");
        //toString(maioresJuntos);
        
        //toString(menoresJuntos);
        //toString(menores[i]);
        acrescentarFim(menoresJuntos, menores[i]);
        //printf("Somado Menores -> ");
        //toString(menoresJuntos);
    }
    free(threads);
    free(args);
    free(maiores);
    free(menores);
    
    // printf("Menores Juntos -> ");
//    toString(menoresJuntos);
    // printf("Maiores Juntos -> ");
//    toString(maioresJuntos);
     //printf("Comparando tamanho %d > %d\n", menoresJuntos->size, (qtThreads * THREAD_ORDENA));
    
    if (menoresJuntos->size >= (qtThreads * THREAD_ORDENA)){
        // printf("----------------------->>          Ordenando os menores com todas as threads\n");
        ordenar(menoresJuntos, &ordenadaMenores, qtThreads, cmp);
        // printf("----------------------->>          Terminou de ordenar os menores com todas as threads\n");
        // printf("----------------------->>          Ordenando os maiores com todas as threads\n");
        ordenar(maioresJuntos, &ordenadaMaiores, qtThreads, cmp);
        // printf("----------------------->>          Terminou de ordenar os maiores com todas as threads\n");
    } else {
        //printf("Ta caindo aqui\n");
        i = menoresJuntos->size / THREAD_ORDENA;
        i = i == 0 ? 1 : i;
        //printf("Ta caindo aqui %d\n", i);
        ordenar(menoresJuntos, &ordenadaMenores, i, cmp);
        // printf("Ta caindo aqui\n");
//        toString(menoresJuntos);
        ordenar(maioresJuntos, &ordenadaMaiores, (qtThreads - i), cmp);
//        toString(maioresJuntos);
    }
    criarLista(ordenada, p->tInfo);
    //printf("addInicio antes %d\n", (* ordenada)->size);
    addInicio((* ordenada), p->inicio->dado);
    //printf("addInicio depois %d\n", (* ordenada)->size);
    acrescentarInicio((* ordenada), ordenadaMenores);
    acrescentarFim((* ordenada), ordenadaMaiores);
    // printf("modafoca\n");
//    toString((* ordenada));
}

void ordenar(pLista p, ppLista ordenada, int qtThreads, int (*cmp)(void *d1, void *d2)) {
    criarLista(ordenada, p->tInfo);
    if (p->size == 0){
        // printf("--------------------------->>          Não tinha nada para ordenar\n");
        return;
    }
    if (p->size == 1){
        // printf("--------------------------->>          Só tinha 1 item\n");
        acrescentarFim((* ordenada), p);
        return;
    }
    if (qtThreads == 1){
        ordenarSozinho(p, ordenada, cmp, p->inicio, p->fim, 0, p->size-1);
    } else {
        ordenarMultiThread(p, ordenada, qtThreads, cmp);
    }
}
