#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "library.h"

char palavrasecreta[TAMANHO_PALAVRA];

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
    Palavra *palavras = NULL;
    geraPalavrasOrdenada(&palavras);
    Palavra *palavrasecreta = noAleatorio(palavras);
    Caracteres *caracter = NULL;
    for (int i = 0; palavrasecreta->palavra[i] != '\0'; i++) {
        adicionaChar(&caracter, palavrasecreta->palavra[i]);
    }

    char palavraAdivinhada[strlen(palavrasecreta->palavra) + 1];
    memset(palavraAdivinhada, '_', strlen(palavrasecreta->palavra));
    palavraAdivinhada[strlen(palavrasecreta->palavra)] = '\0';
    int erros = 0, acertos = 0, tamanhoPalavra = strlen(palavrasecreta->palavra);

    printf("Seja bem-vindo, %s!\n", nome);

    while (erros < MAX_ERROS) {
        printf("Sua dica: %s\n", palavrasecreta->dica);
        printf("Tente acertar a palavra secreta: %s\n", palavraAdivinhada);
        desenhaForca(erros);
        printf("\nArrisque uma letra: ");
        char letra;
        scanf(" %c", &letra);

        if (adivinharLetra(caracter, palavraAdivinhada, letra)) {
            printf("Letra correta!\n");
            acertos++;
        } else {
            printf("Letra incorreta!\n");
            erros++;
        }
        limpaTela();
        if (strcmp(palavraAdivinhada, palavrasecreta->palavra) == 0) {
            venceu(nome);
            break; //ganhou
        }
        if (erros >= MAX_ERROS) {
            perdeu(nome);
            break;
        }
    }
    freeList(palavras);
    free(palavrasecreta);
    freeCaracteres(caracter);
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
            desenhaForca(0);
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

void desenhaForca(int erros) {

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

void venceu(char *nome){
    printf("\nParabens %s, você ganhou!\n\n", nome);

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

void perdeu(char *nome){
    printf("\nPuxa %s, você foi enforcado!\n\n", nome);

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

int sizeList(Palavra * Palavra){
    int size = 0;
    while(Palavra){
        size++;
        Palavra=Palavra->next;
    }
    return size;
}

void geraPalavrasOrdenada(Palavra **palavra) {
    adicionarPalavra(palavra, "programacao", "Trabalho muito legal");
    adicionarPalavra(palavra, "matematica", "Fundamental para a vida");
    adicionarPalavra(palavra, "informatica", "O futuro da humanidade");
    adicionarPalavra(palavra, "filosofia", "Pensamento e existencia");
    adicionarPalavra(palavra, "Portugues", "A linguagem do brasil");
    adicionarPalavra(palavra, "geografia", "Do mundo ao nosso lar");
    adicionarPalavra(palavra, "historia", "Tempos passados e presentes");
    adicionarPalavra(palavra, "literatura", "Leitura eh vida");
    adicionarPalavra(palavra, "biologia", "Vida no universo");
    adicionarPalavra(palavra, "fisica", "Natureza e forca");
    //ordenando lista
    insertionSortList(palavra);
}

Palavra *noAleatorio(Palavra *palavra) {
    int tamanho = sizeList(palavra);
    
    if (tamanho == 0) {
        printf("Lista vazia!\n");
        return NULL; // A lista está vazia.
    }
    srand(time(NULL));
    
    int indiceAleatorio = rand() % tamanho;
    for (int i = 0; i < indiceAleatorio; i++) {
        palavra = palavra->next;
    }
    
    return palavra;
}

void insertionSortList(Palavra **head) {

    // A lista está vazia ou tem apenas um elemento, ou seja já está ordenada.
    if (*head == NULL || (*head)->next == NULL) return; 
    

    Palavra *sorted = NULL; 

    Palavra *current = *head;
    while (current) {
        Palavra *next = current->next;
        if (sorted == NULL || strcmp(current->palavra, sorted->palavra) < 0) {
            current->next = sorted;
            sorted = current;
        } else {
            Palavra *temp = sorted;
            while (temp->next != NULL && strcmp(current->palavra, temp->next->palavra) > 0) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next;
    }
    *head = sorted;
}

void imprimirLista(Palavra *lista) {
    while (lista) {
        printf("Palavra: %s\n", lista->palavra);
        printf("Dica: %s\n", lista->dica);
        printf("\n");
        lista = lista->next;
    }
}
void imprimirP(Caracteres *lista) {
    while (lista) {
        printf("Palavra: %c\n", lista->character);
        printf("\n");
        lista = lista->next;
    }
}
int adivinharLetra(Caracteres *caracter, char *palavraAdivinhada, char letra) {
    int correta = 0;
    Caracteres *current = caracter;
    int i = 0;

    while (current != NULL) {
        if (current->character == letra) {
            palavraAdivinhada[i] = letra;
            correta = 1;
        }
        current = current->next;
        i++;
    }

    return correta;
}


void freeList(Palavra * palavra) {
    while (palavra) {
        Palavra* temp =palavra;
        palavra = palavra->next;
        free(temp);
    }
}

void freeCaracteres(Caracteres *c){
    while (c) {
        Caracteres* temp= c;
        c = c -> next;
        free(temp);
    }
}
void adicionaChar(Caracteres** head, char character) {
    Caracteres* newChar =(Caracteres*) malloc(sizeof(Caracteres));

    if (newChar == NULL) {
        // Handle memory allocation error
        exit(EXIT_FAILURE);
    }

    newChar->character = character;
    newChar->next = NULL;

    if (*head == NULL) {
        *head = newChar;
    } else {
         Caracteres* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newChar;
    }
}