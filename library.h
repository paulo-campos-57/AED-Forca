#ifndef __LIBRARY__
#define __LIBRARY__
#define TAMANHO_PALAVRA 100
#define MAX_ERROS 5

typedef struct Palavra {
    char palavra[100];
    char dica[150];
    struct Palavra *next;
} Palavra;

typedef struct Caracteres {
    char character;
    struct Caracteres *next;
} Caracteres;

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
void salvarPlacar(const char *nome, int pontuacao);
void adicionarPalavra(Palavra **palavras, char *pl, char *d);
int sizeList(Palavra * Palavra);
void geraPalavrasOrdenada(Palavra **palavra);
Palavra *noAleatorio(Palavra *palavra);
void insertionSortList(Palavra **head);
void imprimirLista(Palavra *lista);
int adivinharLetra(Caracteres *caracter, char *palavraAdivinhada, char letra);
void freeList(Palavra * palavra);
void adicionaChar(Caracteres** head, char character);
void imprimirP(Caracteres *lista);
void freeCaracteres(Caracteres *c);
#endif