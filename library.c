#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void telaInicial() {
    printf(" __________    _________     _______     ________      _________\n");
    printf("|  ________|  |  _____  |   |  ___  |   |  ______|    |  _____  |\n");
    printf("| |______     | |     | |   | |___|_|   | |           | |     | |\n");
    printf("|  ______|    | |     | |   |  __|      | |          | |_______| |\n");
    printf("| |           | |     | |   | ||_|_     | |          |  _______  |\n");
    printf("| |           | |_____| |   | |  |_|_   | |______    | |       | |\n");
    printf("|_|           |_________|   |_|    |_|  |________|   |_|       |_|\n");
    printf("\n");
}

void limpaTela() {
    #ifdef _WIN32
    system("cls"); // No Windows
    #else
    printf("\033[H\033[J"); // Em sistemas Unix-like
    #endif
}

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

void jogoDupla(char *j1, char *j2, Palavra **listaPalavras) {
    printf("Jogador 1: %s\n", j1);
    printf("Jogador 2: %s\n", j2);
    char pl[100];
    char d[150];
    pausa();
    limpaTela();
    int vez = 1;
    int j1Pontos = 0;
    int j2Pontos = 0;
    while (vez != 0) {
        char *jogadorVez = NULL;
        jogadorVez = (vez % 2 != 0) ? j1 : j2;
        printf("%s, informe a palavra secreta: ", jogadorVez);
        scanf(" %[^\n]", pl);
        if (pl[strlen(pl) - 1] == '\n') {
            pl[strlen(pl) - 1] = '\0';
        }
        printf("\nAgora informe a dica: ");
        scanf(" %[^\n]", d);
        adicionarPalavra(listaPalavras, pl, d);
        printf("Palavra adicionada!\n");
        pausa();
        limpaTela();
        int tentativas = 7;
        char *outroJogador = (vez % 2 != 0) ? j2 : j1;
        printf("%s, sua vez! tente acertar a palavra secreta!\n", outroJogador);
        while (tentativas > 0) {
            desenhaForca();
            printf("Pontuacao %s: %d\n", j1, j1Pontos);
            printf("Pontuacao %s: %d\n", j2, j2Pontos);
            printf("Dica: %s", d);
            printf("\nTotal de tentativas: %d", tentativas);
            printf("\nArrisque uma letra: ");
            char letra;
            scanf(" %c", &letra);
            tentativas--;
            limpaTela();
        }
        printf("A palavra era %s\n", pl);
        if (vez %2 != 0) {
            printf("%s não acertou a palavra, portanto, %s pontuou!\n", j2, j1);
            j1Pontos++;
        } else {
            printf("%s não acertou a palavra, portanto, %s pontuou!\n", j1, j2);
            j2Pontos++;
        }
        char continuar;
        printf("\nDesejam continuar jogando?\n[S - sim/N - nao]\n");
        scanf(" %c", &continuar);
        if (continuar != 'S') {
            break;
        }
        limpaTela();
        vez++;
    } 
}

void printSobre(){
    printf("Projeto direcionado a disciplina de AED - Jogo da forca\n");
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
}

void adicionarPalavra(Palavra **palavras, char *pl, char *d) {
    Palavra *novaPalavra = (Palavra *)malloc(sizeof(Palavra));
    if (novaPalavra == NULL) {
        printf("Erro na alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(novaPalavra -> palavra, pl);
    strcpy(novaPalavra -> dica, d);
    novaPalavra -> next = *palavras;
    *palavras = novaPalavra;
}

void trofeu(){
    printf("\nParabéns, você ganhou!\n\n");

    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");
}

void caveira(){
    printf("\nPuxa, você foi enforcado!\n");

    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
}