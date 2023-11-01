#include <stdio.h>

void pausa() {
    printf("\n\nPressione ENTER para continuar...\n\n");
    while (getchar() != '\n');
    getchar();
}

void menu() {
    printf("Selecione uma das opções e pressione ENTER\n");
    printf("1 - Jogar sozinho\n");
    printf("2 - Jogar em dupla\n");
    printf("3 - Sobre o jogo\n");
    printf("0 - Sair\n");
}