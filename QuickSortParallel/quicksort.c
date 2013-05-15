
#include "quicksort_privado.h"

void *separar(void *arg) {
    int i, comparacao, endereco;
    Nolista *blocoAtual;
    PaThreadSeparar *tParam = (PaThreadSeparar *) arg;
    ///int pivoData = *((int *) tParam->pivo);
    //printf("Thread -> Separar id= %d, pivo= %d, inicio= %d, deslocamento= %d, \n", tParam->threadId, pivoData, tParam->inicio, tParam->deslocamento);
    criarLista(tParam->maiores, tParam->dataSize, tParam->deslocamento);
    criarLista(tParam->menores, tParam->dataSize, tParam->deslocamento);
    if (tParam->deslocamento == 0) {
        return NULL;
    }
    endereco = (tParam->inicio - 1) % tParam->lista->blockSize;
    //printf("%d - Buscando : Endereço : %d\n", tParam->threadId, endereco);
    buscaNoPos(tParam->lista, &blocoAtual, tParam->inicio);

    //printf("%d - Buscando : %d, Pivo : %d\n", tParam->threadId, *(((int *) blocoAtual->dado)+endereco), *((int *) tParam->pivo));
    for (i = 0; i < tParam->deslocamento; i++) {

        //printf("%d - Comparando : %d - %d\n", tParam->threadId, *(((int *) blocoAtual->dado)+endereco), *((int *) tParam->pivo));

        comparacao = tParam->cmp((((int *) blocoAtual->dado) + endereco), tParam->pivo);
        //printf("%d - Resultado : %d\n", tParam->threadId, comparacao);
        if (comparacao > 0) {
            addFim(*tParam->maiores, (((int *) blocoAtual->dado) + endereco));
        } else {
            addFim(*tParam->menores, (((int *) blocoAtual->dado) + endereco));
        }
        endereco = (endereco + 1) % tParam->lista->blockSize;
        if (endereco == 0) {
            //printf("%d - Pulou de bloco\n", tParam->threadId);
            blocoAtual = blocoAtual->proximo;
        }
        //endereco++;
    }
    //printf("%d - Maiores -> ", tParam->threadId);
    //toString(*tParam->maiores);
    //printf("%d - Menores -> ", tParam->threadId);
    //toString(*tParam->menores);
    return NULL;
}

void ordenarSozinho(pLista p, int (*cmp)(void *d1, void *d2), int m,int n){
    //int list[10];
    pNoLista no  = p->inicio;
    void* pivo = no->dado+(m*p->tInfo);
    
    //int pivoData = *((int *) pivo);
    //printf("------------------>>>>>>>>>>>>    ordenarSozinho -> m = %d, n = %d, pivo= %d   ", m, n, pivoData);
    //toString(p);
    int i,j;
    
    if (m >= n) {
        return;
    }
    //k = choose_pivot(m,n);
    //swap(&list[m],&list[k]);
    //key = list[m];
    i = m+1;
    j = n;

    while(i <= j) {
        //printf("> ville pai i= %d <= j = %d\n", i, j);
        //printf("While 1 -> i= %d, n=%d, cmp=%d\n", i, n, cmp(no->dado+(i*p->tInfo), pivo));
        while((i <= n) && (cmp((no->dado+(i*p->tInfo)), pivo) <= 0)  /*(list[i] <= key)*/){
            //printf("While 1 -> i= %d, n=%d, cmp=%d\n", i, n, cmp(no->dado+(i*p->tInfo), pivo));
            i++;
        }
        //printf("While 2 -> j= %d, m=%d, cmp=%d\n", j, m, cmp(no->dado+(j*p->tInfo), pivo));
        while((j >= m) && (cmp((no->dado+(j*p->tInfo)), pivo) > 0)/*(list[j] > key)*/){
            //printf("While 2 -> j= %d, m=%d, cmp=%d\n", j, m, cmp(no->dado+(j*p->tInfo), pivo));
            j--;
        }
        if( i < j){
            //toString(p);
            swap(p->inicio, i, j, p->tInfo);
            //toString(p);
        }
    }
    /* swap two elements */
    swap(p->inicio, m,j, p->tInfo);
    /* recursively sort the lesser list */
    ordenarSozinho(p, cmp, m,j-1);
    ordenarSozinho(p, cmp, j+1,n);
}

