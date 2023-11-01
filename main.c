#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

typedef struct Palavra {
    char palavra[100];
    char dica[150];
    struct Palavra *next;
} Palavra;


int main() {
    int op;
    do {
        menu();
        scanf("%d", &op);
        printf("\n");
        switch (op) {
        case 3:
            printf("Projeto direcionado a disciplina de AED\n");
            printf("Desenvolvedores\n");
            printf("Danilo Albuquerque de Melo:\t dam@cesar.school\n");
            printf("Paulo Montenegro Campos:\t pmc3@cesar.school\n");
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