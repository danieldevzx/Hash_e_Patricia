#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Função para limpar a tela
void limpa() {
    #ifdef _WIN32
        // Sistema Windows
        if (system("cls")) {
            fprintf(stderr, "Erro ao executar o comando 'cls'\n");
        }
    #elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
        // Sistemas Unix-like (incluindo macOS)
        if (system("clear")) {
            fprintf(stderr, "Erro ao executar o comando 'clear'\n");
        }
    #else
        // Sistema desconhecido
        fprintf(stderr, "Sistema não suportado para limpeza de tela\n");
    #endif
}

// Função para pausar a execução e aguardar a entrada do usuário
void pausa() {
    #ifdef _WIN32
        // Sistema Windows
        if (system("pause")) {
            fprintf(stderr, "Erro ao executar o comando 'pause'\n");
        }
    #elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
        // Sistemas Unix-like (incluindo macOS)
        printf("Pressione Enter para continuar...\n");
        fflush(stdout); // Garante que a mensagem seja exibida antes de aguardar a entrada
        char buffer[100];
        fgets(buffer, sizeof(buffer), stdin); // Lê a entrada do usuário
    #else
        // Sistema desconhecido
        fprintf(stderr, "Sistema não suportado para pausa\n");
    #endif
}
