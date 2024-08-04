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
#include "lista_TAD.h"
#include "palavras_TAD.h"

// Declaração antecipada de tID
typedef struct tID tID;

typedef struct {
    FILE *arquivo;
} tArquivo;

int fAbreArquivo(char *nome, tArquivo *arquivo);
void fFechaArquivo(tArquivo *arquivo);
int fQtdDeArquivos(tArquivo *arquivo);
char **fVetorDeArquivos(tArquivo *arquivos, int n);
char **fCaminhoArquivos(char **arquivos, int qtd);
tNodeP *fListaDePalavras(char **vetorDeArquivos, int qtd);
int fContaIngredientes(char *nomeArquivo, char *ingredientes);
void fExibeDadosDoArquivo(tID id);

#endif // ARQUIVOS_H
