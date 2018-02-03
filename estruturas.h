#ifndef __ESTRUTURAS_H__
#define __ESTRUTURAS_H__

typedef struct _Jogador {
	int vidaatual;
	int fome;
	int idade;
	int danoarma;
	int moedas;
	char terrenoatual;
	char *nome;
} Jogador;

typedef struct _Inimigos {
	int vida;
	int dano;
} Inimigos;

typedef struct _Mochilas {
	int pocaovida;
	int pocaoveneno;
} Mochilas;

#endif
