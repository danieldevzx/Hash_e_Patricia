// fFunção
// pPonteiro
// tTad

/* Lista de funções
-Inserção Palavras
-Inicializar
-Ordenador de índices
-Pesquisa
*/
#ifndef PATRICIA_TAD_H_INCLUDED
#define PATRICIA_TAD_H_INCLUDED

#include "palavras_TAD.h"

typedef struct PatriciaNode PatriciaNode;
typedef struct {
    PatriciaNode *root;
} PatriciaTree;

PatriciaTree* createPatricia();
void insertPatricia(PatriciaTree *tree, const char *key, tIndiceInvertido indice);
PatriciaNode* searchPatricia(PatriciaTree *tree, const char *key);
void printPatriciaNode(PatriciaNode *node);
void printPatricia(PatriciaTree *tree);
void liberaPatricia(PatriciaTree *tree);
char* palavraParaBinario(const char *palavra);

typedef struct tInvertedIndex *pInvertedIndexes;
typedef struct tInvertedIndex {
    int qtnd, idDoc;
    int len;
} tInvertedIndex;

typedef int typeIndex;
typedef int typeBit;
typedef enum {
    Inside, Outside
} typeOfNode;

typedef struct tNode *pNode;
typedef struct tNode {
    typeOfNode type;
    union {
        struct {
            typeIndex index;
            pNode lef, rig;
        } insideNode;
        struct {
            char *key;
            pInvertedIndexes indexesList;
        } outsideNode;
    } Node;
} tNode;

void fPrintKey(char *key, int len);
void fConvertToBin(char *key, char *bin, int size);
typeBit fGetNBit(typeIndex index, char *key);
int IsOutside(pNode node);
pNode fGenOutsideNode(char *key, int idDoc);
pNode fGenInsideNode(int nodeIndex, pNode *lef, pNode *rig);
pNode fInsertIn(char *key, pNode node, int index, int idDoc);
pNode fInsertWord(char *key, pNode *node, int len, int idDoc);
void fPrintInvertedIndexes(pInvertedIndexes indexesList);
void fSearch(char *key, pNode node);

#endif
