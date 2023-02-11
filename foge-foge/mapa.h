#ifndef _MAPA_H_
#define _MAPA_H_

#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'

struct mapa {
    char** matriz;
    int linhas;
    int colunas;
}typedef MAPA;

struct posicao {
    int x;
    int y;
}typedef POSICAO;

void liberaMapa(MAPA* m);
void leMapa(MAPA* m);
void alocaMapa(MAPA* m);
int encontraMapa(MAPA* m, POSICAO* p, char c);
int mapaValido(MAPA* m, int x, int y);
int posicaoVazia(MAPA* m, int x, int y);
void andaNoMapa(MAPA* m, int xorigem, int yorigem,
                int xdestino, int ydestino);
void copiaMapa(MAPA* destino, MAPA* origem);
int podeAndar(MAPA* m, char personagem, int x, int y);
int eUmaParede(MAPA* m, int x, int y);
int eUmPersonagem(MAPA* m, char personagem, int x, int y);
#endif