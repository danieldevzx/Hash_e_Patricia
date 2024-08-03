/*
    Biblioteca para gerenciamento de arquivos de receitas:
    - Abrir e fechar arquivos
    - Contar a quantidade de receitas
    - Obter a lista de receitas
    - Armazenar ingredientes em um lista sem repetição 
    - Contar a frequência de ingredientes nas receitas
    - Exibir a receita com maior relevância

    Definições e declarações de funções para manipulação de arquivos e dados de receitas.
*/

#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>
#include "../include/lista_TAD.h"


typedef struct {
    FILE *arquivo;
} tArquivo;


int abreArquivo(char *nome, tArquivo *arquivo);
int fechaArquivo(char *nome, tArquivo *arquivo);

// Abre um arquivo e retorna 1 se a abertura foi bem-sucedida, e 0 caso contrário.
int fAbreArquivo(char *nome, tArquivo *arquivo);

// Fecha o arquivo.
void fFechaArquivo(tArquivo *arquivo);

// Retorna a quantidade de arquivos (receitas) ou -1 se a contagem falhar.
int fQtdDeArquivos(tArquivo *arquivo);

// Retorna um vetor de strings contendo os nomes dos arquivos (receitas).
char **fVetorDeArquivos(tArquivo *arquivos, int n);

//Apos decobrirmos qual é são os nomes essa função retorna o caminho correto até o arquivos (receitas).
char **fCaminhoArquivos(char **arquivos, int qtd);

//Função que cria uma lista para as palavras 
Node *fListaDePalavras(char **vetorDeArquivos, int qtd);

#endif
