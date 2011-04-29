//Descritivo:Primeiro trabalho de grupo da disciplina de SO
//Titulo:Jogo de Aventura
//Autores: Luís Costa Nº6032, Bruno Moreira Nº6170

#include "stdafx.h"
#include "string.h"
#include <ctime>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_CELULAS 9

//-------------------------------------------------------------------------------------------------
//	ESTRUTURAS
//-------------------------------------------------------------------------------------------------

//Jogador
//---------------------
struct Jogador
{
	char	nome[50];			//Nome do jogador
	int		energia;			//Energia do jogador
	int		localizacao;		//Celula onde o jogador se encontra
	int		flg_tem_tesouro;	//Se o jogador tem ou não tesouro
};

//Celula
//---------------------
// lista de valores possíveis
// **
// norte, sul, este, oeste
//		-1, porta inválida
//	   >=0, ´número da célula
// **
// item
//		 -1, sem item
//		  0, tesouro
struct Celula
{
	int		norte;				//Qual a celula a norte
	int		sul;				//Qual a celula a sul
	int		este;				//Qual a celula a este
	int		oeste;				//Qual a celula a oeste
	char	descricao[400];		//Descrição da celula
	int		item;				//Item	que existe na celula
};

//Monstro
//---------------------
struct Monstro
{
	char	nome[50];
	int		energia;			//Energia do jogador
	int		localizacao;		//Celula onde o jogador se encontra

};

//-------------------------------------------------------------------------------------------------
//	FUNÇÕES
//-------------------------------------------------------------------------------------------------

//Inicializa o jogador
void inicializa_jogador(struct Jogador *pJogador, char* nome, bool blnSuperUser)
{
	// associa os dados por defeito ao jogador
	strcpy(pJogador->nome, nome);
	pJogador->localizacao		= 0;
	pJogador->flg_tem_tesouro	= -1;
	
	if (blnSuperUser == true) {
		pJogador->energia			= 9999;			// energia do superuser
	}
	else {
		pJogador->energia			= 100;			// energia do utilizador normal
	}

	// validador dos dados atribuidos
	printf( "[DADOS DO JOGADOR]\n\n");
	printf( "Nome:%s\n", &pJogador->nome );
	printf( "Energia:%d\n", pJogador->energia );
	printf( "Localização:%d\n", pJogador->localizacao );
	printf( "Flag:%d\n", pJogador->flg_tem_tesouro );
}

//Inicializa o mapa da aventura
//--------------------------------
//    +------+------+------+
//    |             |      |
//    |0     |1     |2     |
//    +------+--  --+--  --+
//    |                    |
//    |3     |4     |5    T|
//    +--  --+------+------+
//    |                    |
//    |6     |7     |8     |
//    +------+------+------+
void inicializa_mapa(struct Celula pMapa[])
{
	int n;

	//pMapa[0].este = 1;
	//pMapa[0]->norte = 1;
	//printf("[MAPA] Sala 0 %d", pMapa[0].este);

	//Construção da sala 0
	//----------------------
	strcpy( pMapa[0].descricao, "Sala 0");
	pMapa[0].norte	= -1;
	pMapa[0].sul	= -1;
	pMapa[0].este	= 1;
	pMapa[0].oeste	= -1;
	pMapa[0].item	= -1;

	//Construção da sala 1
	//----------------------
	strcpy( pMapa[1].descricao, "Sala 1");
	pMapa[1].norte	= -1;
	pMapa[1].sul	= 4;
	pMapa[1].este	= -1;
	pMapa[1].oeste	= 0;
	pMapa[1].item	= -1;

	//Construção da sala 2
	//----------------------
	strcpy( pMapa[2].descricao, "Sala 2");
	pMapa[2].norte	= -1;
	pMapa[2].sul	= 5;
	pMapa[2].este	= -1;
	pMapa[2].oeste	= -1;
	pMapa[2].item	= -1;

	//Construção da sala 3
	//----------------------
	strcpy( pMapa[3].descricao, "Sala 3");
	pMapa[3].norte	= -1;
	pMapa[3].sul	= 6;
	pMapa[3].este	= 4;
	pMapa[3].oeste	= -1;
	pMapa[3].item	= -1;

	//Construção da sala 4
	//----------------------
	strcpy( pMapa[4].descricao, "Sala 4");
	pMapa[4].norte	= 1;
	pMapa[4].sul	= -1;
	pMapa[4].este	= 5;
	pMapa[4].oeste	= 3;
	pMapa[4].item	= -1;

	//Construção da sala 5
	//----------------------
	strcpy( pMapa[5].descricao, "Sala 5");
	pMapa[5].norte	= 2;
	pMapa[5].sul	= -1;
	pMapa[5].este	= -1;
	pMapa[5].oeste	= 4;
	pMapa[5].item	= 0;

	//Construção da sala 6
	//----------------------
	strcpy( pMapa[6].descricao, "Sala 6");
	pMapa[6].norte	= 3;
	pMapa[6].sul	= -1;
	pMapa[6].este	= 7;
	pMapa[6].oeste	= -1;
	pMapa[6].item	= -1;

	//Construção da sala 7
	//----------------------
	strcpy( pMapa[7].descricao, "Sala 7");
	pMapa[7].norte	= -1;
	pMapa[7].sul	= -1;
	pMapa[7].este	= 8;
	pMapa[7].oeste	= 6;
	pMapa[7].item	= -1;

	//Construção da sala 8
	//----------------------
	strcpy( pMapa[8].descricao, "Sala 8");
	pMapa[8].norte	= -1;
	pMapa[8].sul	= -1;
	pMapa[8].este	= -1;
	pMapa[8].oeste	= 7;
	pMapa[8].item	= -1;

	// Valida MAPA
	//for (int i = 0; i < MAX_CELULAS; i++) {
	//	printf("[%s]\n", pMapa[i].descricao);
	//	printf("Norte: %d\n", pMapa[i].norte);
	//	printf("Sul:   %d\n", pMapa[i].sul);
	//	printf("Este:  %d\n", pMapa[i].este);
	//	printf("Oeste: %d\n", pMapa[i].oeste);
	//	printf("Item:  %d\n\n", pMapa[i].item);
	//}
}

