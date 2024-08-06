#ifndef LISTA_DE_PALAVRAS_TAD_H
#define LISTA_DE_PALAVRAS_TAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó em uma lista encadeada de palavras
typedef struct tNodeP {
    char *data;              // Dados armazenados no nó (uma string)
    struct tNodeP *next;    // Ponteiro para o próximo nó na lista
} tNodeP;

/**
 * @brief Cria um novo nó com os dados fornecidos.
 * 
 * @param data String a ser armazenada no novo nó.
 * @return tNodeP* Ponteiro para o novo nó criado.
 */
tNodeP* fCriatNodeP(const char *data);

/**
 * @brief Verifica se um valor já está presente na lista.
 * 
 * @param head Ponteiro para o início da lista.
 * @param data Valor a ser verificado.
 * @return int 1 se o valor for encontrado, 0 caso contrário.
 */
int fVerifica(tNodeP *head, const char *data);

/**
 * @brief Insere um valor na lista se ele não for duplicado.
 * 
 * @param head Ponteiro para o ponteiro do início da lista.
 * @param data Valor a ser inserido.
 */
void fInsere(tNodeP **head, const char *data);

/**
 * @brief Libera a memória alocada para a lista.
 * 
 * @param head Ponteiro para o início da lista.
 */
void fLiberaMemoria(tNodeP *head);

/**
 * @brief Processa a segunda linha de um arquivo e adiciona os ingredientes em uma lista.
 * 
 * @param file Ponteiro para o arquivo a ser lido.
 * @param list Ponteiro para o ponteiro da lista onde os ingredientes serão adicionados.
 * @return int 1 se a operação for bem-sucedida, 0 em caso de erro.
 */
int fAdicionaIgredientes(FILE *file, tNodeP **list);

/**
 * @brief Conta o número de elementos na lista.
 * 
 * @param list Ponteiro para o início da lista.
 * @return int Número de elementos na lista.
 */
int fTamLista(tNodeP *list);

/**
 * @brief Ordena a lista de palavras
 * 
 * @param head recebe o endereço da lista a ser ordenada
 */
void fOrdenaLista(tNodeP *head);

#endif // LISTA_DE_PALAVRAS_TAD_H
