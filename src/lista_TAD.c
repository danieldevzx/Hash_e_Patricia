#include "../include/lista_TAD.h"
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

//Função que adiciona os ingredientes em uma lista
int fAdicionaIgredientes(FILE *file, tNodeP **list) {
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        return 0;
    }

    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        return 0;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    char *item = strtok(buffer, ";");
    while (item != NULL) {
        fRemoveCtr(item);
        if (strlen(item) > 0) {
            fInsere(list, item);
        }
        item = strtok(NULL, ";");
    }


    return 1;
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