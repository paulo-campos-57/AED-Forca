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
void printSobre(){
    printf("Projeto direcionado a disciplina de AED\n");
    printf("Desenvolvedores\n");
    printf("Danilo Albuquerque de Melo:\t dam@cesar.school\n");
    printf("Paulo Montenegro Campos:\t pmc3@cesar.school\n");
}