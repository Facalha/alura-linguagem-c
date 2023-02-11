#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

MAPA m;
POSICAO heroi;
int tempilula = 0;

int praOndeFantasmaVai(int xatual, int yatual, 
    int* xdestino, int* ydestino) {
    
    int opcoes[4][2] = {
        {xatual, yatual +1},
        {xatual +1, yatual},
        {xatual +1, yatual-1},
        {xatual -1, yatual}
    };

    srand(time(0));
    for (int i = 0; i < 10; i++) {
        int posicao = rand() % 4;

        if(podeAndar(&m, FANTASMA, opcoes[posicao][0], opcoes[posicao][1])) {
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];

            return 1;
        }
    }
    return 0;
}

void fantasmas() {
    MAPA copia;

    copiaMapa(&copia, &m);

    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            
            if(copia.matriz[i][j] == FANTASMA) {

                int xdestino;
                int ydestino;

                int encontrou = praOndeFantasmaVai(i, j, &xdestino, &ydestino);

                if(encontrou) {
                    andaNoMapa(&m, i, j, xdestino, ydestino);
                }
                }
            }
        }
    liberaMapa(&copia);
}

int direcaoValida(char direcao) {
    return direcao == ESQUERDA ||
        direcao == CIMA ||
        direcao == BAIXO ||
        direcao == DIREITA;
}

void move(char direcao) {

    if(!direcaoValida(direcao)) 
        return;

    int proximoX = heroi.x;
    int proximoY = heroi.y;

    switch(direcao) {
        case ESQUERDA:
            proximoY--;
            break;
        case CIMA:
            proximoX--;
            break;
        case BAIXO:
            proximoX++;
            break;
        case DIREITA:
            proximoY++;
            break;    
    }

    if(!podeAndar(&m, HEROI, proximoX, proximoY))
        return;

    if(eUmPersonagem(&m, PILULA, proximoX, proximoY)) {
        tempilula = 1;
    }

    andaNoMapa(&m, heroi.x, heroi.y, proximoX, proximoY);
    heroi.x = proximoX;
    heroi.y = proximoY;
}

int jogoAcabou() {
    POSICAO pos;
    int fogeFogeNoMapa = encontraMapa(&m, &pos, HEROI);
    
    return !fogeFogeNoMapa;
}

void explodePilula() {

if(!tempilula) return;

    explodePilula2(heroi.x, heroi.y, 0, 1, 3);
    explodePilula2(heroi.x, heroi.y, 0, -1, 3);
    explodePilula2(heroi.x, heroi.y, 1, 0, 3);
    explodePilula2(heroi.x, heroi.y, -1, 0, 3);

    tempilula = 0;
}

    //RECURSIVIDADE
void explodePilula2(int x, int y, int somax, int somay, int qtd) { 
    
    if(qtd == 0) return;

    int novox = x + somax;
    int novoy = y + somay;

    if(!mapaValido(&m, novox, novoy)) return;
    if(eUmaParede(&m, novox, novoy)) return;

    m.matriz[novox][novoy] = VAZIO;
    explodePilula2(novox, novoy, somax, somay, qtd-1);
}

int main() {

    leMapa(&m);

    do {
        printf("Tem pilula: %s\n", (tempilula ? "SIM" : "NAO")); 
        imprimeMapa(&m);
        encontraMapa(&m, &heroi, HEROI);

        char comando;
        scanf(" %c", &comando);
        move(comando);
        if(comando == BOMBA) explodePilula();

        fantasmas();
        system("clear");

    } while (!jogoAcabou());
    
    liberaMapa(&m);
}