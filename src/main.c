#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/patricia_TAD.h"
#include "../include/arquivos.h"
#include "../include/lista_TAD.h"
#include "../include/hash_TAD.h"


int main() {
    tArquivo aEntrada;
    char entrada[20];
    char caminho[50]; 

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", entrada);

    sprintf(caminho, "arq/%s", entrada);

    if (!fAbreArquivo(caminho, &aEntrada) != 0) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada\n");
        return 1;
    }

    // Ler a quantidade de arquivos
    int qtd = fQtdDeArquivos(&aEntrada);
    printf("Quantidade de arquivos: %d\n", qtd);

    // Criar o vetor de nomes de arquivos
    char **vetorDeArquivos = fVetorDeArquivos(&aEntrada, qtd);
    if (vetorDeArquivos == NULL) {
        fprintf(stderr, "Erro ao ler os nomes dos arquivos\n");
        fFechaArquivo(&aEntrada);
        return 1;
    }

    // Fechar o arquivo de entrada
    fFechaArquivo(&aEntrada);

    // Criar o vetor de caminhos completos
    char **arquivos = fCaminhoArquivos(vetorDeArquivos, qtd);
    if (arquivos == NULL) {
        fprintf(stderr, "Erro ao criar o vetor de caminhos completos\n");
        for (int i = 0; i < qtd; i++) {
            free(vetorDeArquivos[i]);
        }
        free(vetorDeArquivos);
        return 1;
    }

    // Criar a lista de palavras
    tNodeP *listaDePalavras = fListaDePalavras(arquivos, qtd);
    if (listaDePalavras == NULL) {
        fprintf(stderr, "Erro ao criar a lista de palavras\n");
        for (int i = 0; i < qtd; i++) {
            free(arquivos[i]);
        }
        free(arquivos);
        for (int i = 0; i < qtd; i++) {
            free(vetorDeArquivos[i]);
        }
        free(vetorDeArquivos);
        return 1;
    }

    int tam = fTamLista(listaDePalavras);

    // Criar o vetor de palavras
    tPalavra v[tam];
    fProcessaPalavras(listaDePalavras, arquivos, qtd, v);
   
    // Criar a tabela hash
    HashTable *hashTable = fCriaTabelaHash(tam);

    // Inserir as palavras na tabela hash
    for (int i = 0; i < tam; i++) {
        fInsereHash(hashTable, v[i]);
    }
    char palavraBuscada[300];
    printf("Digite a palavra para buscar: ");
    scanf("%s", palavraBuscada);
    tPalavra *resultado = fPesquisaHash(hashTable, palavraBuscada);
    if(resultado != NULL){
        fPrintPalavra(*resultado);
    }
    // Liberar a memória
    fLiberaHash(hashTable);
    fLiberaMemoria(listaDePalavras);
    for (int i = 0; i < tam; i++) {
        free(v[i].nome);
        fLiberaLista(v[i].node);
    }
    for (int i = 0; i < qtd; i++) {
        free(arquivos[i]);
    }
    free(arquivos);
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
