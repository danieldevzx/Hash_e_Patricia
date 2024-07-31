#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include <stdio.h>

typedef struct {
    FILE *arquivo;
} Arquivo;

int abreArquivo(char *nome, Arquivo *arquivo);
int fechaArquivo(char *nome, Arquivo *arquivo);

#endif
