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

typedef struct
{
    int qtde;
    int idDoc;
} tIndex;

typedef struct tNode *pNode;

typedef struct
{
    char chave;
    int EndOfWord;
    int length;
    pNode pLeft, pRight; /* Esquerda palvra de mesmo tamanho <-> Direita tamanho maior */
    tIndex *indexes;
} tNode;

typedef struct
{
    tNode *initialLetters;
} tRoot;

void fInsertWords(tRoot *root, char key[], int length);

void fSearch(tRoot *root, char key[]);

void IndexSorter(tIndex *indexes);
#endif