// inicializa o monstro
void inicializa_monstro(struct Monstro *pMonstro)
{
	// associa os dados por defeito ao monstro
	strcpy(pMonstro->nome, "Wor'urna");
	pMonstro->energia		= 50;
	pMonstro->localizacao	= 4;

	// validador dos dados atribuidos
	printf( "[DADOS DO MONSTRO]\n\n");
	printf( "Nome:%s\n", &pMonstro->nome );
	printf( "Energia:%d\n", pMonstro->energia );
	printf( "Localização:%d\n", pMonstro->localizacao );
}

// Generate a random number between nLow and nHigh (inclusive)
unsigned int GetRandomNumber(int nLow, int nHigh)
{
	return (rand() % (nHigh - nLow + 1)) + nLow;
}

// movimenta o monstro
void movimenta_monstro(struct Monstro *pMonstro, struct Celula pMapa[])
{
	// faz random para decidir se movimenta ou não
	int iMovimenta = GetRandomNumber(0, 1);
	
	// é para movimentar
	if ( iMovimenta == 1 && pMonstro->localizacao != -1)
	{
		// verifica quais as saídas existentes na localização actual do monstro
		int iLocalizacaoActual = pMonstro->localizacao;
		
		int iEste = pMapa[iLocalizacaoActual].este;
		int iNorte = pMapa[iLocalizacaoActual].norte;
		int iSul = pMapa[iLocalizacaoActual].sul;
		int iOeste = pMapa[iLocalizacaoActual].oeste;

		// adiciona as entradas com valor maior ou igual a 0 a um array
		unsigned int iSaidas[4];
		int iPos = -1;

		if (iEste  >= 0) { iPos++; iSaidas[iPos]=iEste; }
		if (iNorte >= 0) { iPos++; iSaidas[iPos]=iNorte; }
		if (iSul   >= 0) { iPos++; iSaidas[iPos]=iSul; }
		if (iOeste >= 0) { iPos++; iSaidas[iPos]=iOeste; }

		//printf("Saídas: Norte:%d || Sul:%d || Este:%d || Oeste:%d\n", iNorte, iSul, iEste, iOeste);
		//printf("Localização do Monstro Antes:%d\n", pMonstro->localizacao);

		// faz random das saídas existentes
		int iNovaLocalizacao = iSaidas[GetRandomNumber(0, iPos)];

		// altera a localização do monstro
		pMonstro->localizacao = iNovaLocalizacao;
		//printf("Localização do Monstro Depois:%d\n", pMonstro->localizacao);
	}

}

// Aceita comando do jogador
int aceita_comando_jogador(char* *sComando, struct Jogador *pJogador, struct Celula pMapa[])
{
	// valida a localização do jogador
	int iLocalizacaoJogador = pJogador->localizacao;
	int iMovimento = -1;

	// validar comandos disponíveis
	if ( strcmp((char*) sComando, "N") == 0 || strcmp((char*) sComando, "n") == 0 ) {
		iMovimento = pMapa[iLocalizacaoJogador].norte;
	}
	
	if ( strcmp((char*) sComando, "S") == 0 || strcmp((char*) sComando, "s") == 0 ) {
		iMovimento = pMapa[iLocalizacaoJogador].sul;
	}
	
	if ( strcmp((char*) sComando, "E") == 0 || strcmp((char*) sComando, "e") == 0 ) {
		iMovimento = pMapa[iLocalizacaoJogador].este;
	}
	
	if ( strcmp((char*) sComando, "O") == 0 || strcmp((char*) sComando, "o") == 0 ) {
		iMovimento = pMapa[iLocalizacaoJogador].oeste;
	}

	// retorna o movimento que foi feito
	return iMovimento;
}

