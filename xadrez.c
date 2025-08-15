#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#define L 8
#define C 8
#define NOME 50
#define MAX_PARTIDAS 100

typedef struct{
    char vencedor[NOME];
    char jogador1[NOME];
    char jogador2[NOME];
}Partida;

void delay(int millisegundos){
    Sleep(millisegundos);
}

void vitoria(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for(int i=0;i<10;i++){
        system("cls");
        SetConsoleTextAttribute(hConsole, 14);
        printf("\n\n\n       *       *       *\n");
        printf("     *   *   *   *   *\n");
        printf("         VITORIA       \n");
        printf("     *   *   *   *   *\n");
        printf("       *       *       *\n");
        delay(500);
        system("cls");
        delay(400);
    }
    SetConsoleTextAttribute(hConsole, 15);
}

void creditos(){
    printf("\n=========================================\n");
    printf("  Obrigado por jogar!\n");
    printf("  Desenvolvido com muito love e odio\n");
    printf("  Por Maria Eduarda Linda Maravilhosa\n");
    printf("=========================================\n");
}

void menu(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    SetConsoleTextAttribute(hConsole, 11);
    printf("\n===============================\n");
    printf("||        CHESS GAME         ||\n");
    printf("===============================\n");
    SetConsoleTextAttribute(hConsole, 9);
    printf("[1] "); 
    SetConsoleTextAttribute(hConsole, 15); 
    printf("JOGAR\n");
    SetConsoleTextAttribute(hConsole, 10);
    printf("[2] "); 
    SetConsoleTextAttribute(hConsole, 15); 
    printf("COMO JOGAR\n");
    SetConsoleTextAttribute(hConsole, 14);
    printf("[3] "); 
    SetConsoleTextAttribute(hConsole, 15); 
    printf("CONSULTAR PARTIDAS\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("[4] "); 
    SetConsoleTextAttribute(hConsole, 15); 
    printf("COMO MOVIMENTAM AS PECAS\n");
    SetConsoleTextAttribute(hConsole, 11);
    printf("[0] ");
    SetConsoleTextAttribute(hConsole, 15);
    printf("SAIR\n");
    printf("Escolha sua opcao: ");
    printf("\n===============================\n");
    SetConsoleTextAttribute(hConsole, 15);
}

void prim_tab(char t[L][C]){
    char modelo[L][C] = {
        {'T','C','B','D','R','B','C','T'},
        {'P','P','P','P','P','P','P','P'},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' '},
        {'p','p','p','p','p','p','p','p'},
        {'t','c','b','d','r','b','c','t'}
    };

    int i, j;
    for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            t[i][j] = modelo[i][j];
        }
    }
}

void printar_tab(char t[L][C]){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int linha, coluna, linha_aux, coluna_aux;

    printf("   ");
    for(coluna=0;coluna<C;coluna++){
        printf("    %c   ", 'A' + coluna); 
    }
    printf("\n");

    for(linha=0;linha<L;linha++){
        for(linha_aux=0;linha_aux<4;linha_aux++){
            if(linha_aux==1){
                printf("%d ", linha + 1);
            }else{
                printf("  ");
            }

            for(coluna=0;coluna<C;coluna++){
                int cor;
                if((linha+coluna)%2==0){
                    cor = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
                }else{
                    cor = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
                }

                SetConsoleTextAttribute(hConsole, cor);

                for(coluna_aux=0;coluna_aux<8;coluna_aux++){
                    if(linha_aux==1 && coluna_aux==4){
                        printf("%c",t[linha][coluna]);
                    }else{
                        printf(" ");
                    }
                }
                SetConsoleTextAttribute(hConsole, 15); 
            }
            printf("\n");
        }
    }
}
int its_over_babe(char t[L][C]){
    int tem_rei_maiusculo = 0;
    int tem_rei_minusculo = 0;

    int i, j;
    for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            if(t[i][j]=='R'){
                tem_rei_maiusculo = 1;
            }
            if(t[i][j]=='r'){
                tem_rei_minusculo = 1;
            }
        }
    }

    return !(tem_rei_maiusculo && tem_rei_minusculo);
}

