#ifndef __COMBATE_H__
#define __COMBATE_H__

#include "estruturas.h"
#include "mapa.h"
#include <stdio.h>

void combate(Jogador *jogador, char *opcoes_menu, Mochilas *mochila, FILE *pont_rank);
void controledevida(Jogador *jogador, char *opcoes_menu, FILE *pont_rank);


#endif
