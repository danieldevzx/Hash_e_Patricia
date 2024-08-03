#ifndef LISTA_DE_PALAVRAS_TAD_H
#define LISTA_DE_PALAVRAS_TAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Estrutura de uma lista encadeada 
typedef struct Node {
    char *data;
    struct Node *next;
} Node;

// Função para criar um novo nó
Node* fCriaNode(const char *data);

// Função para verificar se o valor já está na lista
int fVerifica(Node *head, const char *data);

// Função para inserir um valor na lista, se não for duplicado
void fInsere(Node **head, const char *data);

// Função para liberar a memória da lista
void fLiberaMemoria(Node *head);

// Função para processar a segunda linha de um arquivo
int fAdicionaIgredientes(FILE *file, Node **list);

int fTamLista(Node *list);
#endif