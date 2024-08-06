#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include "lista_TAD.h"
#include "palavras_TAD.h"

// Declaração antecipada de tID
typedef struct tID tID;

// Estrutura que representa um arquivo
typedef struct {
    FILE *arquivo;
} tArquivo;

/**
 * @brief Abre um arquivo para leitura.
 * 
 * @param nome Nome do arquivo a ser aberto.
 * @param arquivo Ponteiro para a estrutura que armazenará o arquivo aberto.
 * @return int Retorna 1 se o arquivo foi aberto com sucesso, 0 caso contrário.
 */
int fAbreArquivo(char *nome, tArquivo *arquivo);

/**
 * @brief Fecha um arquivo aberto.
 * 
 * @param arquivo Ponteiro para a estrutura que contém o arquivo a ser fechado.
 */
void fFechaArquivo(tArquivo *arquivo);

/**
 * @brief Lê a quantidade de arquivos listados no arquivo de entrada.
 * 
 * @param arquivo Ponteiro para a estrutura que contém o arquivo de entrada aberto.
 * @return int A quantidade de arquivos, ou -1 em caso de erro.
 */
int fQtdDeArquivos(tArquivo *arquivo);

/**
 * @brief Cria um vetor de nomes de arquivos a partir do arquivo de entrada.
 * 
 * @param arquivo Ponteiro para a estrutura que contém o arquivo de entrada aberto.
 * @param n Quantidade de arquivos listados no arquivo de entrada.
 * @return char** Vetor de nomes de arquivos, ou NULL em caso de erro.
 */
char **fVetorDeArquivos(tArquivo *arquivos, int n);

/**
 * @brief Gera os caminhos completos para os arquivos listados.
 * 
 * @param arquivos Vetor de nomes de arquivos.
 * @param qtd Quantidade de arquivos.
 * @return char** Vetor de caminhos completos para os arquivos, ou NULL em caso de erro.
 */
char **fCaminhoArquivos(char **arquivos, int qtd);

/**
 * @brief Processa os arquivos e cria uma lista de palavras (ingredientes).
 * 
 * @param vetorDeArquivos Vetor de caminhos completos para os arquivos.
 * @param qtd Quantidade de arquivos.
 * @return tNodeP* Ponteiro para a lista encadeada de palavras.
 */
tNodeP *fListaDePalavras(char **vetorDeArquivos, int qtd);

/**
 * @brief Conta a frequência de um ingrediente específico em um arquivo de receita.
 * 
 * @param nomeArquivo Nome do arquivo de receita.
 * @param ingredientes Ingrediente a ser contado.
 * @return int Frequência do ingrediente no arquivo de receita, ou -1 em caso de erro.
 */
int fContaIngredientes(char *nomeArquivo, char *ingredientes);

/**
 * @brief Exibe os dados de um arquivo de receita baseado em tID.
 * 
 * @param id Estrutura tID que contém a identificação do arquivo a ser exibido.
 */
void fExibeDadosDoArquivo(tID id);

#endif // ARQUIVOS_H
