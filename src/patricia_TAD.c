#include "../include/patricia_TAD.h"
static unsigned int compI = 0;
static unsigned int compP = 0;

int fPatriciaEhExterno(tNodePT *node){
    assert(node != NULL);
    return node->tipo == EXTERNO;
}

int fPatriciaDirecao(int index, tPalavra item, char pivo){
    return (item.nome[index] > pivo);
}

tNodePT *fPatriciaCriaNodeInterno(tNodePT *esq, tNodePT *dir, int index, char letra){
    tNodePT *novoNode = (tNodePT *) malloc(sizeof(tNodePT));
    if(novoNode == NULL) {
        perror("Erro ao alocar memória para nó interno");
        exit(EXIT_FAILURE);
    }
    novoNode->tipo = INTERNO;
    novoNode->node.nodeInterno.esq = esq;
    novoNode->node.nodeInterno.dir = dir;
    novoNode->node.nodeInterno.index = index;
    novoNode->node.nodeInterno.letra = letra;

    return novoNode;
}

tNodePT *fPatriciaCriaNodeExterno(tPalavra item){
    assert(item.nome != NULL);

    tNodePT *novoNode = (tNodePT *) malloc(sizeof(tNodePT));
    if(novoNode == NULL) {
        perror("Erro ao alocar memória para nó externo");
        exit(EXIT_FAILURE);
    }
    novoNode->tipo = EXTERNO;
    novoNode->node.item = item;
    return novoNode;
}

tNodePT *fPatriciaInsereEntre(tNodePT *nodeAtual, tPalavra item, int index, char letraNoInterno){
    tNodePT *novoNode;

    if (fPatriciaEhExterno(nodeAtual) || index < nodeAtual->node.nodeInterno.index) {
        novoNode = fPatriciaCriaNodeExterno(item);

        if (fPatriciaDirecao(index, item, letraNoInterno))
            return fPatriciaCriaNodeInterno(nodeAtual, novoNode, index, letraNoInterno);
        else
            return fPatriciaCriaNodeInterno(novoNode, nodeAtual, index, letraNoInterno);
    } else {
        if (fPatriciaDirecao(nodeAtual->node.nodeInterno.index, item, nodeAtual->node.nodeInterno.letra)) {
            nodeAtual->node.nodeInterno.dir = fPatriciaInsereEntre(nodeAtual->node.nodeInterno.dir, item, index, letraNoInterno);
        } else {
            nodeAtual->node.nodeInterno.esq = fPatriciaInsereEntre(nodeAtual->node.nodeInterno.esq, item, index, letraNoInterno);
        }
        return nodeAtual;
    }
}

tNodePT *fPatriciaInsere(tNodePT **raiz, tPalavra item){
    assert(item.nome != NULL);

    int index = 0;
    char letraNoInterno;
    tNodePT *novoNode;

    if (*raiz == NULL) {
        return fPatriciaCriaNodeExterno(item);
    }

    novoNode = *raiz;

    while (!fPatriciaEhExterno(novoNode)) {
        compI++;
        if (fPatriciaDirecao(novoNode->node.nodeInterno.index, item, novoNode->node.nodeInterno.letra)) {
            novoNode = novoNode->node.nodeInterno.dir;
        } else {
            novoNode = novoNode->node.nodeInterno.esq;
        }
    }

    index = 0;
    while ((index < strlen(item.nome)) && (item.nome[index] == novoNode->node.item.nome[index])) {
        index++;
    }

    if (novoNode->node.item.nome[index] < item.nome[index]) {
        letraNoInterno = novoNode->node.item.nome[index];
    } else {
        letraNoInterno = item.nome[index];
    }

    return fPatriciaInsereEntre(*raiz, item, index, letraNoInterno);
}

void fPrintPatriciaAux(tNodePT *node, int level) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < level; i++) {
        printf(" ");
    }

    if (node->tipo == INTERNO) {
        printf("I:('%c',%d)\n",
               node->node.nodeInterno.letra,
               node->node.nodeInterno.index);
        fPrintPatriciaAux(node->node.nodeInterno.esq, level + 1);
        fPrintPatriciaAux(node->node.nodeInterno.dir, level + 1);
    } else {
        tNodeID *nodeP = node->node.item.node;
        printf("E:'%s':[",
               node->node.item.nome);
        while (nodeP != NULL) {
            printf("<%d,%d>", nodeP->data.qtd, nodeP->data.arq);
            nodeP = nodeP->next;
        }
        printf("]\n");
    }
}

void fPrintPatricia(tNodePT *raiz) {
    printf("Árvore Patricia:\n");
    fPrintPatriciaAux(raiz, 0);
}

void fLiberaPatricia(tNodePT *raiz) {
    if (raiz == NULL) {
        return;
    }

    if (raiz->tipo == INTERNO) {
        fLiberaPatricia(raiz->node.nodeInterno.esq);
        fLiberaPatricia(raiz->node.nodeInterno.dir);
    }

    free(raiz);
}

tNodePT *fPesquisaPatricia(tNodePT *raiz, char *nome) {
    tNodePT *nodeAtual = raiz;

    while (nodeAtual != NULL && !fPatriciaEhExterno(nodeAtual)) {
        compP++;
        if (fPatriciaDirecao(nodeAtual->node.nodeInterno.index, (tPalavra){nome, NULL}, nodeAtual->node.nodeInterno.letra)) {
            nodeAtual = nodeAtual->node.nodeInterno.dir;
        } else {
            nodeAtual = nodeAtual->node.nodeInterno.esq;
        }
    }

    if (nodeAtual != NULL && strcmp(nodeAtual->node.item.nome, nome) == 0) {
        return nodeAtual;
    }

    return NULL;
}
unsigned int fGetCompIPatricia() {
    return compI;
}

unsigned int fGetCompPPatricia() {
    return compP;
}
