#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "patricia_TAD.c"

int main(){

    printf("Vamo que vai dar bom");
    char test[] = "abacaxi"; // Palavra teste pra conversão em binário
    int len = sizeof(test)-1; //Tamanho da palavra
    char word[len*5]; // Vetor para resultado da conversão
    printf("\nTam: %i", len);
    fConvertToBin(test, word, sizeof(test)-1);
    fPrintKey(word);

    char test2[] = "abacaxis";
    len = sizeof(test2)-1;
    char word2[len*5];
    printf("\nTam: %i", len);
    fConvertToBin(test2, word2, len);
    fPrintKey(word2);

    return 0;
}
