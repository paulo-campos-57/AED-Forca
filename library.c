#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include "library.h"

char palavrasecreta[TAMANHO_PALAVRA];

// Funções auxiliares
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
/*---------------------------------------------------------------------------------------*/

// Funções de interface
void telaInicial() {
    printf("\033[1;32m");
    printf(" __________    _________     _______     ________      _________\n");
    printf("|  ________|  |  _____  |   |  ___  |   |  ______|    |  _____  |\n");
    printf("| |______     | |     | |   | |___|_|   | |           | |     | |\n");
    printf("|  ______|    | |     | |   |  __|      | |          | |_______| |\n");
    printf("| |           | |     | |   | ||_|_     | |          |  _______  |\n");
    printf("| |           | |_____| |   | |  |_|_   | |______    | |       | |\n");
    printf("|_|           |_________|   |_|    |_|  |________|   |_|       |_|\n");
    printf("\033[0m");
    printf("\n");
}

void menu() {
    printf("Selecione uma das opções e pressione ENTER\n");
    printf("1 - Jogar sozinho\n");
    printf("2 - Jogar em dupla\n");
    printf("3 - Placares de lideres\n");
    printf("4 - Sobre o jogo\n");
    printf("0 - Sair\n");
}

void printSobre(){
    printf("Projeto direcionado a disciplina de AED - Jogo da forca\n");
    printf("Desenvolvido em linguagem C, por:\n");
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

void venceu(char *nome){
    printf("\033[1;33m"); 
    printf("\nParabens %s, voce ganhou!\n\n", nome);

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
    printf("\033[0m");
}

void perdeu(char *nome){
    printf("\033[1;31m");
    printf("\nPuxa %s, voce foi enforcado!\n\n", nome);
    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX    |/     \n");
    printf(" |   XXX       XXX    |      \n");
    printf(" |                    |      \n");
    printf(" \\__     XXX      __/     \n");
    printf("   |\\    XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_            _/       \n");
    printf("     \\_        _/         \n");
    printf("       \\______/           \n");
    printf("\033[0m");
}
/*---------------------------------------------------------------------------------------*/

// Funções de jogo
void jogoSolo(char *nome) {
    int pontuacao = 0;
    char letrasArriscadas[MAX_TENTATIVAS];
    Palavra *palavras = NULL;
    while (1) {
        //gerando e ordenando lista
        if (palavras == NULL) {
            Palavra *ultimo = geraPalavrasOrdenada(&palavras);
            quickSortList(palavras, ultimo);
        }

        Palavra *palavrasecreta = noAleatorio(palavras);
        Caracteres *caracter = NULL;
        for (int i = 0; palavrasecreta->palavra[i] != '\0'; i++) {
            adicionaChar(&caracter, palavrasecreta->palavra[i]);
        }

        char palavraAdivinhada[strlen(palavrasecreta->palavra) + 1];
        memset(palavraAdivinhada, '_', strlen(palavrasecreta->palavra));
        palavraAdivinhada[strlen(palavrasecreta->palavra)] = '\0';

        int erros = 0, acertos = 0, tentativas = 0, tamanhoPalavra = strlen(palavrasecreta->palavra);

        memset(letrasArriscadas, 0, sizeof(letrasArriscadas));

        printf("Seja bem-vindo, %s!\n", nome);

        while (erros < MAX_ERROS) {
            desenhaForca(erros);
            printf("Sua pontuacao: %d\n", pontuacao);
            printf("Sua dica: %s\n", palavrasecreta->dica);
            printf("Tente acertar a palavra secreta: %s\n", palavraAdivinhada);
            printf("Letras arriscadas: [ ");
            for (int i = 0; i < tentativas; i++) {
                printf("%c ", letrasArriscadas[i]);
            }
            printf("]\n");
            printf("\nArrisque uma letra: ");
            char letra;
            scanf(" %c", &letra);
            if (isalpha(letra)) {
                letra = tolower(letra);
            }

            // Verifica se a letra já foi arriscada
            if (letraJaArriscada(letra, letrasArriscadas) != 0) {
                printf("Voce ja arriscou essa letra. Tente outra!\n");
                sleep(1);
                limpaTela();
                continue;
            }

            letrasArriscadas[tentativas] = letra;
            letrasArriscadas[tentativas + 1] = '\0';
            tentativas++;

            if (adivinharLetra(caracter, palavraAdivinhada, letra)) {
                printf("Letra correta!\n");
                acertos++;
            } else {
                printf("Letra incorreta!\n");
                erros++;
            }
            sleep(1);
            limpaTela();
            if (strcmp(palavraAdivinhada, palavrasecreta->palavra) == 0) {
                venceu(nome);
                pontuacao++;
                break;
            }
            if (erros >= MAX_ERROS) {
                perdeu(nome);
                printf("\n\nA palavra era %s\n", palavrasecreta->palavra);
                break;
            }
        }
        char continuar;
        printf("\nDeseja continuar jogando?\n[S - sim/N - nao]\n");
        scanf(" %c", &continuar);
        continuar = toupper(continuar);
        if (continuar != 'S') {
            salvarPlacar(nome, pontuacao);
            freeCaracteres(caracter);
            freeList(palavras);
            break;
        }

        limpaTela();
    }
}

void jogoDupla(char *j1, char *j2) {
    printf("Jogador 1: %s\n", j1);
    printf("Jogador 2: %s\n", j2);
    char palavra[100];
    char dica[150];
    pausa();
    limpaTela();
    int vez = 1;
    int j1Pontos = 0;
    int j2Pontos = 0;
    while (vez != 0) {
        char *jogadorVez = NULL;
        Caracteres *caracter = NULL;
        jogadorVez = (vez % 2 != 0) ? j1 : j2;
        printf("%s, informe a palavra secreta: ", jogadorVez);
        scanf(" %[^\n]", palavra);
        
        if (palavra[strlen(palavra) - 1] == '\n') {
            palavra[strlen(palavra) - 1] = '\0';
        }
        
        for (int i = 0; palavra[i] != '\0'; i++) {
            adicionaChar(&caracter, palavra[i]);
        }
        
        char palavraAdivinhada[strlen(palavra) + 1];
        memset(palavraAdivinhada, '_', strlen(palavra));
        palavraAdivinhada[strlen(palavra)] = '\0';
        char letrasArriscadas[MAX_TENTATIVAS];
        
        printf("\nAgora informe a dica: ");
        scanf(" %[^\n]", dica);
        printf("Palavra adicionada!\n");
        int erros = 0;
        int acertos = 0;
        int tamanhoPalavra = strlen(palavra);
        pausa();
        limpaTela();
        char *outroJogador = (vez % 2 != 0) ? j2 : j1;
        int tentativas = 0;
        printf("%s, sua vez! tente acertar a palavra secreta!\n", outroJogador);

        while (erros < MAX_ERROS) {

            desenhaForca(erros);
            printf("Pontuacao %s: %d\n", j1, j1Pontos);
            printf("Pontuacao %s: %d\n", j2, j2Pontos);
            printf("Dica: %s\n", dica);
            printf("\nTente acertar a palavra: %s\n", palavraAdivinhada);
            printf("Letras arriscadas: [ ");

            for (int i = 0; i < tentativas; i++) {
                printf("%c ", letrasArriscadas[i]);
            }
            printf("]\n");
            printf("\nArrisque uma letra: ");
            char letra;
            scanf(" %c", &letra);
            if (isalpha(letra)) {
                letra = tolower(letra);
            }

            // Verifica se a letra já foi arriscada
            if (letraJaArriscada(letra, letrasArriscadas) != 0) {
                printf("Voce ja arriscou essa letra. Tente outra!\n");
                sleep(1);
                limpaTela();
                continue;
            }

            letrasArriscadas[tentativas] = letra;
            letrasArriscadas[tentativas + 1] = '\0';
            tentativas++;

            if (adivinharLetra(caracter, palavraAdivinhada, letra)) {
                printf("Letra correta!\n");
                acertos++;
            } else {
                printf("Letra incorreta!\n");
                erros++;
            }
            sleep(1);
            limpaTela();
            if (strcmp(palavraAdivinhada, palavra) == 0) {
                venceu(outroJogador);
                (vez % 2 == 0) ? j1Pontos++ : j2Pontos++;
                break;
            }
            if (erros >= MAX_ERROS) {
                perdeu(outroJogador);
                (vez % 2 == 0) ? j2Pontos++ : j1Pontos++;
                break;
            }
        }
        freeCaracteres(caracter);
        printf("A palavra era %s\n", palavra);
        char continuar;
        printf("\nDesejam continuar jogando?\n[S - sim/N - nao]\n");
        scanf(" %c", &continuar);
        continuar = toupper(continuar);
        if (continuar != 'S') {
            salvarPlacar(j1, j1Pontos);
            salvarPlacar(j2, j2Pontos);
            break;
        }
        limpaTela();
        vez++;
    } 
}

int letraJaArriscada(char letra, const char *letrasArriscadas) {
    for (int i = 0; letrasArriscadas[i] != '\0'; i++) {
        if (letrasArriscadas[i] == letra) {
            return 1;
        }
    }
    return 0;
}

void salvarPlacar(const char *nome, int pontuacao) {
    FILE *arquivo = fopen("placar.txt", "a"); 

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo de placar.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivo, "Nome: %s, Pontuacao: %d\n", nome, pontuacao);

    fclose(arquivo);
}

