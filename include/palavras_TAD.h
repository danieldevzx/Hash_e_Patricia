/*

    Um TAD responsavel por gerenciar as palavras que vão ser inseridas na tabela hash e na PATRICIA
    - Salva a palavra

*/

#ifndef PALAVRAS_TAD_H
#define PALAVRAS_TAD_H

#include <stdio.h>

typedef struct{
    int qtd;
    int arq;
} tID;
typedef struct{
    char *name;
    tID vetor[];
} tPalavra;

void fSalvaPalavra(tPalavra *nome, tID *valor);
#endif