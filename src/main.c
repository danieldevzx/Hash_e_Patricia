#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/arquivos.h"
#include "../include/lista_TAD.h"
#include "../include/hash_TAD.h"
#include "../include/patricia_TAD.h"
#include "../include/util.h"

// Função para liberar recursos e memória
void liberarRecursos(char **vetorDeArquivos, char **arquivos, tNodeP *listaDePalavras, 
                     tPalavra *v, int qtd, int tam, HashTable *hashTable, tNodePT *patricia) {
    if (hashTable) fLiberaHash(hashTable);
    if (listaDePalavras) fLiberaMemoria(listaDePalavras);
    if (patricia) fLiberaPatricia(patricia);

    for (int i = 0; i < tam; i++) {
        free(v[i].nome);
        fLiberaLista(v[i].node);
    }

    for (int i = 0; i < qtd; i++) {
        free(arquivos[i]);
        free(vetorDeArquivos[i]);
    }
    free(arquivos);
    free(vetorDeArquivos);
}

// Função para buscar uma palavra nas estruturas
void buscarPalavra(HashTable *hashTable, tNodePT *patricia, int qtd) {
    char palavraBuscada[50];

    if (fgets(palavraBuscada, sizeof(palavraBuscada), stdin) != NULL) {
        size_t len = strlen(palavraBuscada);
        if (len > 0 && palavraBuscada[len - 1] == '\n') {
            palavraBuscada[len - 1] = '\0';
        }
    }

    // Pesquisa na tabela hash
    printf("\n--- Resultado da Pesquisa na Tabela Hash ---\n");
    tPalavra *resultadoHash = fPesquisaHash(hashTable, palavraBuscada);
    if (resultadoHash != NULL) {
        fPrintPalavra(*resultadoHash);
        tID aux = fMaiorID(resultadoHash, qtd);
        printf("\t|MAIS RELEVANTE:<%d, %d>|\n", aux.qtd, aux.arq);
        fExibeDadosDoArquivo(aux);
    } else {
        printf("Palavra '%s' não encontrada na tabela hash\n", palavraBuscada);
    }

    // Pesquisa na árvore Patricia
    printf("\n--- Resultado da Pesquisa na Árvore Patricia ---\n");
    tNodePT *resultadoPatricia = fPesquisaPatricia(patricia, palavraBuscada);
    if (resultadoPatricia != NULL) {
        fPrintPalavra(resultadoPatricia->node.item);
        tID aux = fMaiorID(&resultadoPatricia->node.item, qtd);
        printf("\t| MAIS RELEVANTE: <%d, %d> |\n", aux.qtd, aux.arq);
        fExibeDadosDoArquivo(aux);
    } else {
        printf("Palavra '%s' não encontrada na árvore Patricia.\n", palavraBuscada);
    }
}

int main() {
    tArquivo aEntrada;
    char entrada[20];
    char caminho[50];

    // Leitura do nome do arquivo de entrada
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%19s", entrada);
    sprintf(caminho, "arq/%s", entrada);
    
    if (fAbreArquivo(caminho, &aEntrada) == 0) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }
    limpa();

    // Ler a quantidade de arquivos
    int qtd = fQtdDeArquivos(&aEntrada);

    // Criar o vetor de nomes de arquivos
    char **vetorDeArquivos = fVetorDeArquivos(&aEntrada, qtd);
    if (vetorDeArquivos == NULL) {
        fprintf(stderr, "Erro ao ler os nomes dos arquivos.\n");
        fFechaArquivo(&aEntrada);
        return 1;
    }

    // Fechar o arquivo de entrada
    fFechaArquivo(&aEntrada);

    // Criar o vetor de caminhos completos
    char **arquivos = fCaminhoArquivos(vetorDeArquivos, qtd);
    if (arquivos == NULL) {
        fprintf(stderr, "Erro ao criar o vetor de caminhos completos.\n");
        for (int i = 0; i < qtd; i++) {
            free(vetorDeArquivos[i]);
        }
        free(vetorDeArquivos);
        return 1;
    }

    // Criar a lista de palavras
    tNodeP *listaDePalavras = fListaDePalavras(arquivos, qtd);
    if (listaDePalavras == NULL) {
        fprintf(stderr, "Erro ao criar a lista de palavras.\n");
        liberarRecursos(vetorDeArquivos, arquivos, NULL, NULL, qtd, 0, NULL, NULL);
        return 1;
    }
    fOrdenaLista(listaDePalavras);
    int tam = fTamLista(listaDePalavras);

    // Criar o vetor de palavras
    tPalavra v[tam];
    fProcessaPalavras(listaDePalavras, arquivos, qtd, v);

    // Criar a tabela hash
    HashTable *hashTable = fCriaTabelaHash(tam);
    if (hashTable == NULL) {
        fprintf(stderr, "Erro ao criar a tabela hash.\n");
        liberarRecursos(vetorDeArquivos, arquivos, listaDePalavras, v, qtd, tam, NULL, NULL);
        return 1;
    }

    // Criar a árvore Patricia
    tNodePT *patricia = NULL;

    // Inserir as palavras na tabela hash e na árvore Patricia
    for (int i = 0; i < tam; i++) {
        fInsereHash(hashTable, v[i]);
        patricia = fPatriciaInsere(&patricia, v[i]);
    }

    pausa();
    limpa();

    int opcao;
    do {
        limpa();
        printf("\n=== Menu ===\n");
        printf("1. Listar arquivos\n");
        printf("2. Listar Ingredientes\n");
        printf("3. Mostrar tabela hash\n");
        printf("4. Mostrar árvore Patricia\n");
        printf("5. Buscar por palavra (Hash e Patricia)\n");
        printf("0. Sair\n");
        printf("Digite a opção: ");
        scanf("%d", &opcao);
        pausa();
        limpa();

        switch (opcao) {
        case 1:
            printf("Quantidade de arquivos: %d\n", qtd);
            for (int i = 0; i < qtd; i++) {
                printf("\t%s\n", vetorDeArquivos[i]);
            }
            pausa();
            limpa();
            break;

        case 2:
            fPrintDados(v, tam);
            pausa();
            limpa();
            break;

        case 3:
            fPrintHash(hashTable);
            pausa();
            limpa();
            break;

        case 4:
            fPrintPatricia(patricia);
            pausa();
            limpa();
            break;

        case 5:
            printf("Digite a palavra:");
            buscarPalavra(hashTable, patricia, qtd);
            pausa();
            limpa();
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida, tente novamente.\n");
            pausa();
            break;
        }
    } while (opcao != 0);
    printf("Número de comparações de inserção na tabela hash: %u\n", fGetCompIHash());
    printf("Número de comparações de pesquisa na tabela hash: %u\n", fGetCompPHash());
    printf("Número de comparações de inserção na árvore Patricia: %u\n", fGetCompIPatricia());
    printf("Número de comparações de pesquisa na árvore Patricia: %u\n", fGetCompPPatricia());

    // Liberar a memória
    liberarRecursos(vetorDeArquivos, arquivos, listaDePalavras, v, qtd, tam, hashTable, patricia);

    return 0;
}
