#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordenacao.h" 

void imprime_vetor(int vetor[], size_t tamVetor){
    for (size_t i=0; i<tamVetor; i++){
        printf("%d ", vetor[i]);
    }
}

void cria_vetor(int vetor[], size_t tamVetor){ 
    for(size_t i=0; i<tamVetor; i++){
        vetor[i] = tamVetor-i;
    }
}

/* ------------------------------------------------------------- */

int main() {
    char nome[MAX_CHAR];
    size_t tamVetor = 10;
    uint64_t numComp;

    int* vetor = (int*)malloc(tamVetor * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
    }

    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR());

    printf ("Teste 0: cria vetor decrescente de 100 posições:\n");
    cria_vetor(vetor, tamVetor);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 1: ordena vetor com o MergeSort recursivo:\n"); 
    numComp = mergeSort(vetor, tamVetor);
    printf("N° de comparações nlog(2)n = ~ 33.21928 ~ %ld\n", numComp);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 2: ordena vetor com o QuickSort recursivo:\n"); 
    cria_vetor(vetor, tamVetor);
    numComp = quickSort(vetor, tamVetor);
    printf("N° de Comparações (n²+n-2)/2 = 54 = %ld\n", numComp);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 3: ordena vetor com o HeapSort recursivo:\n"); 
    cria_vetor(vetor, tamVetor);
    numComp = heapSort(vetor, tamVetor);
    printf("N° de Comparações 2nlog(2)n ~ 66.43856 ~ %ld\n", numComp);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 4: ordena vetor com o MergeSort sem recursão:\n");
    cria_vetor(vetor, tamVetor);
    numComp = mergeSortSR(vetor, tamVetor);
    printf("N° de Comparações nlog(2)n = ~ 33.21928 ~ %ld\n", numComp);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 5: ordena vetor com o QuickSort sem recursão:\n");
    cria_vetor(vetor, tamVetor);
    numComp = quickSortSR(vetor, tamVetor);
    printf("N° de Comparações (n²+n-2)/2 = 54 = %ld\n", numComp);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 6: ordena vetor com o HeapSort sem recursão:\n");
    cria_vetor(vetor, tamVetor);
    numComp = heapSortSR(vetor, tamVetor);
    printf("N° de Comparações 2nlog(2)n ~ 66.43856 ~ %ld\n", numComp);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    free(vetor);

    return 0;
}