void como_movimentam(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    printf("=> Peao:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("    -Se move para frente, duas casas no primeiro movimento e no restante somente uma casa.\n    -Captura na diagonal.\n");
    SetConsoleTextAttribute(hConsole, 5);
    printf("=> Torre:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("    -Se move pela lateral quantas casas quiser.\n    -Captura pela lateral.\n");
    SetConsoleTextAttribute(hConsole, 6);
    printf("=> Cavalo:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("    -Pode se mover:\n");
    printf("      .Duas casas para frente e uma para o lado;\n");
    printf("      .Duas casas para o lado e uma para frente;\n");
    printf("      .Duas casas para tras e uma para o lado;\n");
    printf("      .Duas casas para o lado e uma para tras;\n");
    printf("      .Eh a unica peca que pode pular outras pecas;\n");
    printf("      .Captura na ultima casa que parar.\n");
    SetConsoleTextAttribute(hConsole, 13);
    printf("=> Bispo:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("    -Se move pelas diagonais quantas casas quiser, porem nao pode pular pecas.\n    -Captura pela diagonal.\n");
    SetConsoleTextAttribute(hConsole, 11);
    printf("=> Dama:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("    -Se move para todos os lados que quiser e quantas casas preferir, porem nao pula pecas.\n    -Captura por qualquer lado.\n");
    SetConsoleTextAttribute(hConsole, 9);
    printf("=> Rei:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("    -Se move quase igual a 'DAMA', a diferenca eh que so pode se mover uma casa de cada vez.\n   -Captura por qualquer lado.\n");
}
int jogar(char t[L][C], Partida partidas[], int qtd_partidas, int pontuacoes[2]){
    char jogador1[NOME], jogador2[NOME];
    int turno = 0;

    printf("Digite o nome do jogador das pecas MAIUSCULAS (BRANCAS/DE CIMA): ");
    fgets(jogador1, NOME, stdin);
    jogador1[strlen(jogador1)-1] = '\0';

    printf("Digite o nome do jogador das pecas minusculas (pretas/de baixo): ");
    fgets(jogador2, NOME, stdin);
    jogador2[strlen(jogador2)-1] = '\0';

    prim_tab(t);

    while(!its_over_babe(t)){
        char origem[3], destino[3];
        int origem_linha, origem_coluna, destino_linha, destino_coluna;

        system("cls");
        char nome_turno[NOME];
        char tipo_pecas[20];

        if(turno % 2 == 0){
            strcpy(nome_turno, jogador1);
            strcpy(tipo_pecas, "MAIUSCULAS");
        }else{
            strcpy(nome_turno, jogador2);
            strcpy(tipo_pecas, "minusculas");
        }       

        printf("Turno de %s (%s)\n", nome_turno, tipo_pecas);

        printar_tab(t);

        printf("Digite o movimento (exemplo: e2 e4): ");
        scanf("%s %s", origem, destino);
        getchar();

        origem_linha = origem[1] - '1'; origem_coluna = origem[0] - 'a';
        destino_linha = destino[1] - '1'; destino_coluna = destino[0] - 'a';

        if(origem_linha >= 0 && origem_linha < 8 && origem_coluna >= 0 && origem_coluna < 8 && destino_linha >= 0 && destino_linha < 8 && destino_coluna >= 0 && destino_coluna < 8){
            char peca = t[origem_linha][origem_coluna];
            if((turno % 2 == 0 && isupper(peca)) || (turno % 2 == 1 && islower(peca))){
                t[destino_linha][destino_coluna] = peca;
                t[origem_linha][origem_coluna] = ' ';
                turno++;
            }else{
                printf("Movimento invalido! Aperte ENTER para tentar novamente.\n");
                getchar();
            }
        }else{
            printf("Posicao invalida! Aperte ENTER para tentar novamente.\n");
            getchar();
        }
    }

    system("cls");
    printar_tab(t);
    printf("\n=== FIM DE JOGO ===\n");

    char vencedor[NOME];
    int achou_rei = 0;

    for(int i=0;i<L;i++){
        for(int j=0;j<C;j++){
            if(t[i][j]=='R'){
                achou_rei = 1;
            }
        }
    }

    if(achou_rei){
        strcpy(vencedor, jogador1);
        pontuacoes[0]++;
    }else{
        strcpy(vencedor, jogador2);
        pontuacoes[1]++;
    }

    printf("Vencedor: %s\n", vencedor);
    printf("Pontuacao atual:\n%s: %d vitorias\n%s: %d vitorias\n", jogador1, pontuacoes[0], jogador2, pontuacoes[1]);

    if(qtd_partidas < MAX_PARTIDAS){
        strcpy(partidas[qtd_partidas].jogador1, jogador1);
        strcpy(partidas[qtd_partidas].jogador2, jogador2);
        strcpy(partidas[qtd_partidas].vencedor, vencedor);
        qtd_partidas++;
    }
    
    system("pause");
    vitoria();

    creditos();
    return qtd_partidas;
}

void como_jogar(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\n=== COMO JOGAR ===\n");
    printf("1 => Regras do Jogo:\n");
    SetConsoleTextAttribute(hConsole, 9);
    printf("OBJETIVO DO JOGO:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("  -O objetivo eh capturar o rei adversario, o que se chama de xeque-mate. Quando o rei esta em posicao de ser capturado (em xeque) e nao ha como se mover para uma casa segura, a partida termina.\n");
    SetConsoleTextAttribute(hConsole, 10);
    printf("FIM DE PARTIDA:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("   -O termino da partida desse jogo se da, quando algum rei eh capturado, seja o BRANCO seja o 'preto'.\n");
    SetConsoleTextAttribute(hConsole, 11);
    printf("O QUE EH PROIBIDO:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("   -Mover uma peca de maneira ilegal.\n   -Captura de uma peca que nao eh adversaria.\n   -Pular pecas (exceto o cavalo).\n   -Jogar duas vezes seguidas.\n");
    SetConsoleTextAttribute(hConsole, 12);
    printf("MOVIMENTOS ESPECIAIS:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("Roque:   -Movimenta o rei e uma torre ao mesmo tempo.\n   -O rei anda 2 casas para o lado da torre, e a torre salta por cima dele.\n");
    printf("En passant (passar batido):\n   -Um peao pode capturar um peao inimigo que acabou de andar 2 casas e parou ao lado dele.\n   -So pode capturar na jogada imediatamente seguinte.\n");
    printf("Promocao do peao:\n   -Quando um peao chega ao outro lado do tabuleiro, ele vira dama, torre, bispo ou cavalo (escolha do jogador).\n   -A promocao mais comum eh para dama.\n");
}

void mostrar_partidas(Partida partidas[], int qtd){
    if(qtd==0){
        printf("Nenhuma partida registrada.\n");
    }else{
        for(int i=0;i<qtd;i++){
            printf("Partida %d:\n Jogador 1: %s\n Jogador 2: %s\n Vencedor : %s\n", i+1, partidas[i].jogador1, partidas[i].jogador2, partidas[i].vencedor);
        }
    }
}

int main(){
    char tabuleiro[L][C];
    Partida partidas[MAX_PARTIDAS];
    int qtd_partidas = 0;
    int pontuacoes[2] = {0, 0};
    int to_on = 1;
    int opcao_menu = 0;

    while(to_on==1){
        menu();
        scanf("%d", &opcao_menu);
        getchar();

        switch(opcao_menu){
            case 1:
                qtd_partidas = jogar(tabuleiro, partidas, qtd_partidas, pontuacoes);
                break;
                system("pause");
            case 2: 
                como_jogar();
                system("pause");
                break;
            case 3:
                mostrar_partidas(partidas, qtd_partidas);
                system("pause");
                break;
            case 4:
                como_movimentam();
                system("pause");
                break;
            case 0:
                to_on = 0;
                creditos();
                break;
            default:
                printf("Opcao invalida.\n");
                system("pause");
        }
    }

    printf("Jogo encerrado!\n");
    return 0;
}
