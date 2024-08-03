#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../include/patricia_TAD.h"

// Função para imprimir a chave em formato binário
void fPrintKey(char *key){
    int j = 0;
    printf("\n");
    while(key[j] == (0 + '0') || key[j] == (1 + '0')){ // Completa com 0 até ter 5 bits
        printf("%c ", key[j]);
        j++;
    }
}

// Função para converter uma letra para seu equivalente binário
void fConvertLetter(char c, char *bin, int i){
    int k = i * 5; // Posição inicial no binário
    int j;
    if(c == 32){ // Caso seja um espaço ele adiciona "00000" ao binário da palavra
        for(j = 5; j > 0; j--){ bin[k-j] = 0 + '0'; } // Completa com zeros
        return;
    }

    char *aux = malloc (sizeof(char) * 5); // Auxiliar para guardar o binário da letra (invertido)
    int n = c - 96; // Número que representa o caractere
    j = 0;
    while(n > 1){
        int i = n % 2;
        aux[j] = i + '0'; // Armazena os bits
        n = floor(n / 2); // Divide por 2 para obter o próximo bit
        j++;
    }
    aux[j] = 1 + '0'; // Armazena o bit mais significativo

    for(j++; j < 5; j++){ 
        aux[j] = 0 + '0'; // Completa com zeros
    }

    j = 4;
    for(int i = k-1; i >= k-5; i--){ 
        bin[k-j-1] = aux[j];
        j--;
    } // Inverte o binário auxiliar
    free(aux); // Libera a memória auxiliar
}

// Função para converter uma palavra inteira para binário
void fConvertToBin(char *key, char *bin, int size){
    for(int i = 0; i < size; i++){
        fConvertLetter(key[i], bin, i+1); // Converte cada letra da palavra para binário
    }
}

// Função para obter o enésimo bit de uma chave
typeBit fGetNBit(typeIndex index, char *key){
    if(index == 0) return 0; // Retorna 0 se o índice for 0
    return key[index-1]; // Retorna o enésimo bit da chave
}

// Função para verificar se um nó é externo
int IsOutside(pNode node){
    return (node->type == Outside); // Retorna 1 se o nó for externo, 0 caso contrário
}

// Função para gerar um nó externo
pNode fGenOutsideNode(char *key){
    pNode node = (pNode) malloc (sizeof(tNode)); // Aloca memória para o nó
    node->type = Outside; // Define o tipo do nó como externo
    node->Node.key = key; // Atribui a chave ao nó
    return node; // Retorna o nó
}

// Função para gerar um nó interno
pNode fGenInsideNode(typeIndex nodeIndex, pNode *lef, pNode *rig){
    pNode node = (pNode) malloc (sizeof(tNode)); // Aloca memória para o nó
    node->type = Inside; // Define o tipo do nó como interno
    node->Node.insideNode.index = nodeIndex; // Define o índice do nó interno
    node->Node.insideNode.lef = *lef; // Define o filho esquerdo
    node->Node.insideNode.rig = *rig; // Define o filho direito
    return node; // Retorna o nó
}

// Função para inserir um nó na árvore Patricia
pNode fInsertIn(char *key, pNode *root, int index){
    pNode node;
    if(IsOutside(*root) || index < (*root)->Node.insideNode.index){ // Verifica se o nó é externo ou o índice é menor
        node = fGenOutsideNode(key); // Gera um nó externo
        if (fGetNBit(index, key) == '1'){ // Verifica o bit da chave no índice
            return fGenInsideNode(index, root, &node); // Gera um nó interno com o novo nó à direita
        }
        else {
            return fGenInsideNode(index, &node, root); // Gera um nó interno com o novo nó à esquerda
        }
    }
    else {
        if(fGetNBit((*root)->Node.insideNode.index, key) == 1){ // Verifica o bit da chave no índice do nó interno
            (*root)->Node.insideNode.rig = fInsertIn(key, &(*root)->Node.insideNode.rig, index); // Insere à direita
        }
        else{
            (*root)->Node.insideNode.lef = fInsertIn(key, &(*root)->Node.insideNode.lef, index); // Insere à esquerda
        }
        return *root; // Retorna a raiz
    }
}

// Função para inserir uma palavra na árvore Patricia
pNode fInsertWord(char *key, pNode *root){
    pNode node; 
    int index;
    int len = sizeof(key) - 1; // Obtém o comprimento da chave
    if(*root == NULL) {return (fGenOutsideNode(key));} // Se a raiz for nula, gera um nó externo
    else {
        node = *root; 
        while(!IsOutside(node)){ // Enquanto o nó não for externo
            if(fGetNBit(node->Node.insideNode.index, key) == 1) node = node->Node.insideNode.rig; // Vai para a direita se o bit for 1
            else node = node->Node.insideNode.lef; // Vai para a esquerda se o bit for 0
        }
        index = 1;
        while((index <= len) && (fGetNBit(index, key) == fGetNBit(index, node->Node.key))){ // Encontra o primeiro bit diferente
            index++;
        }
        if(index > len) {
            printf("Erro: chave já inserida\n");
            return *root; // Chave já inserida
        }
        else {
            return fInsertIn(key, root, index); // Insere a chave na árvore
        }
    }
}

void fSearch(char *key, pNode node){ // Função para buscar uma chave na árvore Patricia
    while(!IsOutside(node)){ // Enquanto o nó não for externo
        if(fGetNBit(node->Node.insideNode.index, key) == 1) {
            node = node->Node.insideNode.rig; // Direita se o bit for 1
        } else {
            node = node->Node.insideNode.lef; // Esquerda se o bit for 0
        }
    }
    if(strcmp(node->Node.key, key) == 0) { // Compara a chave com a chave do nó externo
        printf("Chave encontrada\n");
    } else {
        printf("Chave não encontrada\n");
    }
}

//desta vez coom comentários, oiii lindooos.
