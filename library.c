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

void jogoSolo(char *nome) {
    printf("Seja bem vindo %s!\n", nome);
}

void jogoDupla(char *j1, char *j2) {
    printf("Jogador 1: %s\n", j1);
    printf("Jogador 2: %s\n", j2);
}

void printSobre(){
    printf("Projeto direcionado a disciplina de AED\n");
    printf("Desenvolvedores\n");
    printf("Danilo Albuquerque de Melo:\t dam@cesar.school\n");
    printf("Paulo Montenegro Campos:\t pmc3@cesar.school\n");
}