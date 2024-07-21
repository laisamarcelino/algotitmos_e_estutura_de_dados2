#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordenacao.h" 

void imprime_vetor(int vetor[], size_t tamVetor){
    for (size_t i=0; i<tamVetor; i++){
        printf("%d ", vetor[i]);
    }
}

void criar_vetor_decrescente(int vetor[], size_t tamVetor){ 
    for(size_t i = 0; i < tamVetor; i++){
        vetor[i] = tamVetor-i;
    }
}

int aleat (int min, int max){ 
	return min + rand() % (max+1 - min);
}

void criar_vetor_aleatorio(int vetor[], size_t tamVetor){ 
    for(size_t i = 0; i < tamVetor; i++){
        vetor[i] = aleat(0, tamVetor);
    }
}

void criar_vetor_crescente(int vetor[], size_t tamVetor){ 
    for(size_t i = 0; i < tamVetor; i++){
        vetor[i] = i;
    }
}

int criar_vetor(int vetor[], size_t tamVetor, int caso){
    switch (caso) {
    case 1:
        criar_vetor_decrescente(vetor, tamVetor);
        return 1;
    case 2:
        criar_vetor_aleatorio(vetor, tamVetor);
        return 2;
    case 3:
        criar_vetor_crescente(vetor, tamVetor);
        return 3;
    default:
        break;
    }
    return 0;
}

int main() {
    char nome[MAX_CHAR];
    size_t tamVetor=10;
    uint64_t numComp;
    clock_t start, end;  
    double total;
    int caso;
    
    srand(0); /*inicia a semente randomica*/

    int* vetor = (int*)malloc(tamVetor * sizeof(int));
    if (vetor == NULL) {
        printf("Falha fatal. Impossível alocar memoria.");
        return 1;
    }

    getNome(nome);
    printf("Trabalho de %s\n", nome);
    printf("GRR %u\n", getGRR());
    
    printf("Escolha o tipo de ordenação do vetor\n1: Decrescente\n2: Aleatório\n3: Crescente\n");
    scanf("%d", &caso);

    printf ("Teste 0: imprime vetor original:\n");
    criar_vetor(vetor, tamVetor, caso);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 1: Ordena vetor com o MergeSort recursivo:\n"); 
    start = clock(); 
    numComp = mergeSort(vetor, tamVetor);
    end = clock();
    total = ((double)end - start) / CLOCKS_PER_SEC;
    printf("N° de comparações: %ld\n", numComp);
    printf("Tempo de execução: %f segundos\n", total);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 2: Ordena vetor com o QuickSort recursivo:\n"); 
    criar_vetor(vetor, tamVetor, caso);imprime_vetor(vetor, tamVetor);
    start = clock(); 
    numComp = quickSort(vetor, tamVetor);
    end = clock();
    total = ((double)end - start) / CLOCKS_PER_SEC;
    printf("N° de comparações: %ld\n", numComp);
    printf("Tempo de execução: %f segundos\n", total);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 3: Ordena vetor com o HeapSort recursivo:\n"); 
    criar_vetor(vetor, tamVetor, caso);imprime_vetor(vetor, tamVetor);
    start = clock(); 
    numComp = heapSort(vetor, tamVetor);
    end = clock();
    total = ((double)end - start) / CLOCKS_PER_SEC;
    printf("N° de comparações: %ld\n", numComp);
    printf("Tempo de execução: %f segundos\n", total);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 4: Ordena vetor com o MergeSort sem recursão:\n");
    criar_vetor(vetor, tamVetor, caso);imprime_vetor(vetor, tamVetor);
    start = clock(); 
    numComp = mergeSortSR(vetor, tamVetor);
    end = clock();
    total = ((double)end - start) / CLOCKS_PER_SEC;
    printf("N° de comparações: %ld\n", numComp);
    printf("Tempo de execução: %f segundos\n", total);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 5: Ordena vetor com o QuickSort sem recursão:\n");
    criar_vetor(vetor, tamVetor, caso);imprime_vetor(vetor, tamVetor);
    start = clock(); 
    numComp = quickSortSR(vetor, tamVetor);
    end = clock();
    total = ((double)end - start) / CLOCKS_PER_SEC;
    printf("N° de Comparações: %ld\n", numComp);
    printf("Tempo de execução: %f segundos\n", total);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    printf ("Teste 6: Ordena vetor com o HeapSort sem recursão:\n");
    criar_vetor(vetor, tamVetor, caso);imprime_vetor(vetor, tamVetor);
    start = clock(); 
    numComp = heapSortSR(vetor, tamVetor);
    end = clock();
    total = ((double)end - start) / CLOCKS_PER_SEC;
    printf("N° de Comparações: %ld\n", numComp);
    printf("Tempo de execução: %f segundos\n", total);
    imprime_vetor(vetor, tamVetor);
    printf ("\n\n");

    free(vetor);

    return 0;
}
