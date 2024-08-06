#ifndef PALAVRAS_TAD_H
#define PALAVRAS_TAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lista_TAD.h"
#include "arquivos.h"

// Estrutura para armazenar a quantidade e o número do arquivo
typedef struct tID {
    int qtd; // Quantidade de aparições
    int arq; // Número do arquivo
} tID;

// Estrutura para o nó da lista encadeada que contém tID
typedef struct tNodeID {
    tID data;               // Dados do nó (tID)
    struct tNodeID *next;   // Ponteiro para o próximo nó
} tNodeID;

// Estrutura para armazenar uma palavra e a lista encadeada de tID
typedef struct {
    char *nome;        // Nome da palavra
    tNodeID *node;    // Ponteiro para o início da lista encadeada de tID
} tPalavra;

/**
 * @brief Cria um tID com a quantidade e o número do arquivo fornecidos.
 * 
 * @param qtd Quantidade de aparições.
 * @param arq Número do arquivo.
 * @return tID Estrutura tID criada.
 */
tID fCriaID(int qtd, int arq);

/**
 * @brief Cria um novo nó para uma lista encadeada de tID.
 * 
 * @param aux Estrutura tID a ser armazenada no nó.
 * @return tNodeID* Ponteiro para o novo nó criado.
 */
tNodeID *fNodeDeID(tID aux);

/**
 * @brief Adiciona um nó contendo tID a uma lista encadeada.
 * 
 * @param head Ponteiro para o ponteiro do início da lista.
 * @param aux Estrutura tID a ser adicionada.
 */
void fAdicionaNode(tNodeID **head, tID aux);

/**
 * @brief Salva uma palavra e sua lista encadeada de tID.
 * 
 * @param palavra Ponteiro para a estrutura tPalavra a ser preenchida.
 * @param nome Nome da palavra.
 * @param id Ponteiro para o início da lista encadeada de tID.
 */
void fSalvaPalavra(tPalavra *palavra, char *nome, tNodeID *id);

/**
 * @brief Libera a memória alocada para uma lista encadeada de tNodeID.
 * 
 * @param head Ponteiro para o início da lista.
 */
void fLiberaLista(tNodeID *head);

/**
 * @brief Processa uma lista de palavras e armazena suas quantidades e números de arquivo em uma lista de tPalavra.
 * 
 * @param listaDePalavras Ponteiro para a lista de palavras.
 * @param arquivos Vetor de nomes de arquivos onde a contagem deve ser realizada.
 * @param qtd Número de arquivos.
 * @param v Vetor de estruturas tPalavra onde os resultados serão armazenados.
 */
void fProcessaPalavras(tNodeP *listaDePalavras, char **arquivos, int qtd, tPalavra *v);

/**
 * @brief Imprime os dados de uma palavra.
 * 
 * @param palavra Estrutura tPalavra a ser impressa.
 */
void fPrintPalavra(tPalavra palavra);

/**
 * @brief Imprime os dados de todas as palavras em um vetor.
 * 
 * @param v Vetor de estruturas tPalavra a ser impresso.
 * @param tam Tamanho do vetor.
 */
void fPrintDados(tPalavra *v, int tam);

/**
 * @brief Retorna o maior tID de uma estrutura tPalavra.
 * 
 * @param palavra Ponteiro para a estrutura tPalavra.
 * @param totalDocumentos Inteiro de quantidade de arquivos
 * @return tID Estrutura tID com o maior valor de quantidade.
 */
tID fMaiorID(tPalavra *palavra, int totalDocumentos);


#endif // PALAVRAS_TAD_H
