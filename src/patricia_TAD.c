#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../include/patricia_TAD.h"

void fPrintKey(char *key){
    int j = 0;
    printf("\n");
    while(key[j] == (0 + '0') || key[j] == (1 + '0')){ //Completa com 0 até ter 5 bits
        printf("%c ", key[j]);
        j++;
    }
}

void fConvertLetter(char c, char *bin, int i){
    int k = i*5;
    int j;
    if(c == 32){ //Caso seja um espaço ele adiciona "00000" ao binario da palavra
        for(j = 5;j > 0; j--){bin[k-j] = 0 + '0';}
        return;
    }
    

    char *aux = malloc (sizeof(char) * 5); // Auxuliar para guardar o binário da letra (invertido)

    int n = c - 96; // Número que representa o caractere
    j = 0;
    while(n > 1){
        int i = n%2;
        aux[j] = i +'0'; //0 1 0 1
        n = floor(n/2); //10 5 2 1
        j++;
    }
    aux[j] = 1 + '0';

    for(j++; j < 5; j++){ // 
    aux[j] = 0 + '0';
   }

    j = 4;
    //printf("\nAux: %c %c %c %c %c", aux[0], aux[1], aux[2], aux[3], aux[4]);
    for(int i = k-1; i >= k-5;i--){bin[k-j-1] = aux[j];j--;} //Inverte o binário auxiliar
    free(aux);
}
void fConvertToBin(char *key, char *bin, int size){
    for(int i = 0; i < size; i++){
        fConvertLetter(key[i], bin, i+1);
        //int x = 5*i;
        //printf("\nLetra %c = %c %c %c %c %c", key[i], bin[x+0], bin[x+1], bin[x+2], bin[x+3], bin[x+4]);
    }
}

typeBit fGetNBit(typeIndex index, char *key){
    if(index == 0){return 0;}
    return key[index-1];
}

int IsOutside(pNode node){
    return (node->type == Outside);
}

pNode fGenOutsideNode(char *key){
    pNode node;
    node = (pNode) malloc (sizeof(tNode));
    node->type = Outside;
    node->Node.key = key;
    return node;
}

pNode fGenInsideNode(typeIndex nodeIndex, pNode *lef, pNode *rig){
    pNode node;
    node = (pNode) malloc (sizeof(tNode));
    node->type = Inside;
    node->Node.insideNode.index = nodeIndex;
    node->Node.insideNode.lef = *lef;
    node->Node.insideNode.rig = *rig;
    return node;
}

pNode fInsertIn(char *key, pNode *root, int index){
    pNode node;
    if(IsOutside(*root) || index < (*root)-> Node.insideNode.index){
        node = fGenOutsideNode(key);
        if (fGetNBit(index, key) == '1'){
            return (fGenInsideNode(index, root, &node));
        }
        else {
            return (fGenInsideNode(index, &node, root));
        }
    }
    else {
        if(fGetNBit((*root)->Node.insideNode.index, key) == '1'){
            (*root)->Node.insideNode.rig = fInsertIn(key, &(*root)->Node.insideNode.rig, index);
        }
        else{
            (*root)->Node.insideNode.lef = fInsertIn(key, &(*root)->Node.insideNode.lef, index);
        }
        return (*root);
    }
}

pNode fInsertWord(char *key, pNode *root){
    pNode node; 
    int index;
    int len = strlen(key);
    if(*root == NULL) return (fGenOutsideNode(key));
    else {
        node = *root;
        while(!IsOutside(node)){
            if(fGetNBit(node->Node.insideNode.index, key) == '1') node = node->Node.insideNode.rig;
            else node = node->Node.insideNode.lef;
        }
        index = 1;
        while((index <= len) && (fGetNBit(index, key) == fGetNBit(index, node->Node.key))){
            index++;
        }
        if(index > len) {
            printf("Erro: chave já inserida\n");
            return *root;
        }
        else {
            return (fInsertIn(key, root, index));
        }
    }
}

void fSearch(char *key, pNode node){
    while(!IsOutside(node)){
        if(fGetNBit(node->Node.insideNode.index, key) == '1') {
            node = node->Node.insideNode.rig;
        } else {
            node = node->Node.insideNode.lef;
        }
    }
    if(strcmp(node->Node.key, key) == 0) {
        printf("Chave encontrada: %s\n", key);
    } else {
        printf("Chave não encontrada: %s\n", key);
    }
}
