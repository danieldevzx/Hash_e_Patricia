#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "patricia_TAD.c"

int main(){

    tRoot root;

    char wordA[] = "Viado";
    //char wordB[] = "Viagra";
    //char wordC[] = "Banana";

    fInsertWords(&root, wordA, strlen(wordA));
    //main

    return 0;
}
