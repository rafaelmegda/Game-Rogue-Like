#include "mapa.h"

void preenche_terreno(char mapa[MAPA_X][MAPA_Y], char terreno) {

	//Gerar valor aleatório do eixo X e Y para terrenos
	int x, y;
	x = 5 + (rand() % 35);//limite linhas
	y = 10 + (rand() % 70);//limite colunas
	int i, j;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++) {
			mapa[x + i][y + j] = terreno;
		}
	}
}

void preenche_objeto(char mapa[MAPA_X][MAPA_Y], char objeto, int qtd, int t, Jogador *jogador, int **pontx, int **ponty) {

	//Gerar valor aleatório do eixo X e Y para o objeto
	int x, y, i;
	for (i = 0; i < qtd; i++) {
		x = 5 + (rand() % (35));//limite linhas
		y = 10 + (rand() % (70));//limite colunas
		mapa[x][y] = objeto;//Colocar os objetos
		if (t == 6) {
			jogador->terrenoatual = mapa[x][y + 1];
			mapa[x][y + 1] = '@'; //Colocar a Cidade e ao lado colocar o personagem
			**pontx = x;
			**ponty = y + 1;
		}
	}
}

void mostrarjogador(int x, int y, char mapa[MAPA_X][MAPA_Y], Jogador jogador) {//Mostra ao redor do jogador
	int cont1, cont2;
	for (cont1 = x - 5; cont1 < x + 6; cont1++) {
		for (cont2 = y - 10; cont2 < y + 11; cont2++) {
			printf("%c", mapa[cont1][cont2]);
		}
		printf("\n");
	}
	mostrarstatus(jogador);
	opcoesmenujogo();
}

void mostrarstatus(Jogador jogador){
	int coluna;
	linhaDivisaoEspaco();
	printf("%s - HP: %i/20 Fome: %i/50 Idade: %i Moedas: %i\n", jogador.nome, jogador.vidaatual, jogador.fome, jogador.idade, jogador.moedas);
	linhaDivisaoEspaco();
}

void opcoesmenujogo(){
	printf("! para abrir sua mochila\n");
}

void linhaDivisaoEspaco () {
	int coluna;
	for (coluna = 0; coluna < 50; coluna++) {
		printf("-");
	}
	printf("\n");
}

void logogame(){
                                                                                                                 
printf("\t _______  ________  .______    ________    \n");
printf("\t|   ____||       /  |   _  \  |       /   \n");
printf("\t|  |__   `---/  /   |  |_)  | `---/  /    \n");
printf("\t|   __|     /  /    |   ___/     /  /     \n");
printf("\t|  |____   /  /----.|  |        /  /----. \n");
printf("\t|_______| /________|| _|       /________| \n");
printf("\n                  FORTRESS GAMES              \n");
	
}               
                       

