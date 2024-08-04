#ifndef LISTA_DE_PALAVRAS_TAD_H
#define LISTA_DE_PALAVRAS_TAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Estrutura de uma lista encadeada 
typedef struct tNodeP {
    char *data;
    struct tNodeP *next;
} tNodeP;

// Função para criar um novo nó
tNodeP* fCriatNodeP(const char *data);

// Função para verificar se o valor já está na lista
int fVerifica(tNodeP *head, const char *data);

// Função para inserir um valor na lista, se não for duplicado
void fInsere(tNodeP **head, const char *data);

// Função para liberar a memória da lista
void fLiberaMemoria(tNodeP *head);

// Função para processar a segunda linha de um arquivo
int fAdicionaIgredientes(FILE *file, tNodeP **list);

int fTamLista(tNodeP *list);
#endif