#include "../include/arquivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Para isspace

// Função para abrir arquivos
int fAbreArquivo(char *nomeArquivo, tArquivo *arquivo) {
    arquivo->arquivo = fopen(nomeArquivo, "r");
    if (arquivo->arquivo == NULL) {
        perror("fopen");
        return 0;
    }
    return 1;
}

// Função para fechar arquivos
void fFechaArquivo(tArquivo *arquivo) {
    if (arquivo->arquivo != NULL) {
        fclose(arquivo->arquivo);
    }
}

// Função que verifica a quantidade de arquivos
int fQtdDeArquivos(tArquivo *arquivo) {
    int n;
    char linha[10];

    if (fgets(linha, sizeof(linha), arquivo->arquivo) == NULL) {
        printf("Erro ao ler a quantidade de arquivos\n");
        return -1;
    }

    if (sscanf(linha, "%d", &n) != 1) {
        printf("Erro ao ler a quantidade de arquivos\n");
        return -1;
    }

    return n;
}

// Função que cria um vetor de arquivos
char **fVetorDeArquivos(tArquivo *arquivo, int n) {
    char **vetorDeArquivos = (char **)calloc(n, sizeof(char *));
    if (vetorDeArquivos == NULL) {
        printf("Erro ao alocar memória para o vetor de arquivos\n");
        return NULL;
    }

    char linha[200];
    for (int i = 0; i < n; i++) {
        if (fgets(linha, sizeof(linha), arquivo->arquivo) == NULL) {
            printf("Erro ao ler o nome do arquivo %d\n", i + 1);
            for (int j = 0; j < i; j++) {
                free(vetorDeArquivos[j]);
            }
            free(vetorDeArquivos);
            return NULL;
        }

        linha[strcspn(linha, "\n")] = '\0';

        vetorDeArquivos[i] = strdup(linha);
        if (vetorDeArquivos[i] == NULL) {
            printf("Erro ao alocar memória para o nome do arquivo %d\n", i + 1);
            for (int j = 0; j < i; j++) {
                free(vetorDeArquivos[j]);
            }
            free(vetorDeArquivos);
            return NULL;
        }
    }

    return vetorDeArquivos;
}

// Função que remove espaços em branco de uma string
void fQuebra(char *str) {
    char *end;

    // Remove espaços em branco no início
    while (isspace((unsigned char)*str)) str++;

    // Todos os caracteres são espaços em branco?
    if (*str == 0) return;

    // Remove espaços em branco no final
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Adiciona o terminador nulo
    *(end + 1) = '\0';
}

// Função que gera o caminho completo dos arquivos
char **fCaminhoArquivos(char **arquivos, int qtd) {
    char **caminho = (char **)calloc(qtd, sizeof(char *));
    if (caminho == NULL) {
        perror("calloc");
        for (int i = 0; i < qtd; i++) {
            free(arquivos[i]);
        }
        free(arquivos);
        return NULL;
    }

    for (int i = 0; i < qtd; i++) {
        fQuebra(arquivos[i]); // Remove espaços em branco
        caminho[i] = malloc(1024);
        if (caminho[i] == NULL) {
            perror("malloc");
            for (int j = 0; j < i; j++) {
                free(caminho[j]);
            }
            for (int k = 0; k < qtd; k++) {
                free(arquivos[k]);
            }
            free(arquivos);
            return NULL;
        }
        snprintf(caminho[i], 1024, "arq/ArquivosEntrada/%s", arquivos[i]);
    }

    return caminho;
}

// Função para processar todos os arquivos e criar a lista de palavras
Node *fListaDePalavras(char **vetorDeArquivos, int qtd) {
    Node *list = NULL;
    for (int i = 0; i < qtd; i++) {
        tArquivo arquivo;
        if (!fAbreArquivo(vetorDeArquivos[i], &arquivo)) {
            printf("Erro ao abrir o arquivo %s\n", vetorDeArquivos[i]);
            continue;
        }
        if (!fAdicionaIgredientes(arquivo.arquivo, &list)) {
            printf("Erro ao processar o arquivo %s\n", vetorDeArquivos[i]);
        }
        fFechaArquivo(&arquivo);
    }
    return list;
}
