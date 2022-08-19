#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//header file
#include "forca.h"

//váriaveis globais
char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura() {
    printf("*********************************\n");
    printf("**        Jogo de Forca        **\n");
    printf("*********************************\n\n");
}

void chuta() {
    char chute;
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

void desenhaforca() { 

    int erros = chuteserrados();

    //IF's ternários, basicamente true or false
    printf("  ________       \n");
    printf(" |/       |      \n");
    printf(" |       %c%c%c       \n", (erros >= 1 ? '(' : ' ') , (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')': ' '));
    printf(" |       %c%c%c       \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >=3 ? '/' : ' '));
    printf(" |        %c          \n", (erros >= 2 ? '|' : ' '));
    printf(" |       %c %c        \n", (erros >= 4 ? '/' : ' '), (erros >=4 ? '\\' : ' '));
    printf(" |                    \n");
    printf("_|___                 \n");
    printf("\n\n");


    for(int i = 0; i < strlen(palavrasecreta); i++){

        int achou = jachutou(palavrasecreta[i]);

        if(achou){
        printf("%c ", palavrasecreta[i]);
        }
        else{
        printf("_ ");
        }
    }
    printf("\n");
}

void adicionapalavra() {
    
    char quer;

    printf("Você deseja adicionar uma nova palavra no jogo? (S/N)");
    scanf(" %c", &quer);

    if(quer == 'S'){

        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra?");
        scanf("%s", novapalavra);

        FILE* f;

        f = fopen("palavras.md", "r+");
        if(f == 0){
            printf("Desculpe, banco de dados não disponível\n\n");
            exit(1);
        }

        int qtd;
        
        //Conta a quantidade e adiciona +1
        fscanf(f, "%d", &qtd);
        qtd++;

        //Vai no começo do arquivo e muda o número
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        //Vai no final do arquivo e escreve a palavra
        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);

        fclose(f);
    }
}

void escolhepalavra() {
    FILE* f;
    //Abre o arquivo
    f = fopen("palavras.md", "r");
    if(f == 0){
        printf("Desculpe, banco de dados não disponível\n\n");
        exit(1);
    }
    //Analisa o tamanho do arquivo
    int qtddepalavras;
    fscanf(f, "%d", &qtddepalavras);

    //Gera um número aleatório
    srand(time(0));
    int randomico = rand() % qtddepalavras;

    //Escolhe uma palavra a partir de uma linha escolhida sorteada
    for(int i = 0; i < randomico; i++) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

int acertou() {
    for(int i = 0; i < strlen(palavrasecreta); i++){
        if(!jachutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

int chuteserrados() {
    int erros = 0;

    for(int i = 0; i < chutesdados; i++) {
        int existe = 0;

        for(int j = 0; j < strlen(palavrasecreta); j++) {
            if(chutes[i] == palavrasecreta[j]){

                existe = 1;
                break;
            }
        }
        if(!existe) erros++;
    }
    return erros;
}

int enforcou() {
   
    return chuteserrados() >= 5;
}

int jachutou(char letra) {
    int achou = 0;

    for(int j = 0; j < chutesdados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }

    return achou;
}

int main(){

    escolhepalavra();
    abertura();

    do{

        desenhaforca();
        chuta();
        

    }while(!acertou() && !enforcou());

    if(acertou()){
        printf("Parabéns, você ganhou!\n");
        printf("                      ___________                        \n");
        printf("                 .---'::'        `---.                   \n");
        printf("                (::::::'              )                  \n");
        printf("                |`-----._______.-----'|                  \n");
        printf("                |              :::::::|                  \n");
        printf("               .|               ::::::!-.                \n");
        printf("               \\|               :::::/|/                \n");
        printf("                |               ::::::|                  \n");
        printf("                | Troféu de Vencedor::|                  \n");
        printf("                |      da Forca  :::::|                  \n");
        printf("                |               ::::::|                  \n");
        printf("                |              .::::::|                  \n");
        printf("                J              :::::::F                  \n");
        printf("                 \\            :::::::/                  \n");
        printf("                  `.        .:::::::'                    \n");
        printf("                    `-._  .::::::-'                      \n");
        printf("                        |  ''||''                        \n");
        printf("                        |  :::|                          \n");
        printf("                        F   ::J                          \n");
        printf("                       /     ::\\                        \n");                                 
        printf("                  __.-'      :::`-.__                    \n");
        printf("                 (_           ::::::_)                   \n");
        printf("                  `'''---------''''                      \n\n");

    adicionapalavra();

    }
    else if(enforcou()){
        printf("Infelizmente você perdeu!\n");
        printf("                            uuuuuuu                         \n");
        printf("                       uu$$$$$$$$$$$uu                      \n");
        printf("                     uu$$$$$$$$$$$$$$$$$uu                  \n");
        printf("                    u$$$$$$$$$$$$$$$$$$$$$u                 \n");
        printf("                   u$$$$$$$$$$$$$$$$$$$$$$$u                \n");
        printf("                   u$$$$$$$$$$$$$$$$$$$$$$$$$               \n");
        printf("                  u$$$$$$$$$$$$$$$$$$$$$$$$$u               \n");
        printf("                   u$$$$$$'   '$$$'   '$$$$$$u              \n");
        printf("                   '$$$$'      u$u       $$$$'              \n");
        printf("                    $$$u       u$u       u$$$               \n");
        printf("                    $$$u      u$$$u      u$$$               \n");
        printf("                    '$$$$uu$$$    $$$uu$$$$'                \n");
        printf("                     '$$$$$$$'   '$$$$$$$'                  \n");
        printf("                        u$$$$$$$u$$$$$$$u                   \n");
        printf("                         u$'$'$'$'$'$'$u                    \n");
        printf("              uuu        $$u$ $ $ $ $u$$       uuu          \n");
        printf("             u$$$$        $$$$$u$u$u$$$       u$$$$         \n");
        printf("            $$$$$$uu      '$$$$$$$$$'     uu$$$$$$          \n");
        printf("            u$$$$$$$$$$$uu    '''''    uuuu$$$$$$$$$$       \n");
        printf("            $$$$'''$$$$$$$$$$uuu   uu$$$$$$$$$'''$$$'       \n");
        printf("            '''      ''$$$$$$$$$$$uu ''$'''                 \n");
        printf("                        uuuu ''$$$$$$$$$$uuu                \n");
        printf("            u$$$uuu$$$$$$$$$uu '' $$$$$$$$$$$uuu$$$         \n");
        printf("            $$$$$$$$$$''''           '' $$$$$$$$$$$'        \n");
        printf("              '$$$$$'                      ''$$$$''         \n");
        printf("                $$$'                         $$$$'          \n\n");

    }
}