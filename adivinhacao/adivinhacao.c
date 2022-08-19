#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
printf("\n\n");    
printf("/\\/\\/\\/\\/\\/\\/\\/\\                           \n");
printf(":              :                                   \n");
printf("|              |                                   \n");
printf("|              |                                   \n");
printf("|              |                                   \n");
printf("|            __`,                                  \n");
printf("|           /   \\                                 \n");
printf("|           \\__*/__      Olá, bem vindo(a) ao nosso\n");
printf(":               ___)        jogo de adivinhação!   \n");
printf(" \\              \\                                 \n");
printf("  :      _______/                                  \n");
printf("  |         /                                      \n");
printf("  ;        :                                       \n");
printf(" ;         ;                                       \n");
printf("  `""*--*""                                        \n");
printf("\n\n");

    
    int segundos = time(0);
    srand(segundos);
    
    int numerogrande = rand();
        
    int numerosecreto = numerogrande % 100;
    int chute;
    int tentativas = 1;
    double pontos= 1000;
    
    int acertou = 0;
    
    int nivel;
    printf("Em qual nível você quer jogar?\n");
    printf("Fácil(1)\t Médio(2)\tDifícil(3)\n");
    printf("Escolha: ");
    scanf("%d", &nivel);
    
    int numerodetentativas;
    switch(nivel){
        case 1:
            numerodetentativas = 20;
            break;
        case 2:
            numerodetentativas = 15;
            break;
        default:
            numerodetentativas = 6;
            break;
    }
    
    for(int i = 0; i <= numerodetentativas; i++){
        
        printf("Tentativa %d\n", tentativas);
        printf("Qual seu chute? \n");
        
        scanf("%d", &chute);
        printf("Seu chute foi %d\n", chute);
        
        if(chute < 0){
            printf("Você não pode chutar números negativos!\n");
            continue;
        }
        
        acertou = (chute == numerosecreto);
        int maior = chute > numerosecreto;
        
        if(acertou){
            break;
        }
        
        else if(maior){
            printf("Seu chute foi maior que o número secreto\n\n");
        }
        
        else{
            printf("Seu chute foi menor que o número secreto\n\n");
        }
        
        tentativas++;
        
        double pontosperdidos = abs(chute - numerosecreto) / 2.0;
        pontos = pontos - pontosperdidos;
    }
    
    printf("Fim de jogo!\n");
    
    if (acertou){
        printf("Você acertou!\n");
        printf("Você acertou em %d tentativas!\n", tentativas);
        printf("Total de pontos: %.1f\n", pontos);
    }
    else{
        printf("Você perdeu\nTente de novo!");
    }
}