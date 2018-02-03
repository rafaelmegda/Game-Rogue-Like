#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "mapa.h"
#include "estruturas.h"
#include "combate.h"

void menuinicial(Jogador *jogador, char *opcoes_menu, FILE *pont_rank){
	int opcao_inicial = 0;
	
	logogame ();
		
	while(opcao_inicial != 1){
		
	   	printf("\n1. Comecar o Jogo\n2. Checar o Ranking\n");
		scanf("%i", &opcao_inicial);
		system("cls");
		
		if(opcao_inicial == 1){
			logogame ();
			printf("\nMaximo de tres caracteres.\n");
			printf("Digite o seu nickname: $");
			scanf("%s", jogador->nome);
			printf("\n\n");
			printf("%s, Seja bem vindo ao EZPZ Fortress Games.\n", jogador->nome);
			printf("\n");
			linhaDivisaoEspaco ();	
			printf("1 - Consultar as Instrucoes do Jogo\n");
			printf("2 - Vamos Comecar a Jogar\n");
			printf("Digite sair! - Para fechar o jogo\n");
			scanf("%s", opcoes_menu);
			system("cls");
		}
		else if(opcao_inicial == 2){
			system("cls");
			
			logogame ();
			printf("\nLista de Ranking:\n\n");
			
			pont_rank = fopen("ranking.txt", "r");
			char c;
		
			do{
				c = getc(pont_rank);			
				printf("%c", c);		
			} while (c != EOF);
			printf("\n");	
		}
	}
}

void imprimetutorial(){
	logogame ();
	printf("\nAqui constam todas as instrucoes do jogo!\n\n");
	printf("Para se mover no jogo, use as teclas abaixo:\n");
	printf("W - Vai para o Norte\nA - Vai para o Oeste\nS - Vai para o Sul\nD - Vai para o Leste\n");
	printf("\nOs terrenos do jogo sao representados pelos simbolos abaixo:\n");
	printf("Y - Florestas\n. - Planicies\n~ - Rios ou Lagos\n^ - Montanhas\n");
	printf("\nOs inimigos sao divididos em 4 tipos diferentes, sendo eles:\n");
	printf("W - Lobos\nB - Ursos\nA - Anacondas\nK - Crocodilos\n");
	printf("\nAlem de outros simbolos como:\n");
	printf("# - Cidade Natal\nC - Personagens nao-jogaveis\n$ - Tesouros\n");
	printf("Sempre que voltar a sua cidade natal voce ira recuperar suas forcas\n");
	printf("\nEscolha a opcao que deseje seguir\n");
	printf("2 - Comecar a jogar\nsair! - Sair do Jogo\n");
}

void atualizastatus(Jogador *jogador, int *contidade){
	
	*contidade += 1;
	
	if(jogador->fome == 0){
		jogador->vidaatual--;
	}
	else if(jogador->fome > 0){
		if(*contidade == 5){
			jogador->fome--;
		}	
	}
	else if(jogador->fome < 0){
		jogador->fome = 0;
		jogador->vidaatual--;
	}
	if(*contidade == 10){
		jogador->idade++;
		*contidade = 0;
	}
	
	if(jogador->idade == 80){
		printf("Voce nao tem mais idade para sair se aventurando para ai.\n");
		printf("Voce terminou com %i moedas\n\n", jogador->moedas);
		jogo();
	}
	
	if(jogador->terrenoatual == '#'){
		jogador->vidaatual += 10;
		if(jogador->vidaatual > 20){
			jogador->vidaatual = 20;
		}
		jogador->fome += 25;
		if(jogador->fome > 50){
			jogador->fome = 50;
		}
		printf("Voce descansou em sua casa durante a noite, logo que amanhaceu comeu um cafe da manha e recuperou suas energias - Fome Recuperada!\n\n");
	}
}

void delimitadorterreno(char mapa[MAPA_X][MAPA_Y], int *x, int *y){
	if(*x < 5){
		printf("O seu caminho ao norte esta bloqueado\n");
		*x = 5;
	}
	else if(*x > 44){
		printf("O seu caminho ao sul esta bloqueado\n");
		*x = 44;
	}
	else if(*y < 5){
		printf("O seu caminho ao oeste esta bloqueado\n");
		*y = 5;
	}
	else if(*y > 94){
		printf("O seu caminho ao leste esta bloqueado\n");
		*y = 94;
	}
}

