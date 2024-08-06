#include "../include/lista_TAD.h"
#include "../include/palavras_TAD.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Função para criar um novo nó
tNodeP* fCriatNodeP(const char *data) {
    tNodeP *newtNodeP = (tNodeP *)malloc(sizeof(tNodeP));
    if (newtNodeP == NULL) {
        perror("Erro ao alocar memória para um novo nó");
        exit(EXIT_FAILURE);
    }
    newtNodeP->data = strdup(data);
    if (newtNodeP->data == NULL) {
        perror("Erro ao duplicar string");
        exit(EXIT_FAILURE);
    }
    newtNodeP->next = NULL;
    return newtNodeP;
}

// Função para verificar se o valor já está na lista
int fVerifica(tNodeP *head, const char *data) {
    tNodeP *current = head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            return 1; // Valor encontrado
        }
        current = current->next;
    }
    return 0; // Valor não encontrado
}

// Função para inserir um valor na lista, se não for duplicado
void fInsere(tNodeP **head, const char *data) {
    if (*head == NULL) {
        *head = fCriatNodeP(data);
    } else if (!fVerifica(*head, data)) {
        tNodeP *newtNodeP = fCriatNodeP(data);
        newtNodeP->next = *head;
        *head = newtNodeP;
    }
}

// Função para liberar a memória da lista
void fLiberaMemoria(tNodeP *head) {
    tNodeP *current = head;
    tNodeP *next;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

// Função para remover caracteres específicos e espaços em uma string
void fRemoveCtr(char *str) {
    char *src = str;
    char *dst = str;
    int inside_word = 0;

    while (*src) {
        if (*src == ';') {
            *dst++ = *src++; // Copia o ';'
            // Pular espaços após ';'
            while (*src == ' ') {
                src++;
            }
            inside_word = 0; // Agora estamos fora de uma palavra
        } else if (*src == '.') {
            // Ignorar o '.' e qualquer espaço após ele
            src++;
            while (*src == ' ') {
                src++;
            }
            inside_word = 0; // Agora estamos fora de uma palavra
        } else if (isspace((unsigned char)*src)) {
            // Ignorar espaços em branco se estamos fora de uma palavra
            if (inside_word) {
                *dst++ = *src;
                inside_word = 0;
            }
            src++;
        } else {
            *dst++ = *src++;
            inside_word = 1; // Agora estamos dentro de uma palavra
        }
    }
    *dst = '\0'; // Adiciona o terminador nulo ao final da string
}

// Função que adiciona os ingredientes em uma lista a partir de um arquivo
int fAdicionaIgredientes(FILE *file, tNodeP **list) {
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        return 0; // Erro ao ler a primeira linha ou fim do arquivo
    }

    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        return 0; // Erro ao ler a segunda linha ou fim do arquivo
    }

    buffer[strcspn(buffer, "\n")] = '\0'; // Remove o caractere de nova linha

    char *item = strtok(buffer, ";");
    while (item != NULL) {
        fRemoveCtr(item);
        if (strlen(item) > 0) {
            fInsere(list, item);
        }
        item = strtok(NULL, ";");
    }

    return 1; // Sucesso ao adicionar ingredientes
}

// Função para contar o número de elementos na lista
int fTamLista(tNodeP *list) {
    int count = 0;
    tNodeP *current = list;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}
// Função para trocar os dados entre dois nós
void fTrocaNode(tNodeP *a, tNodeP *b) {
    tPalavra temp;
    temp.nome = a->data;
    a->data = b->data;
    b->data = temp.nome;
}

// Função para ordenar a lista de palavras em ordem alfabética
void fOrdenaLista(tNodeP *head) {
    if (head == NULL || head->next == NULL) {
        return; // A lista está vazia ou tem apenas um elemento
    }
    
    int swapped;
    tNodeP *ptr1;
    tNodeP *lptr = NULL; // Último nó já ordenado

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->data , ptr1->next->data ) > 0) {
                fTrocaNode(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}