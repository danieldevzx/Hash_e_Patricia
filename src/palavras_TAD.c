#include "../include/palavras_TAD.h"


// Cria um tID com a quantidade e o número do arquivo fornecidos
tID fCriaID(int qtd, int arq) {
    tID id;
    id.qtd = qtd;
    id.arq = arq;
    return id;
}

// Cria um novo nó para uma lista encadeada de tID
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

// Adiciona um nó contendo tID a uma lista encadeada
void fAdicionaNode(tNodeID **head, tID aux) {
    tNodeID *newNode = fNodeDeID(aux);
    newNode->next = *head;
    *head = newNode;
}

// Salva uma palavra e sua lista encadeada de tID
void fSalvaPalavra(tPalavra *palavra, char *nome, tNodeID *id) {
    palavra->nome = strdup(nome);
    if (palavra->nome == NULL) {
        perror("Erro ao alocar memória para o nome da palavra");
        exit(EXIT_FAILURE);
    }
    palavra->node = id;
}

// Libera a memória alocada para uma lista encadeada de tNodeID
void fLiberaLista(tNodeID *head) {
    tNodeID *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Processa uma lista de palavras e armazena suas quantidades e números de arquivo em uma lista de tPalavra
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

// Imprime os dados de uma palavra
void fPrintPalavra(tPalavra palavra) {
    printf("Palavra: %s\n[", palavra.nome);
    tNodeID *currentNode = palavra.node;
    while (currentNode != NULL) {
        printf("<%d,%d>", currentNode->data.qtd, currentNode->data.arq);
        currentNode = currentNode->next;
    }
    printf("]\n");
}

// Imprime os dados de todas as palavras em um vetor
void fPrintDados(tPalavra *v, int tam) {
    for (int i = 0; i < tam; i++) {
        printf("Palavra[%d]: %s\n", i + 1, v[i].nome);
        tNodeID *currentNode = v[i].node;
        while (currentNode != NULL) {
            printf("<%d,%d>", currentNode->data.qtd, currentNode->data.arq);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}


// Função para calcular o TF-IDF para uma palavra
tID fMaiorID(tPalavra *palavra, int totalDocumentos) {
    // Inicializa variáveis para armazenar o maior TF-IDF e o tID correspondente
    double maiorTFIDF = 0.0;
    tID maiorID = {0, 0};
    
    // Obtém o total de documentos que contêm a palavra
    int documentosContendoPalavra = 0;
    tNodeID *current = palavra->node;
    while (current != NULL) {
        documentosContendoPalavra++;
        current = current->next;
    }
    
    // Se a palavra não aparece em nenhum documento, retorna um tID vazio
    if (documentosContendoPalavra == 0) {
        return maiorID;
    }
    
    // Itera sobre a lista de tID e calcula o TF-IDF para cada documento
    current = palavra->node;
    while (current != NULL) {
        // Aqui, consideramos que o número total de palavras no documento não está disponível,
        // então a TF é assumida como `qtd` e a IDF é calculada como log(N / documentosContendoPalavra).
        double tf = (double)current->data.qtd; // Número de vezes que a palavra aparece
        double idf = log((double)totalDocumentos / documentosContendoPalavra);
        double tfidf = tf * idf;

        // Atualiza o maior TF-IDF e o tID correspondente
        if (tfidf > maiorTFIDF) {
            maiorTFIDF = tfidf;
            maiorID = current->data;
        }
        current = current->next;
    }
    
    return maiorID;
}
