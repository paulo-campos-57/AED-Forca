#ifndef __LIBRARY__
#define __LIBRARY__
#define TAMANHO_PALAVRA 20
#define MAX_ERROS 5
typedef struct Palavra {
    char palavra[100];
    char dica[150];
    struct Palavra *next;
} Palavra;

void telaInicial();
void limpaTela();
void pausa();
void menu();
void jogoSolo(char *nome);
void jogoDupla(char *j1, char *j2, Palavra **listaPalavras);
void printSobre();
void desenhaForca(int erros);
void adicionarPalavra(Palavra **palavras, char *pl, char *d);
void venceu();
void perdeu();
int sizeList(Palavra * Palavra);
void geraPalavrasOrdenada(Palavra **palavra);
Palavra *noAleatorio(Palavra *palavra);
void insertionSortList(Palavra **head);
void imprimirLista(Palavra *lista);
int adivinharLetra(Palavra *palavraSecreta, char *palavraAdivinhada, char letra);
#endif