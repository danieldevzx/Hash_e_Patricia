#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/arquivos.h"
#include "../include/lista_TAD.h"
#include "../include/hash_TAD.h"
#include "../include/patricia_TAD.h"
#include "../include/util.h"


// Função para liberar recursos e memória
void liberarRecursos(char **vetorDeArquivos, char **arquivos, tNodeP *listaDePalavras, 
                     tPalavra *v, int qtd, int tam, HashTable *hashTable) {
    fLiberaHash(hashTable);
    fLiberaMemoria(listaDePalavras);
    
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

// Função para processar a busca por palavra
void buscarPalavra(HashTable *hashTable) {
    char palavraBuscada[50];

    printf("Digite a palavra para buscar: ");
    if (fgets(palavraBuscada, sizeof(palavraBuscada), stdin) != NULL) {
        size_t len = strlen(palavraBuscada);
        if (len > 0 && palavraBuscada[len - 1] == '\n') {
            palavraBuscada[len - 1] = '\0';
        }
    }

    // Pesquisa na tabela hash
    tPalavra *resultadoHash = fPesquisaHash(hashTable, palavraBuscada);
    if (resultadoHash != NULL) {
        printf("Palavra encontrada na tabela hash:\n");
        fPrintPalavra(*resultadoHash);
        tID aux = fMaiorID(resultadoHash);
        printf("\t|MAIS RELEVANTE:<%d, %d>|\n", aux.qtd, aux.arq);
        fExibeDadosDoArquivo(aux);
    } else {
        printf("Palavra '%s' não encontrada na tabela hash\n", palavraBuscada);
    }
}

void menu() {
    tArquivo aEntrada;
    char entrada[20];
    char caminho[50];
    
    // Leitura do nome do arquivo de entrada
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", entrada);
    sprintf(caminho, "arq/%s", entrada);

    if (!fAbreArquivo(caminho, &aEntrada) != 0) {
        fprintf(stderr, "Erro ao abrir o arquivo de entrada\n");
        return;
    }
    limpa();

    // Ler a quantidade de arquivos
    int qtd = fQtdDeArquivos(&aEntrada);
    printf("Quantidade de arquivos: %d\n", qtd);
    pause();
    limpa();

    // Criar o vetor de nomes de arquivos
    char **vetorDeArquivos = fVetorDeArquivos(&aEntrada, qtd);
    if (vetorDeArquivos == NULL) {
        fprintf(stderr, "Erro ao ler os nomes dos arquivos\n");
        fFechaArquivo(&aEntrada);
        return;
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
        return;
    }

    // Criar a lista de palavras
    tNodeP *listaDePalavras = fListaDePalavras(arquivos, qtd);
    if (listaDePalavras == NULL) {
        fprintf(stderr, "Erro ao criar a lista de palavras\n");
        liberarRecursos(vetorDeArquivos, arquivos, NULL, NULL, qtd, 0, NULL);
        return;
    }

    int tam = fTamLista(listaDePalavras);

    // Criar o vetor de palavras
    tPalavra v[tam];
    fProcessaPalavras(listaDePalavras, arquivos, qtd, v);

    // Criar a tabela hash
    HashTable *hashTable = fCriaTabelaHash(tam);
    if (hashTable == NULL) {
        fprintf(stderr, "Erro ao criar a tabela hash\n");
        liberarRecursos(vetorDeArquivos, arquivos, listaDePalavras, v, qtd, tam, NULL);
        return;
    }

    // Inserir as palavras na tabela hash
    for (int i = 0; i < tam; i++) {
        fInsereHash(hashTable, v[i]);
    }

    int opcao;
    do {
        limpa();
        printf("\n=== Menu ===\n");
        printf("1. Listar arquivos\n");
        printf("2. Listar Ingredientes\n");
        printf("3. Mostrar tabela hash\n");
        printf("4. Mostrar Patricia\n");
        printf("5. Buscar por palavra (Hash e Patricia)\n");
        printf("-1. Sair\n");
        printf("Digite a opcao: ");
        scanf("%d", &opcao);
        pause();
        limpa();

        switch (opcao) {
        case 1:
            for (int i = 0; i < qtd; i++) {
                printf("%s\n", vetorDeArquivos[i]);
            }
            pause();
            limpa();
            break;

        case 2:
            fPrintDados(v, tam);
            pause();
            limpa();
            break;

        case 3:
            fPrintHash(hashTable);
            pause();
            limpa();
            break;

        case 4:
            printf("Não feito ainda\n");
            pause();
            limpa();
            break;

        case 5:
            buscarPalavra(hashTable);
            pause();
            limpa();
            break;

        case -1:
            break;

        default:
            printf("Opção inválida, tente novamente.\n");
            break;
        }
    } while (opcao != -1);

    // Liberar a memória
    liberarRecursos(vetorDeArquivos, arquivos, listaDePalavras, v, qtd, tam, hashTable);
}


int main() {


    menu();


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
