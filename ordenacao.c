#include "ordenacao.h"
#include "pilha.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void getNome(char nome[]) {
    strncpy(nome, "Laisa Marcelino Santos Rodrigues", MAX_CHAR);
    /* adicionada terminação manual para caso de overflow*/
    nome[MAX_CHAR - 1] = '\0';
}

/* a função a seguir retorna o número de GRR*/
uint32_t getGRR() { return 20243783; }

/* Realiza a cópia de um vetor */
void copiar(int vetor[], int aux[], size_t a, size_t b){
    for(size_t i=0; i<=b-a;i++)
        vetor[a+i] = aux[i];
} 

/* Troca a posição de dois valores em um vetor */
void trocar(int vetor[], size_t a, size_t b){
    int aux;
    aux = vetor[a];
    vetor[a] = vetor[b];
    vetor[b] = aux;
} 
/* ----------- Funções do MergeSort ----------- */

/* Mescla dois vetores ordenados gerando um único vetor ordenado */
void merge(int vetor[], size_t a, size_t m, size_t b, uint64_t* numComparacoes){
    size_t i, j, p;
    int *aux = (int *)malloc((b - a + 1) * sizeof(int));

    i = a;
    j = m+1;

    if (a>=b){
        free(aux);
        return;
    }

    for(size_t k = 0; k <= b-a; k++){
        if( j > b || (i <= m && vetor[i] <= vetor[j])){
            p = i;
            i++;
        } 
        else{
            p = j;
            j++;
        }
        aux[k] = vetor[p];
        *numComparacoes += 1;
    }
    copiar(vetor, aux, a, b);
    free(aux);
}

/* Ordenação recursiva de um vetor a partir dos indices inicial e final*/
void mergeSortAuxiliar(int vetor[], size_t a, size_t b, uint64_t* numComparacoes){
    size_t m;

    if(a >= b)
        return;

    m = (a+b) >> 1;
    
    mergeSortAuxiliar(vetor, a, m, numComparacoes);
    mergeSortAuxiliar(vetor, m+1, b, numComparacoes);
    merge(vetor, a, m, b, numComparacoes);
}

/* Ordenação iterativa de um vetor a partir dos indices inicial e final*/
void mergeSortAuxiliarSR(int vetor[], size_t a, size_t b, uint64_t* numComparacoes){
    struct pilha *p;
    size_t m;

    p = pilha_cria();
    empilhar(p, a);
    empilhar(p, b);
    
    while (!pilha_vazia(p)){
        desempilhar(p, &b);
        desempilhar(p, &a);
        
        if (a < b){
            m = (a+b) >> 1;
            
            empilhar(p, a);
            empilhar(p, m);
            empilhar(p, m+1);
            empilhar(p, b);
            merge(vetor, a, m, b, numComparacoes);
        }
    }
    
    pilha_destroi(&p);   
}

uint64_t mergeSort(int vetor[], size_t tam) { 
    uint64_t numComparacoes=0;

    mergeSortAuxiliar(vetor, 0, tam - 1, &numComparacoes);
    return numComparacoes;
}

uint64_t mergeSortSR(int vetor[], size_t tam) {
    uint64_t numComparacoes=0;

    mergeSortAuxiliarSR(vetor, 0, tam-1, &numComparacoes);
    return numComparacoes;
}

/* ----------- Funções do QuickSort ----------- */

/* Particiona um vetor a partir de um pivô */
size_t particionar(int vetor[], size_t a, size_t b, uint64_t *numComparacoes){ 
    size_t m = a;
   
    for (size_t i = a; i <= b - 1; i++){ 
        (*numComparacoes)++;
        if (vetor[i] <= vetor[b]){
            trocar(vetor, m, i);
            m++;
        }
    }
    trocar(vetor, m, b);

    return m; 
}

/* Ordenação recursiva de um vetor a partir dos indices inicial e final*/
void quickSortAuxiliar(int vetor[], size_t a, size_t b, uint64_t *numComparacoes){
    size_t m;

    if (a >= b)
        return;

    (*numComparacoes)++;
    m = particionar(vetor, a, b, numComparacoes); 

    /* Verifica para evitar acesso inválido a memória*/
    if (m > 0)
        quickSortAuxiliar(vetor, a, m-1, numComparacoes);
    quickSortAuxiliar(vetor, m+1, b, numComparacoes);

}