// Movimenta ao jogador para a localização pretendida
void movimenta_jogador(int iLocalizacao, struct Jogador *pJogador)
{
	// validar se o comando recebido está nos comandos disponíveis
	if (iLocalizacao >= 0) {
		// movimenta jogador
		pJogador->localizacao = iLocalizacao;
	}
}

// Descreve jogador
void descreve_jogador(struct Jogador *pJogador)
{
	printf("+------------------------------\n");
	printf("| DADOS DO JOGADOR\n");
	printf("|\n");
	printf("| Nome   : %s\n", pJogador->nome);
	printf("| Energia: %d\n", pJogador->energia);
	printf("+------------------------------\n");
}

// Descreve monstro
void descreve_monstro(struct Monstro *pMonstro)
{
	printf("+------------------------------\n");
	printf("| DESCRIÇÃO DOS MONSTROS\n");
	printf("|\n");
	printf("| %s   Energia:%d\n", pMonstro->nome, pMonstro->energia);
	printf("+------------------------------\n");
}

// Desenha no ecrã o que ocorre no jogo
void descreve_status(struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[])
{
	system("cls");							// limpa ecrã

	// descreve jogador
	descreve_jogador(pJogador);

	printf("+------------------------------\n");
	printf("| DESCRIÇÃO DA LOCALIZAÇÃO\n");
	printf("|\n");
	printf("| %s\n", pMapa[pJogador->localizacao].descricao);
	printf("+------------------------------\n");

	//printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n");
	
}

// Simula a luta entre jogador e monstro
int lutar(struct Jogador *pJogador, struct Monstro *pMonstro)
{
	int MAX_DANO = 30;
	int iReturn = 1;

	// descreve status
		system("cls");
		printf("+------------------------------\n");
		printf("| COMBATE\n");
		printf("+------------------------------\n");
		descreve_jogador(pJogador);
		descreve_monstro(pMonstro);

	// solicita a posição para atacar (cima, baixo, esquerda, direita, foge)
		int iJogadorAtaque;
		printf("Qual a posição em que quer atacar? 1-cima, 2-baixo, 3-esquerda, 4-direita, 0-fugir:\n");
		scanf( "%d", &iJogadorAtaque );

	// solicita a posição para defender
		int iJogadorDefesa;
		printf("Qual a posição em que quer defender? 1-cima, 2-baixo, 3-esquerda, 4-direita, 0-fugir:\n");
		scanf( "%d", &iJogadorDefesa );

	// random de da posição onde o monstro defende/ataca
	// (cima, baixo, esquerda, direita, foge)
		int iMonstroAtaque = GetRandomNumber(0, 4);
		int iMonstroDefesa = GetRandomNumber(0, 4);
	
	// calcula dano
		int iDanoJogador = GetRandomNumber(1, MAX_DANO);
		int iDanoMonstro = GetRandomNumber(1, MAX_DANO);

	// Simula a luta
		// ATAQUE
		if (iJogadorAtaque == iMonstroDefesa)
		{
			printf("O monstro defendeu o ataque!\n");
		}
		else
		{
			// desconta o dano no monstro
			printf("Causou %d pontos de dano no monstro %s\n", iDanoJogador, pMonstro->nome);
			pMonstro->energia = pMonstro->energia - iDanoJogador;
		}

		// DEFESA
		if (iMonstroAtaque == iJogadorDefesa)
		{
			printf("O jogador defendeu o ataque!\n");
		}
		else
		{
			// desconta o dano no jogador
			printf("O monstro %s causou-lhe %d pontos de dano\n", pMonstro->nome, iDanoMonstro);
			pJogador->energia = pJogador->energia - iDanoMonstro;
		}

	// Valida se a luta terminou

		if (pJogador->energia <= 0)
		{
			// o monstro matou o jogador
			printf("Infelizmente o monstro %s matou-o!\n", pMonstro->nome);
			iReturn = 0;
		}

		if (pMonstro->energia <= 0)
		{
			// o jogador matou o monstro
			printf("Parabéns! Matou o monstro %s!\n", pMonstro->nome);

			// remove o monstro do mapa
			pMonstro->localizacao = -1;
			iReturn = 0;
		}

		// pausa se a luta terminou
		system("pause");

		return iReturn;
}

// Tenta apanhar o tesouro
bool apanha_tesouro(struct Jogador *pJogador, struct Celula pMapa[])
{
	// se exitir tesouro apanha-o
	if (pMapa[pJogador->localizacao].item == 0)
	{
		// define o jogador como tendo o tesouro
		pJogador->flg_tem_tesouro = 0;

		// retira o tesouro da célula
		pMapa[pJogador->localizacao].item = -1;

		// o tesouro foi apanhado
		return true;
	}

	// o tesouro não foi apanhado
	return false;
}

