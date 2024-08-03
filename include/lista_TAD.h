#ifndef LISTA_DE_PALAVRAS_TAD_H
#define LISTA_DE_PALAVRAS_TAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Estrutura de uma lista encadeada 
typedef struct NodeL {
    char *data;
    struct NodeL *next;
} NodeL;

// Função para criar um novo nó
NodeL* fCriaNode(const char *data);

// Função para verificar se o valor já está na lista
int fVerifica(NodeL *head, const char *data);

// Função para inserir um valor na lista, se não for duplicado
void fInsere(NodeL **head, const char *data);

// Função para liberar a memória da lista
void fLiberaMemoria(NodeL *head);

// Função para processar a segunda linha de um arquivo
int fAdicionaIgredientes(FILE *file, NodeL **list);

int fTamLista(NodeL *list);
#endif