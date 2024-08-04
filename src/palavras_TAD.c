#include "../include/palavras_TAD.h"
tID fCriaID(int qtd, int arq) {
    tID id;
    id.qtd = qtd;
    id.arq = arq;
    return id;
}

tNodeID *fNodeDeID(tID aux) {
    tNodeID *node = (tNodeID *)malloc(sizeof(tNodeID));
    if (node == NULL) {
        perror("Erro ao alocar memória para o nó");
        exit(EXIT_FAILURE);
    }
    node->data = aux;
    node->next = NULL;
    return node;
}
void fAdicionaNode(tNodeID **head, tID aux) {
    tNodeID *newNode = fNodeDeID(aux);
    newNode->next = *head;
    *head = newNode;
}

void fSalvaPalavra(tPalavra *palavra, char *nome, tNodeID *id) {
    palavra->nome = strdup(nome);
    if (palavra->nome == NULL) {
        perror("Erro ao alocar memória para o nome da palavra");
        exit(EXIT_FAILURE);
    }
    palavra->node = id;
}
void fLiberaLista(tNodeID *head) {
    tNodeID *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}
void fProcessaPalavras(tNodeP *listaDePalavras, char **arquivos, int qtd, tPalavra *v) {
    // Obter o tamanho da lista de palavras
    int tam = fTamLista(listaDePalavras);
    
    // Processar cada palavra na lista
    tNodeP *current = listaDePalavras;
    for (int i = 0; i < tam; i++) {
        tNodeID *lista = NULL;
        for (int j = 0; j < qtd; j++) {
            int t = fContaIngredientes(arquivos[j], current->data);
            if (t > 0) {
                fAdicionaNode(&lista, fCriaID(t, j + 1));
            }
        }
        fSalvaPalavra(&v[i], current->data, lista);
        current = current->next;
    }
}
void fPrintPalavra(tPalavra palavra){
    printf("Palavra: %s\n[", palavra.nome);
    tNodeID *currentNode = palavra.node;
    while (currentNode != NULL) {
        printf("<%d,%d>", currentNode->data.qtd, currentNode->data.arq);
        currentNode = currentNode->next;
    }
    printf("]\n");
}
void fPrintDados(tPalavra *v, int tam){
    for (int i = 0; i < tam; i++) {
        printf("Palavra[%d]: %s\n", i+1,v[i].nome);
        tNodeID *currentNode = v[i].node;
        while (currentNode != NULL) {
            printf("<%d,%d>", currentNode->data.qtd, currentNode->data.arq);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}