// valida os comandos disponíveis para o jogador
char* valida_comandos_disponiveis(struct Celula *pMapa)
{
	int MAX_CHARS = 100;
	char* sComandosDisponiveis;
	sComandosDisponiveis = (char *) malloc( MAX_CHARS );
	strcpy((char*) sComandosDisponiveis, "+------------------------------\n");

	// valida Norte
		if (pMapa->norte >= 0){	strcat((char*) sComandosDisponiveis, "| N - Norte\n");}
	// valida Sul
		if (pMapa->sul >= 0)  {	strcat((char*) sComandosDisponiveis, "| S - Sul\n");  }
	// valida Este
		if (pMapa->este >= 0) {	strcat((char*) sComandosDisponiveis, "| E - Este\n"); }
	// valida Oeste
		if (pMapa->oeste >= 0){	strcat((char*) sComandosDisponiveis, "| O - Oeste\n");}

	return (char*) sComandosDisponiveis;
}

// valida switches
void validaSwitches(int argc, char* args[], bool *pSuperUser, char *pFicheiroMapa)
{
	bool godMode = false;

	printf("Argumentos %d", argc);
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(args[i], "su") == 0 || strcmp(args[i], "SU") == 0) { *pSuperUser = true; }			   // modo GOD
		if (strcmp(args[i], "m") == 0 || strcmp(args[i], "M") == 0) { strcpy(pFicheiroMapa, args[i+1]); }  // faz load do mapa
	}
}


//-------------------------------------------------------------------------------------------------
//	MAIN
//-------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	int iResultado;
	setlocale( LC_ALL, "Portuguese" );
	srand(time(0));

	//--------------------------------
	/Chama a função para validar os switches
	//--------------------------------
	bool superUser = false;						// define se está ou não no modo superuser
	char* ficheiroMapa[100];					// nome do ficheiro do mapa

	validaSwitches(argc, argv, &superUser, (char*) ficheiroMapa);

	//--------------------------------
	//Chama a função para inicializar o jogador
	//--------------------------------
	struct Jogador jogador;
	char * nomeJogador[50];
	// solicita o nome do jogador
	printf( "Indique o nome do jogador:" );
	scanf( "%s", &nomeJogador );

	inicializa_jogador(&jogador, (char *) nomeJogador, superUser );

	//--------------------------------
	//Chama a função para inicializar o mapa
	//--------------------------------
	struct Celula mapa[MAX_CELULAS];				//Cria um array de células para o mapa do jogo
	inicializa_mapa( mapa,  );

	//--------------------------------
	//Chama a função para inicializar o monstro
	//--------------------------------
	struct Monstro monstro;
	inicializa_monstro( &monstro );

	//--------------------------------
	// Inicia o jogo
	//--------------------------------
	
	//Enquanto não for Fim de Jogo 
	while (jogador.energia > 0 && jogador.flg_tem_tesouro == -1)
	{
		//	Movimentar Monstro
		movimenta_monstro(&monstro, mapa);

		//	Descrever a Localização do Jogador
		descreve_status(&jogador, &monstro, mapa);

		//	TODO: Aceitar Comando do Jogador
		char* sComando;

		// TODO: validar/imprimir comandos disponíveis
		char* sComandosDisponiveis = valida_comandos_disponiveis(&mapa[jogador.localizacao]);
		printf("%s\n", sComandosDisponiveis);
		printf("Insira um Comando: ");
		scanf( "%s", &sComando );
		int iMovimento = aceita_comando_jogador(&sComando, &jogador, mapa);
			
		if (iMovimento < 0) {
			printf("Movimento não disponível!\n");
		}
		else
		{
			printf("Movimentou-se para a localização %d\n", iMovimento);
		}
		//	Movimentar Jogador
		movimenta_jogador(iMovimento, &jogador);

		//  apanha o tesouro
		bool tesouro = apanha_tesouro(&jogador, mapa);

		if (tesouro == true) { printf("Apanhou o tesouro! %d\n", jogador.flg_tem_tesouro); system("pause"); }

		//	Se a Localização do Jogador for igual à do Monstro
		if (iMovimento == monstro.localizacao)
		{
			// avisa o jogador que se encontra na mesma localização que o monstro e que tem de lutar
			printf("Há um monstro na sala... tens que lutar!!\n");
			system("pause");
			iResultado = 1;
			// Lutar
			while (iResultado != 0)
			{
				// descreve status
				iResultado = lutar(&jogador, &monstro);
			}
		}
	}

	printf("----O jogo terminou----");
	system( "pause" );
	return 0;
}

