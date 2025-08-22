# 📌 Projeto de Implementação e Análise de Algoritmos de Ordenação  

Este projeto implementa e compara diferentes algoritmos de ordenação em versões recursivas e iterativas. Além disso, mede o número de comparações realizadas e o tempo de execução para cada algoritmo, utilizando vetores em diferentes configurações.  

## 🚀 Algoritmos  

  - **MergeSort** (recursivo e iterativo)  
  - **QuickSort** (recursivo e iterativo)  
  - **HeapSort** (recursivo e iterativo)  

## 📂 Estrutura do Projeto  

- **`ordenacao.h`**  
  Declaração das funções de ordenação (recursivas e iterativas) e informações de identificação do autor (nome e GRR).  

- **`pilha_t.h`**  
  Implementação de uma pilha utilizada para simular recursividade nos algoritmos iterativos.  

- **`main.c`**  
  Arquivo principal do projeto, responsável por:  
  - Criar vetores em diferentes estados (crescente, decrescente, aleatório).  
  - Executar os algoritmos de ordenação.  
  - Medir tempo de execução e número de comparações.  
  - Exibir os resultados no console.  


## 🛠️ Funcionalidades  

- **Criação de vetores de teste**:  
  - Crescente → `0, 1, 2, ..., n-1`  
  - Decrescente → `n, n-1, ..., 1`  
  - Aleatório → `valores entre 0 e 100`  

- **Medição de desempenho**:  
  - Número de comparações realizadas por cada algoritmo.  
  - Tempo de execução medido com `clock()`.  

- **Execução automática**:  
  O programa executa todos os algoritmos sobre vetores do mesmo tamanho e imprime resultados organizados.  