void adicionarPalavra(Palavra **palavras, char *pl, char *d) {
    Palavra *novaPalavra = (Palavra *)malloc(sizeof(Palavra));
    if (novaPalavra == NULL) {
        perror("Erro na alocacao de memoria.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(novaPalavra -> palavra, pl);
    strcpy(novaPalavra -> dica, d);
    novaPalavra -> next = *palavras;
    *palavras = novaPalavra;
}

int sizeList(Palavra * Palavra){
    int size = 0;
    while(Palavra){
        size++;
        Palavra=Palavra->next;
    }
    return size;
}
    
Palavra *geraPalavrasOrdenada(Palavra **palavra) {
    adicionarPalavra(palavra, "programacao", "Trabalho muito legal");
    adicionarPalavra(palavra, "matematica", "Fundamental para a vida");
    adicionarPalavra(palavra, "informatica", "O futuro da humanidade");
    adicionarPalavra(palavra, "filosofia", "Pensamento e existencia");
    adicionarPalavra(palavra, "portugues", "A linguagem do brasil");
    adicionarPalavra(palavra, "geografia", "Do mundo ao nosso lar");
    adicionarPalavra(palavra, "historia", "Tempos passados e presentes");
    adicionarPalavra(palavra, "literatura", "Leitura eh vida");
    adicionarPalavra(palavra, "biologia", "Vida no universo");
    adicionarPalavra(palavra, "fisica", "Natureza e forca");
    adicionarPalavra(palavra, "paralelepipedo", "Forma geometrica");
    adicionarPalavra(palavra, "dados", "Juntos constituem informacao");
    adicionarPalavra(palavra, "bubblesort", "Ordenacao das bolhas");
    adicionarPalavra(palavra, "selectionsort", "Ordenacao de selecao");
    adicionarPalavra(palavra, "insertionsort", "Ordenacao de insercao");
    adicionarPalavra(palavra, "javascript", "Linguagem de programacao mais usada");
    adicionarPalavra(palavra, "lua", "Satelite natural e linguagem de programacao");
    adicionarPalavra(palavra, "perl", "Linguagem de perola");
    adicionarPalavra(palavra, "python", "Cobra perigosa e linguagem de programacao");
    adicionarPalavra(palavra, "linux", "Sistema do pinguim");
    adicionarPalavra(palavra, "windows", "Sistema das janelas");
    adicionarPalavra(palavra, "github", "Portifolio dos programadores");
    adicionarPalavra(palavra, "powershell", "Poder da concha");
    adicionarPalavra(palavra, "fortran", "Uma das primeiras linguagens de programacao");
    adicionarPalavra(palavra, "assembly", "Linguagem de maquina");
    adicionarPalavra(palavra, "mysql", "Meu banco de dados");
    adicionarPalavra(palavra, "ciberseguranca", "Mantem seus dados seguros");
    adicionarPalavra(palavra, "django", "Framework de python para web");
    adicionarPalavra(palavra, "haskell", "Linguagem recursiva");
    adicionarPalavra(palavra, "portugol", "Pseudolinguagem introdutoria");
    adicionarPalavra(palavra, "lovelace", "Mulher muito importante para a computacao");
    return encontrarUltimoNo(*palavra);
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

    while (current) {
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
        Palavra* temp = palavra;
        palavra = palavra->next;
        free(temp);
    }
}

void freeCaracteres(Caracteres *c){
    while (c) {
        Caracteres* temp = c;
        c = c -> next;
        free(temp);
    }
}

void adicionaChar(Caracteres** head, char character) {
    Caracteres* newChar =(Caracteres*) malloc(sizeof(Caracteres));

    if (newChar == NULL) {
        perror("Erro na alocacao de caracter.\n");
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
/*---------------------------------------------------------------------------------------*/

// Funções de pontuação
void lideres() {
    FILE *arquivo = fopen("placar.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    Info *dados = NULL;
    int capacidade = 10;

    dados = (Info *)malloc(capacidade * sizeof(Info));
    if (dados == NULL) {
        perror("Erro ao alocar memoria.\n");
        exit(EXIT_FAILURE);
    }

    int loop = 0;
    
    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *nome_inicio = strstr(linha, "Nome: ");
        char *pontuacao_inicio = strstr(linha, "Pontuacao: ");

        if (nome_inicio && pontuacao_inicio) {
            nome_inicio += 6;
            pontuacao_inicio += 11;

            char *virgula_nome = strchr(nome_inicio, ',');
            if (virgula_nome) {
                *virgula_nome = '\0';
            }

            char *virgula = strchr(pontuacao_inicio, ',');
            if (virgula) {
                *virgula = '\0';
            }

            int pontuacao;
            if (sscanf(pontuacao_inicio, "%d", &pontuacao) == 1) {
                strncpy(dados[loop].nome, nome_inicio, sizeof(dados[loop].nome));
                dados[loop].pontuacao = pontuacao;
                loop++;
            }
        }

        if (loop >= capacidade) {
            capacidade *= 2;
            dados = (Info *)realloc(dados, capacidade * sizeof(Info));
            if (dados == NULL) {
                perror("Erro ao realocar memoria.\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(arquivo);

    if (loop == 0) {
        printf("Ainda nao tem jogadores registrados.\n");
    } else {
        insertionSort(dados, loop);
        printf("Ranking de jogadores\n");
        for (int i = 0; i < loop; i++) {
            if (i == 0) {
                printf("\033[1;33m"); // Amarelo brilhante
                printf("1 - Nome: %s, Pontuacao: %d\n", dados[i].nome, dados[i].pontuacao);
                printf("\033[0m"); // Volta para cor padrão
            } else if (i == 1) {
                printf("\033[1;30m"); // Cinza brilhante
                printf("2 - Nome: %s, Pontuacao: %d\n", dados[i].nome, dados[i].pontuacao);
                printf("\033[0m"); // Volta para cor padrão
            } else if (i == 2) {
                printf("\033[1;31m"); // Vermelho brilhante
                printf("3 - Nome: %s, Pontuacao: %d\n", dados[i].nome, dados[i].pontuacao);
                printf("\033[0m"); // Volta para cor padrão
            } else {
                printf("Nome: %s, Pontuacao: %d\n", dados[i].nome, dados[i].pontuacao);
            }
        }
    }
    free(dados);
}
/*---------------------------------------------------------------------------------------*/

// Funções de ordenação
void insertionSort(Info *dados, int n) {
    int i, j;
    Info key;
    for (i = 1; i < n; i++) {
        key = dados[i];
        j = i - 1;

        while (j >= 0 && dados[j].pontuacao < key.pontuacao) {
            dados[j + 1] = dados[j];
            j = j - 1;
        }
        dados[j + 1] = key;
    }
}

void quickSortList(Palavra *head, Palavra *tail) {
    if (head >= tail || head == tail->next) {
        return;
    }
    Palavra *pi = partition(head, tail);

    quickSortList(head, pi);
    quickSortList(pi->next, tail);
}

void swap(Palavra* a, Palavra* b) {
    char temp[TAMANHO_PALAVRA]; 
    strcpy(temp, a->palavra);
    strcpy(a->palavra, b->palavra);
    strcpy(b->palavra, temp);
}

Palavra *partition(Palavra *low, Palavra *high) {
    char pivot[TAMANHO_PALAVRA];
    strcpy(pivot, high->palavra);

    Palavra *i = low;

    for (Palavra *j = low; j != high; j = j->next) {
        if (strcmp(j->palavra, pivot) < 0) {
            swap(i, j);
            i = i->next;
        }
    }
    swap(i, high);
    return i;
}

Palavra* encontrarUltimoNo(Palavra* head) {
    if (head == NULL){
        return NULL;
    }

    while (head->next) {
        head = head->next;
    }
    return head;
}
