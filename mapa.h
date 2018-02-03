#ifndef __MAPA_H__
#define __MAPA_H__

#include "estruturas.h"

#define MAPA_X 50
#define MAPA_Y 100

void preenche_terreno(char mapa[MAPA_X][MAPA_Y], char terreno);
void preenche_objeto(char mapa[MAPA_X][MAPA_Y], char objeto, int qtd, int t, Jogador *jogador, int **pontx, int **ponty);
void mostrarjogador(int x, int y, char mapa[MAPA_X][MAPA_Y], Jogador jogador);
void mostrarstatus(Jogador jogador);
void linhaDivisaoEspaco();
void opcoesmenujogo();
void logogame();

#endif
