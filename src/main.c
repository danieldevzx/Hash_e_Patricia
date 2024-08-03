#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/patricia_TAD.h"
#include "../include/arquivos.h"
#include "../include/lista_TAD.h"


int main() {
    tArquivo arquivo;

    // Abrir o arquivo de entrada
    fAbreArquivo("arq/entrada.txt", &arquivo);

    // Ler a quantidade de arquivos
    int qtd = fQtdDeArquivos(&arquivo);

    printf("Quantidade de arquivos: %d\n", qtd);

    // Criar o vetor de nomes de arquivos
    char **vetorDeArquivos = fVetorDeArquivos(&arquivo, qtd);
    if (vetorDeArquivos == NULL) {
        printf("Erro ao ler os nomes dos arquivos\n");
        fFechaArquivo(&arquivo);
        return 1;
    }

    // Fechar o arquivo de entrada
    fFechaArquivo(&arquivo);
    // Criar o vetor de caminhos completos
    char **arquivos = fCaminhoArquivos(vetorDeArquivos, qtd);

    // Criar a lista de palavras
    NodeL *listaDePalavras = fListaDePalavras(arquivos, qtd);
    if (listaDePalavras == NULL) {
        printf("Erro ao criar a lista de palavras\n");
        // Liberar memória
        for (int i = 0; i < qtd; i++) {
            free(arquivos[i]);
        }
        for (int i = 0; i < qtd; i++) {
            free(vetorDeArquivos[i]);
        }
        free(vetorDeArquivos);
        return 1;
    }

    // Imprimir a lista de palavras
    printf("Lista de palavras:\n");
    NodeL *current = listaDePalavras;
    int op = 0;
    while (current != NULL) {
        printf("Palavra %d:%s\n", op+1, current->data);
        current = current->next;
        op += 1;
    }

    // Liberar a lista de palavras
    fLiberaMemoria(listaDePalavras);

    // Liberar a memória do vetor de arquivos
    for (int i = 0; i < qtd; i++) {
        free(arquivos[i]);
    }
    // Liberar a memória de vetorDeArquivos
    for (int i = 0; i < qtd; i++) {
        free(vetorDeArquivos[i]);
    }
    free(vetorDeArquivos);

    printf("Vamo que vai dar bom");
    char test[] = "abacaxi"; // Palavra teste pra conversão em binário
    int len = sizeof(test)-1; //Tamanho da palavra
    char word[len*5]; // Vetor para resultado da conversão
    printf("\nTam: %i", len);
    fConvertToBin(test, word, sizeof(test)-1);
    fPrintKey(word);

    char test2[] = "abacaxis";
    len = sizeof(test2)-1;
    char word2[len*5];
    printf("\nTam: %i", len);
    fConvertToBin(test2, word2, len);
    fPrintKey(word2);

    return 0;
}
