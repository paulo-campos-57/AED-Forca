#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

int main() {
    int op;
    char nome1[50];
    char nome2[50];
    Palavra *palavras = NULL;

    do {
        menu();
        scanf("%d", &op);
        printf("\n");
        switch (op) {
        case 1:
            printf("Informe o seu nome: ");
            scanf(" %[^\n]", nome1);
            if (nome1[strlen(nome1) - 1] == '\n') {
                nome1[strlen(nome1) - 1] = '\0';
            }
            jogoSolo(nome1);
            break;
        case 2:
            printf("Informe o nome do primeiro jogador: ");
            scanf(" %[^\n]", nome1);
            if (nome1[strlen(nome1) - 1] == '\n') {
                nome1[strlen(nome1) - 1] = '\0';
            }
            printf("\nInforme o nome do segundo jogador: ");
            scanf(" %[^\n]", nome2);
            if (nome2[strlen(nome2) - 1] == '\n') {
                nome2[strlen(nome2) - 1] = '\0';
            }
            printf("\n");
            jogoDupla(nome1, nome2, &palavras);
            break;
        case 3:
            printSobre();
            break;
        case 0:
            printf("Operacao encerrada\n");
            break;
        default:
            printf("Opção inválida\n");
            break;
        }
        if (op != 0) {
            pausa();
        }
    } while(op != 0);
    exit(EXIT_SUCCESS);
}