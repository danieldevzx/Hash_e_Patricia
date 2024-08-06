#ifndef PATRICIA_TAD_H
#define PATRICIA_TAD_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "palavras_TAD.h"

// Enum para tipo de nó
typedef enum {
    INTERNO,  ///< Nó interno da árvore Patricia
    EXTERNO   ///< Nó externo da árvore Patricia
} TipoNode;

// Estrutura para o nó da árvore Patricia
typedef struct tNodePT pNodePT;
typedef struct tNodePT {
    TipoNode tipo;  ///< Tipo do nó (INTERNO ou EXTERNO)
    union {
        struct {
            char letra;       ///< Letra que divide os nós internos
            int index;        ///< Índice da letra na palavra
            pNodePT *esq;     ///< Ponteiro para a subárvore esquerda
            pNodePT *dir;     ///< Ponteiro para a subárvore direita
        } nodeInterno;
        tPalavra item;  ///< Palavra armazenada no nó externo
    } node;
} tNodePT;

/**
 * @brief Verifica se o nó é do tipo EXTERNO.
 * 
 * @param node Ponteiro para o nó da árvore Patricia.
 * @return int Retorna 1 se o nó é EXTERNO, 0 caso contrário.
 */
int fPatriciaEhExterno(tNodePT *node);

/**
 * @brief Determina a direção de inserção com base no índice e no caractere pivô.
 * 
 * @param index Índice atual da letra na palavra.
 * @param item Estrutura tPalavra que está sendo inserida.
 * @param pivo Letra pivô para comparação.
 * @return int Retorna 1 se a letra da palavra é maior que o pivo, 0 caso contrário.
 */
int fPatriciaDirecao(int index, tPalavra item, char pivo);

/**
 * @brief Cria um nó interno com filhos, índice e letra.
 * 
 * @param esq Ponteiro para a subárvore esquerda.
 * @param dir Ponteiro para a subárvore direita.
 * @param index Índice da letra na palavra.
 * @param letra Letra que divide os nós.
 * @return tNodePT* Ponteiro para o novo nó interno criado.
 */
tNodePT *fPatriciaCriaNodeInterno(tNodePT *esq, tNodePT *dir, int index, char letra);

/**
 * @brief Cria um nó externo com uma palavra.
 * 
 * @param item Estrutura tPalavra a ser armazenada no nó externo.
 * @return tNodePT* Ponteiro para o novo nó externo criado.
 */
tNodePT *fPatriciaCriaNodeExterno(tPalavra item);

/**
 * @brief Insere um item entre dois nós existentes.
 * 
 * @param nodeAtual Ponteiro para o nó atual na árvore.
 * @param item Estrutura tPalavra a ser inserida.
 * @param index Índice da letra na palavra.
 * @param letraNoInterno Letra no nó interno para comparação.
 * @return tNodePT* Ponteiro para o novo nó criado, possivelmente o nó interno.
 */
tNodePT *fPatriciaInsereEntre(tNodePT *nodeAtual, tPalavra item, int index, char letraNoInterno);

/**
 * @brief Insere um item na árvore Patricia.
 * 
 * @param raiz Ponteiro para a raiz da árvore Patricia.
 * @param item Estrutura tPalavra a ser inserida.
 * @return tNodePT* Ponteiro para a raiz atualizada da árvore Patricia.
 */
tNodePT *fPatriciaInsere(tNodePT **raiz, tPalavra item);

/**
 * @brief Função auxiliar que imprime a árvore Patricia.
 * 
 * @param node Ponteiro para o nó atual.
 * @param level Nível de profundidade na árvore para formatação.
 */
void fPrintPatriciaAux(tNodePT *node, int level);

/**
 * @brief Imprime a árvore Patricia.
 * 
 * @param raiz Ponteiro para a raiz da árvore Patricia.
 */
void fPrintPatricia(tNodePT *raiz);

/**
 * @brief Libera a memória alocada para a árvore Patricia.
 * 
 * @param raiz Ponteiro para a raiz da árvore Patricia.
 */
void fLiberaPatricia(tNodePT *raiz);

/**
 * @brief Pesquisa uma palavra na árvore Patricia.
 * 
 * @param raiz Ponteiro para a raiz da árvore Patricia.
 * @param nome Nome da palavra a ser pesquisada.
 * @return tNodePT* Ponteiro para o nó onde a palavra foi encontrada, ou NULL se não encontrada.
 */
tNodePT *fPesquisaPatricia(tNodePT *raiz, char *nome);

/**
 * @brief Pega as comparações de inserção
 * 
 * @return Retorna um int das comparações de inserção
 */
unsigned int fGetCompIPatricia();

/**
 * @brief Pega as comparações de pesquisa
 * 
 * @return Retorna um int das comparações de pesquisa
 */
unsigned int fGetCompPPatricia();


#endif // PATRICIA_TAD_H
