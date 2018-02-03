#include "combate.h"
#include <time.h>


void controledevida(Jogador *jogador, char *opcoes_menu, FILE *pont_rank){
	if(jogador->vidaatual <= 0){
		system("cls");
		printf("Voce esta morto.\n");
		
		pont_rank = fopen("ranking.txt", "a");
		printf("%s\n", jogador->nome);
		fprintf(pont_rank, "Jogador:%s - Total de Moedas:%i\n", jogador->nome, jogador->moedas);
		
		fclose(pont_rank);

		jogo();
	}
}

//continuar implementação
void combate(Jogador *jogador, char *opcoes_menu, Mochilas *mochila, FILE *pont_rank){
	char opCombate;
	if(jogador->terrenoatual == 'W' || jogador->terrenoatual == 'B' || jogador->terrenoatual == 'A' || jogador->terrenoatual == 'K'){
		if(jogador->terrenoatual == 'W'){
			system("cls");
			printf("Deseja entrar em combate com um Lobo? (Y) (N)\n");
			printf("Resposta:");
			scanf(" %c", &opCombate);
			if (opCombate == 'N' || opCombate == 'n'){
				printf("Voce Fugiu mesmo? Na proxima enfrente o inimigo!\n");
			}
			else if (opCombate == 'Y' || opCombate == 'y'){
				Inimigos lobo;
				lobo.dano = 2;
				lobo.vida = 6;
				int opcoes_ataq;
				while(lobo.vida > 0){
					mostrarstatus(*jogador);
					printf("Lobo - Vida: %i\n", lobo.vida);
					linhaDivisaoEspaco();
					printf("1- Atacar com sua espada\n2- Defender com seu escudo\n3- Usar Item\n4- Fugir\n$:");
					scanf("%i", &opcoes_ataq);
					system("cls");
					if(opcoes_ataq == 1){
						lobo.vida = lobo.vida - jogador->danoarma;
						printf("Voce acertou a criatura com um golpe de sua espada. O Lobo recebeu %i de Dano.\n", jogador->danoarma);
						jogador->vidaatual -= lobo.dano;
						printf("\nO lobo o atacou com suas garras afiadas. Voce recebeu %i de Dano.\n", lobo.dano);
						controledevida(jogador, opcoes_menu, pont_rank);					
					}
					else if(opcoes_ataq == 2){
						jogador->vidaatual = jogador->vidaatual - (lobo.dano/2);
						printf("O lobo o atacou com suas garras afiadas, mas você se defendeu com seu escudo e recebeu apenas %i de Dano.\n", lobo.dano/2);
						controledevida(jogador, opcoes_menu, pont_rank);
					}
					else if(opcoes_ataq == 3){
						int opcao_item;
						printf("1. Pocoes de Vida: %i\n2. Pocoes de veneno: %i.\n3. Voltar ao combate.\n", mochila->pocaovida, mochila->pocaoveneno);
						scanf("%i", &opcao_item);
						
						if(opcao_item == 1){
							if(mochila->pocaovida < 1){
								printf("Voce nao tem pocao de vida.\n");
							}
							else{
								printf("Voce gastou uma pocao de vida.\n");
								printf("Voce recuperou 25 de Vida.\n");
								mochila->pocaovida -= 1;
								jogador->vidaatual += 10;
								if(jogador->vidaatual > 20){
									jogador->vidaatual = 20;
								}
								
							}
						}
						else if(opcao_item == 2){
							if(mochila->pocaoveneno < 1){
								printf("Voce nao tem pocao de veneno.\n");
							}
							else{
								printf("Voce gastou uma pocao de veneno.\n");
								printf("Voce envenenou o inimigo ele perdeu 5 de vida.\n");
								mochila->pocaoveneno -= 1;
								lobo.vida -= 5;
							}
						}
						else if(opcao_item == 3){
							continue;
						}
					}
					else if(opcoes_ataq == 4){
						printf("Voce fugiu com sucesso do lobo.\n");
						break;
					}
					else if(jogador->vidaatual <= 0){
						break;
					}
				}
				if(lobo.vida <= 0){
					printf("\nVoce Matou o Lobo!.\n");
					jogador->terrenoatual = '.';
					srand(time(NULL));
					int recompensa = (rand() % 2);
					if(recompensa == 0){
						int dinhero = 1 + (rand() % 19);
						jogador->moedas = jogador->moedas + dinhero;
						printf("\nVoce recebeu %i moedas.\n", dinhero);
					}
					else if(recompensa == 1){
						printf("\nVoce recebeu uma pocao de vida.\n");
						mochila->pocaovida += 1;
						
					}
					else if(recompensa == 2){
						printf("\nA sua pericia com a espada foi aprimorada e seu dano com a espada virou %i.", jogador->danoarma);
						jogador->danoarma += 1;
					}
				}
				
			}
		}
		//Combate Urso
		else if(jogador->terrenoatual == 'B'){
			system("cls");
			printf("Deseja entrar em combate com um Urso? (Y) (N)\n");
			printf("Resposta:");
			scanf(" %c", &opCombate);
			if (opCombate == 'N' || opCombate == 'n'){
				printf("Voce Fugiu mesmo? Na proxima enfrente o inimigo!\n");
			}
			else if (opCombate == 'Y' || opCombate == 'y'){
				Inimigos urso;
				urso.dano = 4;
				urso.vida = 12;
				int opcoes_ataq;
				while(urso.vida > 0){
					mostrarstatus(*jogador);
					printf("Urso - Vida: %i\n", urso.vida);
					linhaDivisaoEspaco();
					printf("1- Atacar com sua espada\n2- Defender com seu escudo\n3- Usar Item\n4- Fugir\n$:");
					scanf("%i", &opcoes_ataq);
					system("cls");
					if(opcoes_ataq == 1){
						urso.vida = urso.vida - jogador->danoarma;
						printf("Voce acertou a criatura com um golpe de sua espada. O Urso recebeu %i de Dano.\n", jogador->danoarma);
						jogador->vidaatual -= urso.dano;
						printf("\nO Urso o atacou com suas garras afiadas. Voce recebeu %i de Dano.\n", urso.dano);
						controledevida(jogador, opcoes_menu, pont_rank);					}
					else if(opcoes_ataq == 2){
						jogador->vidaatual = jogador->vidaatual - (urso.dano/2);
						printf("O urso o atacou com enorme forca, mas voce se defendeu com seu escudo e recebeu apenas %i de Dano.\n", urso.dano/2);
						controledevida(jogador, opcoes_menu, pont_rank);
					}
					else if(opcoes_ataq == 3){
						int opcao_item;
						printf("1. Pocoes de Vida: %i\n2. Pocoes de veneno: %i.\n3. Voltar ao combate.\n", mochila->pocaovida, mochila->pocaoveneno);
						scanf("%i", &opcao_item);
						
						if(opcao_item == 1){
							if(mochila->pocaovida < 1){
								printf("Voce nao tem pocao de vida.\n");
							}
							else{
								printf("Voce gastou uma pocao de vida.\n");
								printf("Voce recuperou 25 de Vida.\n");
								mochila->pocaovida -= 1;
								jogador->vidaatual += 10;
								if(jogador->vidaatual > 20){
									jogador->vidaatual = 20;
								}
								
							}
						}
						else if(opcao_item == 2){
							if(mochila->pocaoveneno < 1){
								printf("Voce nao tem pocao de veneno.\n");
							}
							else{
								printf("Voce gastou uma pocao de veneno.\n");
								printf("Voce envenenou o inimigo ele perdeu 5 de vida.\n");
								mochila->pocaoveneno -= 1;
								urso.vida -= 5;
							}
						}
						else if(opcao_item == 3){
							continue;
						}
					}
					else if(opcoes_ataq == 4){
						printf("Voce fugiu com sucesso do Urso.\n");
						break;
					}
					else if(jogador->vidaatual <= 0){
						break;
					}
				}
				if(urso.vida <= 0){
					printf("\nVoce Matou o Urso!.\n");
					jogador->terrenoatual = 'Y';
					srand(time(NULL));
					int recompensa = (rand() % 2);
					if(recompensa == 0){
						int dinhero = 1 + (rand() % 39);
						jogador->moedas = jogador->moedas + dinhero;
						printf("\nVoce recebeu %i moedas.\n", dinhero);
					}
					else if(recompensa == 1){
						printf("\nVoce recebeu uma pocao de vida.\n");
						mochila->pocaovida += 1;
					}
					else if(recompensa == 2){
						printf("\nA sua pericia com a espada foi aprimorada e seu dano com a espada virou %i.", jogador->danoarma);
						jogador->danoarma += 2;
					}
				}			
			}				
		}
		//Combate Anaconda
		else if(jogador->terrenoatual == 'A'){
			system("cls");
			printf("Deseja entrar em combate com uma Anaconda? (Y) (N)\n");
			printf("Resposta:");
			scanf(" %c", &opCombate);
			if (opCombate == 'N' || opCombate == 'n'){
				printf("Voce Fugiu mesmo? Na proxima enfrente o inimigo!\n");
			}
			else if (opCombate == 'Y' || opCombate == 'y'){
				Inimigos anaconda;
				anaconda.dano = 4;
				anaconda.vida = 10;
				int opcoes_ataq;
				while(anaconda.vida > 0){
					mostrarstatus(*jogador);
					printf("Anaconda - Vida: %i\n", anaconda.vida);
					linhaDivisaoEspaco();
					printf("1- Atacar com sua espada\n2- Defender com seu escudo\n3- Usar Item\n4- Fugir\n$:");
					scanf("%i", &opcoes_ataq);
					system("cls");
					if(opcoes_ataq == 1){
						anaconda.vida = anaconda.vida - jogador->danoarma;
						printf("Voce acertou a criatura com um golpe de sua espada. A Anaconda recebeu %i de Dano.\n", jogador->danoarma);
						jogador->vidaatual -= anaconda.dano;
						printf("A Anaconda o atacou com seu veneno mortal. Voce recebeu %i de Dano.\n", anaconda.dano);
						controledevida(jogador, opcoes_menu, pont_rank);					
						}
					else if(opcoes_ataq == 2){
						jogador->vidaatual = jogador->vidaatual - (anaconda.dano/2);
						printf("\nA Anaconda o atacou com seu veneno mortal, mas voce se defendeu com seu escudo e recebeu apenas %i de Dano.\n", anaconda.dano/2);
						controledevida(jogador, opcoes_menu, pont_rank);
					}
					else if(opcoes_ataq == 3){
						int opcao_item;
						printf("1. Pocoes de Vida: %i\n2. Pocoes de veneno: %i.\n3. Voltar ao combate.\n", mochila->pocaovida, mochila->pocaoveneno);
						scanf("%i", &opcao_item);
						
						if(opcao_item == 1){
							if(mochila->pocaovida < 1){
								printf("Voce nao tem pocao de vida.\n");
							}
							else{
								printf("Voce gastou uma pocao de vida.\n");
								printf("Voce recuperou 25 de Vida.\n");
								mochila->pocaovida -= 1;
								jogador->vidaatual += 10;
								if(jogador->vidaatual > 20){
									jogador->vidaatual = 20;
								}
								
							}
						}
						else if(opcao_item == 2){
							if(mochila->pocaoveneno < 1){
								printf("Voce nao tem pocao de veneno.\n");
							}
							else{
								printf("Voce gastou uma pocao de veneno.\n");
								printf("Voce envenenou o inimigo ele perdeu 5 de vida.\n");
								mochila->pocaoveneno -= 1;
								anaconda.vida -= 5;
							}
						}
						else if(opcao_item == 3){
							continue;
						}
					}
					else if(opcoes_ataq == 4){
						printf("Voce fugiu com sucesso da Anaconda.\n");
						break;
					}
					else if(jogador->vidaatual <= 0){
						break;
					}
				}
				if(anaconda.vida <= 0){
					printf("\nVoce Matou a Anaconda.\n");
					jogador->terrenoatual = '~';
					srand(time(NULL));
					int recompensa = (rand() % 3);
					if(recompensa == 0){
						int dinhero = 1 + (rand() % 29);
						jogador->moedas = jogador->moedas + dinhero;
						printf("\nVoce recebeu %i moedas.\n", dinhero);
					}
					else if(recompensa == 1){
						printf("\nVoce recebeu uma pocao de vida.\n");
						mochila->pocaovida += 1;
					}
					else if(recompensa == 2){
						jogador->danoarma += 2;
						printf("\nA sua pericia com a espada foi aprimorada e seu dano com a espada virou %i.", jogador->danoarma);
					}
					else if(recompensa == 3){
						printf("Você recebeu uma pocao de veneno.\n");
						mochila->pocaoveneno +=1;
					}
				}
				
			}				
		}
		//combate Crocodilo
		else if(jogador->terrenoatual == 'K'){
			system("cls");
			printf("Deseja entrar em combate com um Crocodilo? (Y) (N)\n");
			printf("Resposta:");
			scanf(" %c", &opCombate);
			if (opCombate == 'N' || opCombate == 'n'){
				printf("Voce Fugiu mesmo? Na proxima enfrente o inimigo!\n");
			}
			else if (opCombate == 'Y' || opCombate == 'y'){
				Inimigos crocodilo;
				crocodilo.dano = 8;
				crocodilo.vida = 14;
				int opcoes_ataq;
				while(crocodilo.vida > 0){
					mostrarstatus(*jogador);
					printf("Crocodilo - Vida: %i\n", crocodilo.vida);
					linhaDivisaoEspaco();
					printf("1- Atacar com sua espada\n2- Defender com seu escudo\n3- Usar Item\n4- Fugir\n$:");
					scanf("%i", &opcoes_ataq);
					system("cls");
					if(opcoes_ataq == 1){
						crocodilo.vida = crocodilo.vida - jogador->danoarma;
						printf("Voce acertou a criatura com um golpe de sua espada. O Crocodilo recebeu %i de Dano.\n", jogador->danoarma);
						jogador->vidaatual -= crocodilo.dano;
						printf("\nO Crocodilo o atacou com sua mordida descomunal. Voce recebeu %i de Dano.\n", crocodilo.dano);
						controledevida(jogador, opcoes_menu, pont_rank);					}
					else if(opcoes_ataq == 2){
						jogador->vidaatual = jogador->vidaatual - (crocodilo.dano/4);
						printf("O Crocodilo o atacou com sua mordida descomunal, mas voce se defendeu com seu escudo e recebeu apenas %i de Dano.\n", crocodilo.dano/4);
						controledevida(jogador, opcoes_menu, pont_rank);
					}
					else if(opcoes_ataq == 3){
						int opcao_item;
						printf("1. Pocoes de Vida: %i\n2. Pocoes de veneno: %i.\n3. Voltar ao combate.\n", mochila->pocaovida, mochila->pocaoveneno);
						scanf("%i", &opcao_item);
						
						if(opcao_item == 1){
							if(mochila->pocaovida < 1){
								printf("Voce nao tem pocao de vida.\n");
							}
							else{
								printf("Voce gastou uma pocao de vida.\n");
								printf("Voce recuperou 25 de Vida.\n");
								mochila->pocaovida -= 1;
								jogador->vidaatual += 10;
								if(jogador->vidaatual > 20){
									jogador->vidaatual = 20;
								}
								
							}
						}
						else if(opcao_item == 2){
							if(mochila->pocaovida < 1){
								printf("Voce nao tem pocao de veneno.\n");
							}
							else{
								printf("Voce gastou uma pocao de veneno.\n");
								printf("Voce envenenou o inimigo ele perdeu 9 de vida.\n");
								mochila->pocaoveneno -= 1;
								crocodilo.vida -= 9;
							}
						}
						else if(opcao_item == 3){
							continue;
						}
					}
					else if(opcoes_ataq == 4){
						printf("Voce fugiu com sucesso do Crocodilo.\n");
						break;
					}
					else if(jogador->vidaatual <= 0){
						break;
					}
				}
				if(crocodilo.vida <= 0){
					printf("\nVoce Matou o Crocodilo.\n");
					jogador->terrenoatual = '~';
					srand(time(NULL));
					int recompensa = (rand() % 2);
					if(recompensa == 0){
						int dinhero = 1 + (rand() % 29);
						jogador->moedas = jogador->moedas + dinhero;
						printf("\nVoce recebeu %i moedas.\n", dinhero);
					}
					else if(recompensa == 1){
						printf("\nVoce recebeu uma pocao de vida.\n");
						mochila->pocaovida += 1;
					}
					else if(recompensa == 2){
						printf("\nA sua pericia com a espada foi aprimorada e seu dano com a espada virou %i.\n", jogador->danoarma);
						jogador->danoarma++;
					}
				}	
			}				
		}
	}
	//mochila
	else if(jogador->terrenoatual == 'C'){
		int resp_mercador;
		system("cls");
		printf("Eu costumava ser um aventureiro como voce, ate que levei uma flechada no joelho!\n");
		printf("Eu sou um mercador, deseja comprar algo?\n");
		printf("1. Sim\n2. Nao\n");
		scanf("%i", &resp_mercador);
		
		if(resp_mercador == 1){
			system("cls");
			int compra;
			printf("1. Pocao de Vida: 10 Moedas\n2. Pocao de Veneno: 5 Moedas\n3. Nao desejo comprar nada.\n");
			scanf("%i", &compra);
			
			if(compra == 1){
				if(jogador->moedas >= 10){
					jogador->moedas -= 10;
					printf("Voce recebeu uma pocao de vida.\n");
					mochila->pocaovida += 1;
				}
				else{
					printf("Voce nao tem moedas suficientes.\n");
				}
			}
			else if(compra == 2){
				if(jogador->moedas >= 5){
					jogador->moedas -= 5;
					printf("Voce recebeu uma pocao de veneno.\n");
					mochila->pocaoveneno += 1;
				}
				else{
					printf("Voce nao tem moedas suficientes.\n");
				}
			}
			else if(compra == 3){
				printf("Tudo bem, tenha um bom dia.\n");
			}
		}
		else if(resp_mercador == 2){
			printf("Tudo bem, tenha um bom dia.\n");
		}
	}
	else if(jogador->terrenoatual == '$'){
		srand(time(NULL));
		int recompensa = (rand() % 3);
		if(recompensa == 0){
			int dinhero = 1 + (rand() % 29);
			jogador->moedas = jogador->moedas + dinhero;
			printf("Voce recebeu %i moedas.\n", dinhero);
		}
		else if(recompensa == 1){
			printf("Voce recebeu uma pocao de vida.\n");
			mochila->pocaovida += 1;
		}
		else if(recompensa == 2){
			jogador->danoarma += 2;
			printf("Voce encontrou uma lamina melhor, seu dano atual e %i.\n", jogador->danoarma);
		}
		else if(recompensa == 3){
			mochila->pocaoveneno += 1;
			printf("Voce recebeu uma pocao de veneno.\n");
		}
		jogador->terrenoatual = '.';
	}
}
