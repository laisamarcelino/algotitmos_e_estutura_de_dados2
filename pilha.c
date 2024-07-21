#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct pilha *pilha_cria (){
    struct pilha *pilha;

	pilha = malloc(sizeof(struct pilha));

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

size_t empilhar (struct pilha *pilha, size_t dado){
    struct nodo *novo;

	novo = malloc(sizeof(struct nodo));

	if (novo == NULL)
		return 0;

	novo->chave = dado;
	novo->prox = pilha->topo;
	pilha->topo = novo;
	(pilha->tamanho)++;
	
	return 1;
}

size_t desempilhar (struct pilha *pilha, size_t *dado){
    struct nodo *aux;

	if (pilha_vazia(pilha))
		return 0;

	*dado = pilha->topo->chave;
	aux = pilha->topo;
	pilha->topo = pilha->topo->prox;
	(pilha->tamanho)--;
	free(aux);
	aux = NULL;

	return 1;
}

size_t pilha_topo (struct pilha *pilha, size_t *dado){

	if (pilha_vazia(pilha))
		return 0;

	*dado = pilha->topo->chave;

	return 1;
}

size_t pilha_tamanho (struct pilha *pilha){
    return pilha->tamanho;
}

size_t pilha_vazia (struct pilha *pilha){
    if (pilha->tamanho == 0)
		return 1;
	return 0;
}