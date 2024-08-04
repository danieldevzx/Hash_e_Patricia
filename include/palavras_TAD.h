/*

    Um TAD responsavel por gerenciar as palavras que vão ser inseridas na tabela hash e na PATRICIA
    - Salva a palavra

*/

#ifndef PALAVRAS_TAD_H
#define PALAVRAS_TAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lista_TAD.h"
#include "../include/arquivos.h"

// Estrutura para armazenar a quantidade e o número do arquivo
typedef struct tID {
    int qtd; // Quantidade de aparições
    int arq; // Número do arquivo
} tID;

// Estrutura para o nó da lista encadeada que contém tID
typedef struct tNodeID {
    tID data;
    struct tNodeID *next;
} tNodeID;

// Estrutura para armazenar uma palavra e a lista encadeada de tID
typedef struct {
    char *nome; // Nome da palavra
    tNodeID *node; // Ponteiro para o início da lista encadeada de tID
} tPalavra;

// Funções declaradas
tID fCriaID(int qtd, int arq);
tNodeID *fNodeDeID(tID aux);
void fAdicionaNode(tNodeID **head, tID aux);
void fSalvaPalavra(tPalavra *palavra, char *nome, tNodeID *id);
void fLiberaLista(tNodeID *head);
void fProcessaPalavras(tNodeP *listaDePalavras, char **arquivos, int qtd, tPalavra *v);
void fPrintPalavra(tPalavra palavra);
void fPrintDados(tPalavra *v, int tam);

#endif // PALAVRAS_TAD_H
