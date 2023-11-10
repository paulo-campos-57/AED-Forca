#ifndef __LIBRARY__
#define __LIBRARY__
#define TAMANHO_PALAVRA 100
#define MAX_ERROS 5
#define MAX_TENTATIVAS 26

typedef struct Palavra {
    char palavra[100];
    char dica[150];
    struct Palavra *next;
} Palavra;

typedef struct Caracteres {
    char character;
    struct Caracteres *next;
} Caracteres;

typedef struct Info {
    char nome[50];
    int pontuacao;
} Info;

// Funções auxiliares
void limpaTela();
void pausa();
// Funções de interface
void telaInicial();
void menu();
void printSobre();
void desenhaForca(int erros);
void venceu(char *nome);
void perdeu(char *nome);
// Funções de jogo
void jogoSolo(char *nome);
void jogoDupla(char *j1, char *j2);
int letraJaArriscada(char letra, const char *letrasArriscadas);
void salvarPlacar(const char *nome, int pontuacao);
void adicionarPalavra(Palavra **palavras, char *pl, char *d);
int sizeList(Palavra * Palavra);
Palavra *  geraPalavrasOrdenada(Palavra **palavra);
Palavra *noAleatorio(Palavra *palavra);
void imprimirLista(Palavra *lista);
int adivinharLetra(Caracteres *caracter, char *palavraAdivinhada, char letra);
void freeList(Palavra * palavra);
void adicionaChar(Caracteres** head, char character);
void imprimirP(Caracteres *lista);
void freeCaracteres(Caracteres *c);
// Funções de pontuação
int compara(const void *a, const void *b);
void lideres();
void swap(Palavra* a, Palavra* b);
Palavra *partition(Palavra *low, Palavra *high);
void quickSortList(Palavra *low, Palavra *high);
Palavra* encontrarUltimoNo(Palavra* head);
#endif