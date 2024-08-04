#include "../include/hash_TAD.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Função de hash (djb2)
unsigned int fHash(char *str, unsigned int size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % size;
}

// Cria uma nova tabela hash
HashTable *fCriaTabelaHash(unsigned int tam) {
    unsigned int hashTableSize = (unsigned int)((double)tam / 3.0);
    if (hashTableSize < 1) {
        hashTableSize = 1;
    }
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    if (!hashTable) {
        perror("Erro ao alocar memória para a tabela hash");
        exit(EXIT_FAILURE);
    }
    hashTable->size = hashTableSize;
    hashTable->table = (tNodeH **)malloc(hashTableSize * sizeof(tNodeH *));
    if (!hashTable->table) {
        perror("Erro ao alocar memória para a tabela de nós da hash");
        free(hashTable);
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < hashTableSize; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

// Insere uma palavra na tabela hash
void fInsereHash(HashTable *hashTable, tPalavra palavra) {
    unsigned int index = fHash(palavra.nome, hashTable->size);
    tNodeH *newNode = (tNodeH *)malloc(sizeof(tNodeH));
    if (!newNode) {
        perror("Erro ao alocar memória para o nó da tabela hash");
        exit(EXIT_FAILURE);
    }
    newNode->palavra = palavra;
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

// Procura uma palavra na tabela hash
tPalavra *fPesquisaHash(HashTable *hashTable, char *nome) {
    unsigned int index = fHash(nome, hashTable->size);
    tNodeH *current = hashTable->table[index];
    while (current) {
        if (strcmp(current->palavra.nome, nome) == 0) {
            return &current->palavra;
        }
        current = current->next;
    }
    return NULL;
}

// Libera a memória da tabela hash
void fLiberaHash(HashTable *hashTable) {
    for (unsigned int i = 0; i < hashTable->size; i++) {
        tNodeH *current = hashTable->table[i];
        while (current) {
            tNodeH *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable->table);
    free(hashTable);
}
// Função para imprimir a tabela hash
void fPrintHash(HashTable *hashTable) {
    if (hashTable == NULL) {
        printf("Tabela hash não inicializada.\n");
        return;
    }

    printf("Tabela Hash:\n");
    for (unsigned int i = 0; i < hashTable->size; i++) {
        printf("Índice %u: ", i);
        tNodeH *node = hashTable->table[i];
        if (node == NULL) {
            printf("Lista vazia\n");
        } else {
            while (node != NULL) {
                printf(" -> %s: [", node->palavra.nome);
                while (node->palavra.node != NULL) {
                    printf("<%d,%d>", node->palavra.node->data.qtd, node->palavra.node->data.arq);
                    node->palavra.node = node->palavra.node->next;
                }
                node = node->next;
                printf("]");
            }
            printf("\n");
        }
    }
}