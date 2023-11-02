#ifndef __LIBRARY__
#define __LIBRARY__

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
void desenhaForca();
void adicionarPalavra(Palavra **palavras, char *pl, char *d);
void trofeu();
void caveira();

#endif