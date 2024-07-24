#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct pilha *pilha_cria (){
    struct pilha *pilha;

	pilha = (struct pilha*)malloc(sizeof(struct pilha));

	if (pilha == NULL)
		return NULL; 

	pilha->topo = NULL;
    pilha->tamanho = 0;

	return pilha;
}

void pilha_destroi (struct pilha **pilha){
    struct nodo *aux;

	while ((*pilha)->topo != NULL){
		aux = (*pilha)->topo;
		(*pilha)->topo = (*pilha)->topo->prox;
		free(aux);
	}

	free(*pilha);
	(*pilha) = NULL;
}

size_t empilhar(struct pilha *pilha, size_t inicio, size_t fim) {
    struct nodo *novo;

    novo = (struct nodo*)malloc(sizeof(struct nodo));
    if (novo == NULL)
        return 0;

    novo->inicio = inicio;
    novo->fim = fim;
    novo->prox = pilha->topo;
    pilha->topo = novo;
    (pilha->tamanho)++;

    return 1;
}

size_t desempilhar(struct pilha *pilha, size_t *inicio, size_t *fim) {
    struct nodo *aux;

    if (pilha->topo == NULL){
		return 0;
	}

	aux = pilha->topo;
    *inicio = aux->inicio;
    *fim = aux->fim;
    pilha->topo = aux->prox;
    free(aux);
    (pilha->tamanho)--;
    
    return 1;
}

size_t pilha_tamanho(struct pilha *pilha) {
    return pilha->tamanho;
}

size_t pilha_vazia(struct pilha *pilha) {
    return pilha->tamanho == 0;
}