void jogo(){
	char mapa[MAPA_X][MAPA_Y]; 
	int linha, coluna, r;
	srand(time(NULL));
	int x, y;
	int *pontx = &x, *ponty = &y;
	
	Jogador jogador;
	jogador.vidaatual = 20;
	jogador.fome = 50;
	jogador.idade = 18;
	jogador.danoarma = 2;
	jogador.moedas = 0;
	jogador.nome=(char *) malloc(4*sizeof(char));
	
	FILE *pont_rank;
		
	//variaveis_menu
	int cont_menu;
	char opcoes_menu[20];
	char movimento = '0';
	Mochilas mochila;
	mochila.pocaovida = 0;
	mochila.pocaoveneno = 0;
	
	
	int contidade = 0;

	menuinicial(&jogador, &opcoes_menu, &pont_rank);
		
	while (opcoes_menu != "sair!") {
								
		if(strcmp(opcoes_menu,"sair!") == 0){
			system("cls");
			linhaDivisaoEspaco();
			break;
		}

		else if(strcmp(opcoes_menu,"1") == 0){
			linhaDivisaoEspaco ();
			imprimetutorial();
			scanf("%s", opcoes_menu);
		}
	
		else if(strcmp(opcoes_menu,"2") == 0){
			linhaDivisaoEspaco ();
			
			printf("\n");
			// Preenchimento de PLanicies no Mapa Todo
			for (linha = 0; linha < MAPA_X; linha++) {
				for (coluna = 0; coluna < MAPA_Y; coluna++) {
					mapa[linha][coluna] = ' ';
				}
			}
			for (linha = 5; linha < MAPA_X - 5; linha++) {
				for (coluna = 5; coluna < MAPA_Y - 5; coluna++) {
					mapa[linha][coluna] = '.';
				}
			}
			char terreno, objeto, qtd;
			int t;
			for (t = 0; t < 3; t++) {
				if (t == 0) {
					terreno = 'Y';
				}
				else if (t == 1) {
					terreno = '^';
				}
				else if (t == 2) {
					terreno = '~';
				}
				int abc;
				for (abc = 0; abc < 8; abc++) {
					preenche_terreno(mapa, terreno);
				}
			}
			for (t = 0; t < 7; t++) {
				char objeto;
				if (t == 6) {
					objeto = '#';
					qtd = 1;
				}
				else if (t == 1) {
					objeto = 'C';
					qtd = (rand() % 6);
				}
				else if (t == 2) {
					objeto = 'W';
					qtd = (rand() % 14);
				}
				else if (t == 3) {
					objeto = 'B';
					qtd = (rand() % 6);
				}
				else if (t == 4) {
					objeto = 'K';
					qtd = (rand() % 8);
				}
				else if (t == 5) {
					objeto = 'A';
					qtd = (rand() % 10);
				}
				else if (t == 0) {
					objeto = '$';
					qtd = (rand() % 4);
				}
				int ab;
				for (ab = 0; ab < qtd; ab++) {
					preenche_objeto(mapa, objeto, qtd, t, &jogador, &pontx, &ponty);
				}
			}
			
			system("cls");
			logogame ();
			mostrarjogador(x, y, mapa, jogador);			
			printf("3 - Movimentar Jogador\n4 - Listar Itens da Mochila\nsair! - Sair do Jogo\n");
			scanf("%s", opcoes_menu);
		}	
		else if(strcmp(opcoes_menu,"3") == 0){
			movimento = '0';
			while(movimento != '!'){
				
				printf("Seu movimento:\n");
				movimento = getch();
				system("cls");
				if(movimento == 'w' || movimento == 'W'){
					mapa[x][y] = jogador.terrenoatual;
					x = x - 1;
					delimitadorterreno(mapa, &x, &y);
					jogador.terrenoatual = mapa[x][y];
					mapa[x][y] = '@';
					logogame ();
					atualizastatus(&jogador, &contidade);
					mostrarjogador(x, y, mapa, jogador);
				}
				else if(movimento == 's' || movimento == 'S'){
					mapa[x][y] = jogador.terrenoatual;
					x = x + 1;
					delimitadorterreno(mapa, &x, &y);
					jogador.terrenoatual = mapa[x][y];
					mapa[x][y] = '@';
					logogame ();
					atualizastatus(&jogador, &contidade);
					mostrarjogador(x, y, mapa, jogador);
				}
				else if(movimento == 'a' || movimento == 'A'){
					mapa[x][y] = jogador.terrenoatual;
					y = y - 1;
					delimitadorterreno(mapa, &x, &y);
					jogador.terrenoatual = mapa[x][y];
					mapa[x][y] = '@';
					logogame ();
					atualizastatus(&jogador, &contidade);
					mostrarjogador(x, y, mapa, jogador);
				}	
				else if(movimento == 'd' || movimento == 'D'){
					mapa[x][y] = jogador.terrenoatual;
					y = y + 1;
					delimitadorterreno(mapa, &x, &y);
					jogador.terrenoatual = mapa[x][y];
					mapa[x][y] = '@';	
					logogame ();
					atualizastatus(&jogador, &contidade);
					mostrarjogador(x, y, mapa, jogador);
				}
				else if(movimento == '!'){
					logogame ();
					mostrarjogador(x, y, mapa, jogador);			
					puts("3 - Movimentar Jogador\n4 - Mochila\nsair! - Sair do Jogo");
					scanf("%s", opcoes_menu);
					break;
				}
				controledevida(&jogador, &opcoes_menu, &pont_rank);
				combate(&jogador, &opcoes_menu, &mochila, &pont_rank);
			}
		}
		else if(strcmp(opcoes_menu,"4") == 0){
			int opcao_item = 0;
			while(opcao_item != 3){
				system("cls");
				printf("1. Pocoes de Vida: %i\n2. Pocoes de veneno: %i\n3. Voltar ao mapa.\n", mochila.pocaovida, mochila.pocaoveneno);
				scanf("%i", &opcao_item);
				if(opcao_item == 1){
					if(mochila.pocaovida < 1){
						printf("Voce nao tem pocao de vida.\n");
					}
					else{
						printf("Voce gastou uma pocao de vida.\n");
						printf("Voce recuperou 25 de Vida.\n");
						mochila.pocaovida -= 1;
						jogador.vidaatual += 10;
						if(jogador.vidaatual > 20){
							jogador.vidaatual = 20;
						}			
					}
				}	
				else if(opcao_item == 2){
					printf("Voce não pode usar essa pocao fora de batalha.\n");
				}
				else if(opcao_item == 3){
					logogame ();
					mostrarjogador(x, y, mapa, jogador);			
					printf("3 - Movimentar Jogador\n4 - Listar Itens da Mochila\nsair! - Sair do Jogo\n");
					scanf("%s", opcoes_menu);
				}		
			}
		}
	}
	free(jogador.nome);
}

int main(int argc, char **argv) {

	jogo();

}
