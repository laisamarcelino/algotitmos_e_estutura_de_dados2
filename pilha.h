#ifndef _pilha_t_H
#define _pilha_t_H

struct nodo {
    size_t chave;
    struct nodo *prox;
};

struct pilha {
    struct nodo *topo;
    size_t tamanho;
};

/* 
 * Cria e retorna uma nova pilha.
 * Retorna NULL em caso de erro de alocação.
*/
struct pilha *pilha_cria ();

/* Desaloca toda memoria da pilha e faz pilha receber NULL. */
void pilha_destroi (struct pilha **pilha);

/* 
 * Insere dado na pilha (politica LIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
size_t empilhar (struct pilha *pilha, size_t dado);

/* 
 * Remove o topo (politica LIFO) e retorna o elemento 
 * no parametro dado. A funcao retorna 1 em caso de 
 * sucesso e 0 no caso da pilha estar vazia.
*/
size_t desempilhar (struct pilha *pilha, size_t *dado);
 
/* 
 * Similar ao pop (desempilhar), mas retorna o elemento dado sem remove-lo. 
 * A funcao retorna 1 em caso de sucesso e 0 no caso 
 * da pilha estar vazia.
*/
size_t pilha_topo (struct pilha *pilha, size_t *dado); 

/* Retorna o numero de elementos da pilha, que pode ser 0. */
size_t pilha_tamanho (struct pilha *pilha);

/* Retorna 1 se pilha vazia, 0 em caso contrario. */ 
size_t pilha_vazia (struct pilha *pilha);

#endif