void ordenarMultiThread(pLista p, ppLista ordenada, int qtThreads, int (*cmp)(void *d1, void *d2)) {
    int qtDiv = (p->size - 1) / qtThreads;
    int qtIni = qtDiv + ((p->size - 1) % qtThreads);
    int i;

    pthread_t *threads;
    PaThreadSeparar *args;

    pLista *maiores, *menores, maioresJuntos, menoresJuntos, ordenadaMenores, ordenadaMaiores, tempList;

    threads = (pthread_t *) malloc(qtThreads * sizeof (pthread_t));
    args = (PaThreadSeparar *) malloc(qtThreads * sizeof (PaThreadSeparar));
    maiores = (pLista *) malloc(qtThreads * sizeof (pLista));
    menores = (pLista *) malloc(qtThreads * sizeof (pLista));

    //    printf("Ordenar qtThreads = %d, qtDiv = %d, qtIni = %d\n", qtThreads, qtDiv, qtIni);
    for (i = 0; i < qtThreads; i++) {
        args[i].threadId = i;
        args[i].cmp = cmp;
        args[i].dataSize = p->tInfo;
        args[i].pivo = p->inicio->dado;
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
        acrescentarFim(maioresJuntos, maiores[i], &tempList);
        //destruirLista(&maioresJuntos);
        //destruirLista(&(maiores[i]));
        maioresJuntos = tempList;
        //printf("Somado Maiores -> ");
        //toString(maioresJuntos);

        //toString(menoresJuntos);
        //toString(menores[i]);
        acrescentarFim(menoresJuntos, menores[i], &tempList);
        //destruirLista(&menoresJuntos);
        //destruirLista(&(menores[i]));
        menoresJuntos = tempList;
        //printf("Somado Menores -> ");
        //toString(menoresJuntos);
    }
    free(threads);
    free(args);
    free(maiores);
    free(menores);

    /*
    printf("Menores Juntos -> ");
    toString(menoresJuntos);
    printf("Maiores Juntos -> ");
    toString(maioresJuntos);
    */
    //printf("Comparando tamanho %d > %d\n", menoresJuntos->size, (qtThreads * THREAD_ORDENA));

    if (menoresJuntos->size >= (qtThreads * THREAD_ORDENA)) {
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
    criarLista(ordenada, p->tInfo, p->blockSize);
    //addFim((* ordenada), p->inicio->dado);
    acrescentarInicio((* ordenada), ordenadaMenores);
    //acrescentarFim((* ordenada), ordenadaMaiores);
    
   addFim(ordenadaMenores, p->inicio->dado);
   acrescentarFim(ordenadaMenores, ordenadaMaiores, ordenada);
     

    // printf("modafoca\n");
    //    toString((* ordenada));*/
}

void ordenar(pLista p, ppLista ordenada, int qtThreads, int (*cmp)(void *d1, void *d2)) {
    criarLista(ordenada, p->tInfo, p->blockSize);
    if (p->size == 0) {
        // printf("--------------------------->>          Não tinha nada para ordenar\n");
        return;
    }
    if (p->size == 1) {
        //printf("--------------------------->>          Só tinha 1 item\n");
        pLista tempList;
        criarLista(&tempList, p->tInfo, p->blockSize);
        acrescentarFim(p, tempList, ordenada);
        return;
    }
    if (qtThreads == 1) {
        //ordenarSozinho(p, ordenada, cmp, p->inicio, p->fim, 0, p->size - 1);
        ordenarSozinho(p, cmp, 0, p->size - 1);
        (* ordenada) = p;
    } else {
        ordenarMultiThread(p, ordenada, qtThreads, cmp);
    }
}