/* Ordenação iterativa de um vetor a partir dos indices inicial e final*/
void quickSortAuxiliarSR(int vetor[], size_t a, size_t b, uint64_t *numComparacoes){
    struct pilha *p;
    size_t m;

    p = pilha_cria();
    empilhar(p, a);
    empilhar(p, b);

    while (!pilha_vazia(p)){
        desempilhar(p, &b);
        desempilhar(p, &a);

        if (a < b){
            m = particionar(vetor, a, b, numComparacoes);
            (*numComparacoes)++;
            if (m > 0){
                empilhar(p, a);
                empilhar(p, m-1); 
            }
            empilhar(p, m+1);
            empilhar(p, b);
        }
    }
    pilha_destroi(&p);
}

uint64_t quickSort(int vetor[], size_t tam) {
    uint64_t numComparacoes=0;

    quickSortAuxiliar(vetor, 0, tam - 1, &numComparacoes);
    return numComparacoes;
}

uint64_t quickSortSR(int vetor[], size_t tam) {
    uint64_t numComparacoes=0;

    quickSortAuxiliarSR(vetor, 0, tam - 1, &numComparacoes);
    return numComparacoes;
}

/* ----------- Funções do HeapSort ----------- */

/* Retorna o indice do filho esquerdo de uma heap */
size_t indiceFilhoEsquerdo(size_t i){
    return (i << 1) + 1; 
}

/* Retorna o indice do filho direito de uma heap */
size_t indiceFilhoDireito(size_t i){
    return (i << 1) + 2; 
}

void maxHeapify(int vetor[], size_t i, size_t tam, uint64_t *numComparacoes){
    size_t l, r, maior;

    l = indiceFilhoEsquerdo(i);
    r = indiceFilhoDireito(i);

    (*numComparacoes)++;
    if (l <= tam-1 && vetor[l] > vetor[i])
        maior = l;

    else 
        maior = i;

    (*numComparacoes)++;
    if (r <= tam-1 && vetor[r] > vetor[maior])
        maior = r;
  
    if (maior != i){
        trocar(vetor, i, maior);
        maxHeapify(vetor, maior, tam, numComparacoes);
    }
}

/* Constroi uma max heap */
void contruirMaxHeap(int vetor[], size_t tam, uint64_t *numComparacoes){
    for (ssize_t i = (ssize_t)(tam >> 1)-1; i >= 0; i--)
        maxHeapify(vetor, i, tam, numComparacoes);
}

uint64_t heapSort(int vetor[], size_t tam) {
    uint64_t numComparacoes=0;

    contruirMaxHeap(vetor, tam, &numComparacoes);
    
    for (size_t i = tam-1; i > 0; i--){
        trocar(vetor, 0, i);
        maxHeapify(vetor, 0, i, &numComparacoes);
    }
    return numComparacoes;
}

void maxHeapifySR(int vetor[], size_t i, size_t tam, uint64_t *numComparacoes){
    size_t l, r, maior;
    
    while (1){
        l = indiceFilhoEsquerdo(i);
        r = indiceFilhoDireito(i);
        maior = i;
        
        (*numComparacoes)++;
        if (l <= tam-1 && vetor[l] > vetor[i])
            maior = l;

        (*numComparacoes)++;
        if (r <= tam-1 && vetor[r] > vetor[maior])
            maior = r;
        
        if (maior != i){
            trocar(vetor, i, maior);
            i = maior;
        }
        else 
            break;
    }
}

void contruirMaxHeapSR(int vetor[], size_t tam, uint64_t *numComparacoes){
    for (ssize_t i = (ssize_t)(tam >> 1)-1; i >= 0; i--)
        maxHeapifySR(vetor, i, tam, numComparacoes);
}

uint64_t heapSortSR(int vetor[], size_t tam) {
    uint64_t numComparacoes=0;

    contruirMaxHeapSR(vetor, tam, &numComparacoes);
    
    for (size_t i = tam-1; i > 0; i--){
        trocar(vetor, 0, i);
        maxHeapifySR(vetor, 0, i, &numComparacoes);
    }
    return numComparacoes;
}