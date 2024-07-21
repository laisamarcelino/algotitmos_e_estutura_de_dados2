#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ordenacao.h" 

void imprime(int vetor[], size_t tamVetor){
    for (int i=0; i<tamVetor; i++){
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void vetorDescrescente(int vetor[], size_t tamVetor){ 
    for(int i=0; i<tamVetor; i++){
        vetor[i] = tamVetor-i;
    }
}

int main() {
    char nome[MAX_CHAR];
    /*int numComp; */

    size_t tamVetor = 20;
    int* vetor = (int*)malloc(tamVetor * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
    }

    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR());
    /*numComp = mergeSort(vetor, tamVetor); // = nlog2(n)*/
    /*printf("NumComp: %d\n", numComp);*/
    /*TESTE*/
    vetorDescrescente(vetor, tamVetor);
    printf("Vetor original:\n");
    imprime(vetor, tamVetor);
/*
    mergeSort(vetor, tamVetor);
    printf("Merge normal:\n");
    imprime(vetor, tamVetor);
*/
   
    quickSort(vetor, tamVetor);
    printf("Quick normal:\n");
    imprime(vetor, tamVetor);
    
/*    
    heapSort(vetor, tamVetor);
    printf("Heap normal:\n");
    imprime(vetor, tamVetor);
    
    
    quickSortSR(vetor, tamVetor);
    printf("Quick sem recursao:\n");
    imprime(vetor, tamVetor);
    
    
    heapSortSR(vetor, tamVetor);
    printf("Heap sem recursao:\n");
    imprime(vetor, tamVetor);
*/
    free(vetor);

    return 0;
}
