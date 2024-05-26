//
// Created by lucas on 24/05/2024.
//
// Ficheiro com as definições e construtores das estruturas utilizadas na realização do trabalho.
//
// Criamos um vertice para recriar a estrutura do grafo e apontamos para os proximos vertices possiveis.
// A regra de coneção é apenas para a direita do ponto e para baixo.
//
// Da mesma maneira utilizamos uma pilha para facilmente aceder a varios pontos do grafo
//

#ifndef PROJECT_2_EA_GRAFOS_H
#define PROJECT_2_EA_GRAFOS_H
#include <stdlib.h>

// Defenição de um vertice do grafo
typedef struct vertice *Vertice;

// Construtor da estrutura de um vertice
struct vertice{
    // Apontar para os dois caminhos possiveis
    struct pilha *direita; // Aresta da Direita
    struct pilha *baixo; // Aresta de Baixo

    // Variaveis logicas
    int valor;
};


// Defenição da pilha
typedef  struct pilha *Pilha;

// Construtor da estrutura da pilha
struct pilha{
    // Apontatar para a proxima instancia da pilha
    struct pilha *proximo;

    // Variaveis logicas
    int id; // Posição na pilha
    struct vertice *Vertice; // Armazenar um vertice do grafo nesta posição da pilha
};

#endif //PROJECT_2_EA_GRAFOS_H
