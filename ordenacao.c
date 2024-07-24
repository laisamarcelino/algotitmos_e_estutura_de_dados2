#include "ordenacao.h"
#include "pilha.h"
#include <string.h>
#include <stdlib.h>

void getNome(char nome[]) {
    strncpy(nome, "Laisa Marcelino Santos Rodrigues", MAX_CHAR);
    /* adicionada terminação manual para caso de overflow*/
    nome[MAX_CHAR - 1] = '\0';
}

/* Retorna o número de GRR*/
uint32_t getGRR() { return 20243783; }

/* Troca a posição de dois valores em um vetor */
void trocar(int vetor[], size_t a, size_t b){
    int aux;
    aux = vetor[a];
    vetor[a] = vetor[b];
    vetor[b] = aux;
} 

/* ----------- Funções do MergeSort ----------- */

/* Realiza a cópia de um vetor */
void copiar(int* vetor, int* aux, size_t a, size_t b) {
     for(size_t i = 0 ; i <= b-a; i++)
        vetor[a+i] = aux[i];
}

/* Mescla dois vetores ordenados gerando um único vetor ordenado */
void merge(int vetor[], size_t a, size_t m, size_t b, uint64_t* numComp){
    size_t i, j, p;
    int *aux = (int*)malloc((b - a + 1) * sizeof(int));

    i = a;
    j = m + 1;

    if (a >= b){
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
        (*numComp)++;
    }
    copiar(vetor, aux, a, b);
    free(aux);
}

/* Ordenação recursiva de um vetor a partir dos indices inicial e final*/
void mergeSortAuxiliar(int vetor[], size_t a, size_t b, uint64_t* numComp){
    size_t m;

    if(a >= b)
        return;

    m = (a+b) >> 1;
    
    mergeSortAuxiliar(vetor, a, m, numComp);
    mergeSortAuxiliar(vetor, m+1, b, numComp);
    merge(vetor, a, m, b, numComp);
}

/* Função principal do mergeSort */
uint64_t mergeSort(int vetor[], size_t tam) { 
    uint64_t numComp=0;

    mergeSortAuxiliar(vetor, 0, tam - 1, &numComp);
    return numComp;
}
/* Ordenação iterativa de um vetor a partir do tam - bottom-up mergeSort*/
uint64_t mergeSortSR(int vetor[], size_t tam) {
    uint64_t numComp = 0;
    size_t m, fim_sub; 

    for (size_t tam_sub = 1; tam_sub < tam; tam_sub *= 2) {
        for (size_t ini_sub = 0; ini_sub < tam - tam_sub; ini_sub += tam_sub + tam_sub) {
            m = ini_sub + tam_sub - 1;
            if (ini_sub + tam_sub + tam_sub - 1 < tam - 1)
                fim_sub = ini_sub + tam_sub + tam_sub - 1;
            else
                fim_sub = tam - 1;
            merge(vetor, ini_sub, m, fim_sub, &numComp);
        }
    }

    return numComp;
}

/* ----------- Funções do QuickSort ----------- */

/* Particiona um vetor a partir de um pivô */
size_t particionar(int vetor[], size_t a, size_t b, uint64_t *numComp){ 
    size_t m = a;
   
    for (size_t i = a; i <= b - 1; i++){ 
        (*numComp)++;
        if (vetor[i] <= vetor[b]){
            trocar(vetor, m, i);
            m++;
        }
    }
    trocar(vetor, m, b);

    return m; 
}

/* Ordenação recursiva de um vetor a partir dos indices inicial e final*/
void quickSortAuxiliar(int vetor[], size_t a, size_t b, uint64_t *numComp){
    size_t m;

    if (a >= b)
        return;

    m = particionar(vetor, a, b, numComp); 

    /* Verifica para evitar acesso inválido a memória*/
    if (m > 0)
        quickSortAuxiliar(vetor, a, m-1, numComp);
    quickSortAuxiliar(vetor, m+1, b, numComp);

}
/* Função principal do quickSort */
uint64_t quickSort(int vetor[], size_t tam) {
    uint64_t numComp=0;

    quickSortAuxiliar(vetor, 0, tam - 1, &numComp);
    return numComp;
}

/* Ordenação iterativa de um vetor a partir dos indices inicial e final*/
void quickSortAuxiliarSR(int vetor[], size_t a, size_t b, uint64_t *numComp){
    struct pilha *p;
    size_t m, ini, fim;

    p = pilha_cria();
    empilhar(p, a, b);

    while (!pilha_vazia(p)){
        desempilhar(p, &ini, &fim);

        if (ini < fim){
            (*numComp)++;
            m = particionar(vetor, ini, fim, numComp);
            if (m > ini){
                empilhar(p, ini, m-1);
            }
            empilhar(p, m+1, fim);
        }
    }
    pilha_destroi(&p);
}

uint64_t quickSortSR(int vetor[], size_t tam) {
    uint64_t numComp=0;

    quickSortAuxiliarSR(vetor, 0, tam - 1, &numComp);
    return numComp;
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

/* Garante que a propriedade da max-heap seja mantida */
void maxHeapify(int vetor[], size_t i, size_t tam, uint64_t *numComp){
    size_t l, r, maior;

    l = indiceFilhoEsquerdo(i);
    r = indiceFilhoDireito(i);

    (*numComp)++;
    if (l <= tam-1 && vetor[l] > vetor[i])
        maior = l;

    else 
        maior = i;

    (*numComp)++;
    if (r <= tam-1 && vetor[r] > vetor[maior])
        maior = r;
  
    if (maior != i){
        trocar(vetor, i, maior);
        maxHeapify(vetor, maior, tam, numComp);
    }
}

/* Constroi uma max heap */
void contruirMaxHeap(int vetor[], size_t tam, uint64_t *numComp){
    for (ssize_t i = (ssize_t)(tam >> 1)-1; i >= 0; i--)
        maxHeapify(vetor, i, tam, numComp);
}

/* Ordena recursiva de um vetor a partir do tam */
uint64_t heapSort(int vetor[], size_t tam) {
    uint64_t numComp=0;

    contruirMaxHeap(vetor, tam, &numComp);
    
    for (size_t i = tam-1; i > 0; i--){
        trocar(vetor, 0, i);
        maxHeapify(vetor, 0, i, &numComp);
    }
    return numComp;
}

void maxHeapifySR(int vetor[], size_t i, size_t tam, uint64_t *numComp){
    size_t l, r, maior;
    
    while (1){
        l = indiceFilhoEsquerdo(i);
        r = indiceFilhoDireito(i);
        maior = i;
        
        (*numComp)++;
        if (l <= tam-1 && vetor[l] > vetor[i])
            maior = l;

        (*numComp)++;
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

void contruirMaxHeapSR(int vetor[], size_t tam, uint64_t *numComp){
    for (ssize_t i = (ssize_t)(tam >> 1)-1; i >= 0; i--)
        maxHeapifySR(vetor, i, tam, numComp);
}

/* Ordenação iterativa de um vetor a partir do tam */
uint64_t heapSortSR(int vetor[], size_t tam) {
    uint64_t numComp=0;

    contruirMaxHeapSR(vetor, tam, &numComp);
    
    for (size_t i = tam-1; i > 0; i--){
        trocar(vetor, 0, i);
        maxHeapifySR(vetor, 0, i, &numComp);
    }
    return numComp;
}