#ifndef HASH_TAD_H
#define HASH_TAD_H

#include "palavras_TAD.h"

// Definição da estrutura tNodeH
typedef struct tNodeH {
    tPalavra palavra;
    struct tNodeH *next;
} tNodeH;

// Definição da estrutura HashTable
typedef struct {
    tNodeH **table;   // Ponteiro para um array de ponteiros para tNodeH
    unsigned int size;  // Tamanho da tabela hash
} HashTable;

// Funções para criar, inserir, procurar e liberar a tabela hash
unsigned int fHash(char *str, unsigned int size);
HashTable *fCriaTabelaHash(unsigned int size);
void fInsereHash(HashTable *hashTable, tPalavra palavra);
tPalavra *fPesquisaHash(HashTable *hashTable, char *nome);
void fLiberaHash(HashTable *hashTable);
void fPrintHash(HashTable *hashTable);
#endif // HASH_TAD_H
