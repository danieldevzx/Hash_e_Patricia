#ifndef HASH_TAD_H
#define HASH_TAD_H

#include "palavras_TAD.h"

// Definição da estrutura tNodeH para os nós da tabela hash
typedef struct tNodeH {
    tPalavra palavra;      // Estrutura de dados que representa a palavra
    struct tNodeH *next;   // Ponteiro para o próximo nó na lista encadeada
} tNodeH;

// Definição da estrutura HashTable
typedef struct {
    tNodeH **table;        // Ponteiro para um array de ponteiros para tNodeH
    unsigned int size;     // Tamanho da tabela hash
} HashTable;

/**
 * @brief Função de hash usando o algoritmo djb2.
 * 
 * @param str String para gerar o hash.
 * @param size Tamanho da tabela hash (número de buckets).
 * @return unsigned int Índice da tabela hash onde a string deve ser armazenada.
 */
unsigned int fHash(char *str, unsigned int size);

/**
 * @brief Cria uma nova tabela hash com o tamanho especificado.
 * 
 * @param size Tamanho desejado para a tabela hash.
 * @return HashTable* Ponteiro para a tabela hash criada.
 */
HashTable *fCriaTabelaHash(unsigned int size);

/**
 * @brief Insere uma palavra na tabela hash.
 * 
 * @param hashTable Ponteiro para a tabela hash onde a palavra será inserida.
 * @param palavra Estrutura tPalavra que será inserida na tabela hash.
 */
void fInsereHash(HashTable *hashTable, tPalavra palavra);

/**
 * @brief Procura uma palavra na tabela hash.
 * 
 * @param hashTable Ponteiro para a tabela hash onde a palavra será procurada.
 * @param nome Nome da palavra a ser procurada.
 * @return tPalavra* Ponteiro para a estrutura tPalavra encontrada, ou NULL se não encontrada.
 */
tPalavra *fPesquisaHash(HashTable *hashTable, char *nome);

/**
 * @brief Libera a memória alocada para a tabela hash.
 * 
 * @param hashTable Ponteiro para a tabela hash a ser liberada.
 */
void fLiberaHash(HashTable *hashTable);

/**
 * @brief Imprime o conteúdo da tabela hash.
 * 
 * @param hashTable Ponteiro para a tabela hash a ser impressa.
 */
void fPrintHash(HashTable *hashTable);

/**
 * @brief Pega as comparações de inserção
 * 
 * @return Retorna um int das comparações de inserção
 */
unsigned int fGetCompIHash();

/**
 * @brief Pega as comparações de pesquisa
 * 
 * @return Retorna um int das comparações de pesquisa
 */
unsigned int fGetCompPHash();

#endif // HASH_TAD_H
