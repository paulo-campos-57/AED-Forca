#include <stdio.h>
#include "library.h"

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
    desenhaForca();
}

void jogoDupla(char *j1, char *j2) {
    printf("Jogador 1: %s\n", j1);
    printf("Jogador 2: %s\n", j2);
    desenhaForca();
}

void printSobre(){
    printf("Projeto direcionado a disciplina de AED\n");
    printf("Desenvolvedores\n");
    printf("Danilo Albuquerque de Melo:\t dam@cesar.school\n");
    printf("Paulo Montenegro Campos:\t pmc3@cesar.school\n");
}


void desenhaForca() {

    int erros = 0;

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");
/*
    for(int i = 0; i < strlen(palavrasecreta); i++) {

        if(jachutou(palavrasecreta[i])) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }

    }
    printf("\n");
*/
}