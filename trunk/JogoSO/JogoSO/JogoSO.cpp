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
#include <ctype.h>
#include "windows.h"

#define MAX_CELULAS 9

//-------------------------------------------------------------------------------------------------
//	ESTRUTURAS
//-------------------------------------------------------------------------------------------------

//Jogador
//---------------------
struct Jogador
{
	char*	nome[50];			//Nome do jogador
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
	char*	descricao[400];		//Descrição da celula
	int		item;				//Item	que existe na celula
};

//Monstro
//---------------------
struct Monstro
{
	char*	nome[50];
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
	strcpy((char*) pJogador->nome, nome);
	pJogador->localizacao		= 0;
	pJogador->flg_tem_tesouro	= -1;
	
	if (blnSuperUser == true) {
		pJogador->energia			= 9999;			// energia do superuser
	}
	else {
		pJogador->energia			= 100;			// energia do utilizador normal
	}
}

// ltrim
char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

// rtrim
char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

// trim
char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

// inicilializa mapa com base num ficheiro
void inicializa_mapa_ficheiro(struct Celula pMapa[], char* pFicheiroMapa)
{
	printf("inicializa mapa ficheiro\n");
	system("pause");
	#define MAX_LIN 80
	#define CAMPOS 7

	FILE *f;
	char l[ MAX_LIN ];

	f = fopen( pFicheiroMapa, "r" );
	
	// inicia a linha
	int iLinha = 0;

	// inicia o contador
	int iIndice = -1;

	// percorre o ficheiro até encontrar o fim
	while( fgets(l, MAX_LIN, f) != NULL ){

		// se o resto da divisão do número da linha pelo número de linhas por célula
		// for igual a 0, quer dizer que é um novo registo
		if (iLinha % CAMPOS == 0)
		{
			// incrementa o indice
			iIndice = iIndice + 1;
		}

		// imprime a linha
		int iResto = iLinha % CAMPOS;

		switch ( iResto )
		{
			case 0:	// Descrição
				strcpy((char*)pMapa[iIndice].descricao, rtrim(l));
				break;
			case 1:	// Norte
				pMapa[iIndice].norte = atoi (l);
				break;
			case 2:	// Sul
				pMapa[iIndice].sul = atoi (l);
				break;
			case 3:	// Este
				pMapa[iIndice].este = atoi (l);
				break;
			case 4:	// Oeste
				pMapa[iIndice].oeste = atoi (l);
				break;
			case 5:	// Item
				pMapa[iIndice].item = atoi (l);
				break;
		}

		// incrementa o número da linha
		iLinha = iLinha + 1;
	}
	
	fclose( f );

	printf("concluiu a inicialização do mapa com base num ficheiro\n");
	system("pause");

}

// Inicilializa mapa com base num ficheiro binário
void inicializa_mapa_ficheiro_bin(struct Celula pMapa[], char* pFicheiroMapa)
{
	printf("inicializa mapa ficheiro binário\n");
	system("pause");

	#define MAX_LIN 80
	#define CAMPOS 7

	FILE *f;
	char l[ MAX_LIN ];

	f = fopen( pFicheiroMapa, "rb" );
	
	// inicia a linha
	int iLinha = 0;

	// inicia o contador
	int iIndice = -1;

	if (f != NULL)
	{
		// percorre o ficheiro até encontrar o fim
		while( fread(l,sizeof(char), MAX_LIN, f) != NULL ){

			// se o resto da divisão do número da linha pelo número de linhas por célula
			// for igual a 0, quer dizer que é um novo registo
			if (iLinha % CAMPOS == 0)
			{
				// incrementa o indice
				iIndice = iIndice + 1;
			}

			// imprime a linha
			int iResto = iLinha % CAMPOS;

			switch ( iResto )
			{
				case 0:	// Descrição
					strcpy((char*)pMapa[iIndice].descricao, rtrim(l));
					break;
				case 1:	// Norte
					pMapa[iIndice].norte = atoi (l);
					break;
				case 2:	// Sul
					pMapa[iIndice].sul = atoi (l);
					break;
				case 3:	// Este
					pMapa[iIndice].este = atoi (l);
					break;
				case 4:	// Oeste
					pMapa[iIndice].oeste = atoi (l);
					break;
				case 5:	// Item
					pMapa[iIndice].item = atoi (l);
					break;
			}

			// incrementa o número da linha
			iLinha = iLinha + 1;
		}
	
		fclose( f );

		printf("concluiu a inicialização do mapa com base num ficheiro binário\n");
	}
	else
	{
		printf("Erro a abrir o ficheiro %s",pFicheiroMapa); 
	}
	system("pause");

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
void inicializa_mapa(struct Celula pMapa[], char* pFicheiroMapa)
{
	printf("inicializa_mapa\n");
	// se o tamanho da string pFicheiroMapa for superior a 0 então é
	// para carregar o mapa do ficheiro
	if (strlen(pFicheiroMapa) > 1)
	{
		// carrega mapa do ficheiro
		inicializa_mapa_ficheiro_bin(pMapa, pFicheiroMapa);
	}
	else
	{
		//Construção da sala 0
		//----------------------
		strcpy((char*) pMapa[0].descricao, "Sala 0");
		pMapa[0].norte	= -1;
		pMapa[0].sul	= -1;
		pMapa[0].este	= 1;
		pMapa[0].oeste	= -1;
		pMapa[0].item	= -1;

		//Construção da sala 1
		//----------------------
		strcpy((char*) pMapa[1].descricao, "Sala 1");
		pMapa[1].norte	= -1;
		pMapa[1].sul	= 4;
		pMapa[1].este	= -1;
		pMapa[1].oeste	= 0;
		pMapa[1].item	= -1;

		//Construção da sala 2
		//----------------------
		strcpy((char*) pMapa[2].descricao, "Sala 2");
		pMapa[2].norte	= -1;
		pMapa[2].sul	= 5;
		pMapa[2].este	= -1;
		pMapa[2].oeste	= -1;
		pMapa[2].item	= -1;

		//Construção da sala 3
		//----------------------
		strcpy((char*) pMapa[3].descricao, "Sala 3");
		pMapa[3].norte	= -1;
		pMapa[3].sul	= 6;
		pMapa[3].este	= 4;
		pMapa[3].oeste	= -1;
		pMapa[3].item	= -1;

		//Construção da sala 4
		//----------------------
		strcpy((char*) pMapa[4].descricao, "Sala 4");
		pMapa[4].norte	= 1;
		pMapa[4].sul	= -1;
		pMapa[4].este	= 5;
		pMapa[4].oeste	= 3;
		pMapa[4].item	= -1;

		//Construção da sala 5
		//----------------------
		strcpy((char*) pMapa[5].descricao, "Sala 5");
		pMapa[5].norte	= 2;
		pMapa[5].sul	= -1;
		pMapa[5].este	= -1;
		pMapa[5].oeste	= 4;
		pMapa[5].item	= 0;


		//Construção da sala 6
		//----------------------
		strcpy((char*) pMapa[6].descricao, "Sala 6");
		pMapa[6].norte	= 3;
		pMapa[6].sul	= -1;
		pMapa[6].este	= 7;
		pMapa[6].oeste	= -1;
		pMapa[6].item	= -1;

		//Construção da sala 7
		//----------------------
		strcpy((char*) pMapa[7].descricao, "Sala 7");
		pMapa[7].norte	= -1;
		pMapa[7].sul	= -1;
		pMapa[7].este	= 8;
		pMapa[7].oeste	= 6;
		pMapa[7].item	= -1;

		//Construção da sala 8
		//----------------------
		strcpy((char*) pMapa[8].descricao, "Sala 8");
		pMapa[8].norte	= -1;
		pMapa[8].sul	= -1;
		pMapa[8].este	= -1;
		pMapa[8].oeste	= 7;
		pMapa[8].item	= -1;
	}
}

//Converte o mapa para um ficheiro binário
void converte_mapa()
{
	printf("A converter o mapa para binário...");
	system("pause");

	#define MAX_COL 80				// tamanho máximo da linha		

	FILE *forigem;					// ficheiro de origem
	FILE *fdestino;					// ficheiro dedestino
	char l[ MAX_COL ];				// linha

	char* nomeMapaOrigem[100];						// nome do ficheiro do mapa
	char* nomeMapaDestino[100];

	strcpy((char*) nomeMapaOrigem, "");
	strcpy((char*) nomeMapaDestino, "");

	//Pede o nome do ficheiro do mapa a converte
	printf("Nome do mapa a converter:");
	scanf("%s", nomeMapaOrigem);

	strcpy((char*) nomeMapaDestino, (char*) nomeMapaOrigem);

	//Abre o ficheiro do mapa de origem
	forigem = fopen( strcat((char*) nomeMapaOrigem, ".txt"), "r");

	//Abre o ficheiro do mapa de destino em binário
	fdestino = fopen( strcat((char*) nomeMapaDestino, "b.txt"), "wb");

	if (forigem != NULL)
	{
		if (fdestino != NULL)
		{
			// percorre o ficheiro de origem até encontrar o fim
			while( fgets(l, MAX_COL, forigem) != NULL )
			{
				printf("Dados:%s/n",l);
				system("pause");

				//grava a linha no ficheiro binário
				fwrite(l,sizeof(char),MAX_COL,fdestino);
			}

			fclose(fdestino);
		}
		else
		{
			printf("Erro a abrir/criar o ficheiro binário do mapa/n"); 
		}

		fclose(forigem);

		printf("Ficheiro do mapa convertido/n");
		system("pause");
	}
	else
	{
		printf("Erro a ler o ficheiro %s/n", nomeMapaOrigem);
	}
}

// testes da inicialização do mapa
void inicializa_mapa_teste (struct Celula pMapa[])
{
	printf ("inicializa_mapa_teste\n");
	for (int i = 0; i < MAX_CELULAS; i++)
	{
		printf("[%s]\n", pMapa[i].descricao);
		printf("Norte: %d\n", pMapa[i].norte);
		printf("Sul:   %d\n", pMapa[i].sul);
		printf("Este:  %d\n", pMapa[i].este);
		printf("Oeste: %d\n", pMapa[i].oeste);
		printf("Item:  %d\n\n", pMapa[i].item);
	}
	system("pause");
}

// testes da inicialização do jogador
void inicializa_jogador_teste ( struct Jogador *pJogador )
{
	printf ("inicializa_jogador_teste\n");
	printf("Nome: %s\n", pJogador->nome);
	printf("Energia:   %d\n", pJogador->energia);
	printf("Localização:  %d\n", pJogador->localizacao);
	printf("Tesouro: %d\n", pJogador->flg_tem_tesouro);
	system("pause");
}

// testes da inicialização do monstro
void inicializa_monstro_teste ( struct Monstro *pMonstro )
{
	printf ("inicializa_monstro_teste\n");
	printf("Nome: %s\n", pMonstro->nome);
	printf("Energia:   %d\n", pMonstro->energia);
	printf("Localização:  %d\n", pMonstro->localizacao);
	system("pause");
}

// inicializa o monstro
void inicializa_monstro(struct Monstro *pMonstro)
{
	// associa os dados por defeito ao monstro
	strcpy((char*) pMonstro->nome, "Wor'urna");
	pMonstro->energia		= 50;
	pMonstro->localizacao	= 4;
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
int aceita_comando_jogador(char *sComando, struct Jogador *pJogador, struct Celula pMapa[])
{
	// valida a localização do jogador
	int iLocalizacaoJogador = pJogador->localizacao;
	int iAccao = -1;

	// validar comandos disponíveis
	sComando = strupr(sComando);

	if ( strcmp(sComando, "N") == 0 ) {
		iAccao = pMapa[iLocalizacaoJogador].norte;
	}
	
	if ( strcmp(sComando, "S") == 0 ) {
		iAccao = pMapa[iLocalizacaoJogador].sul;
	}
	
	if ( strcmp(sComando, "E") == 0 ) {
		iAccao = pMapa[iLocalizacaoJogador].este;
	}
	
	if ( strcmp(sComando, "O") == 0 ) {
		iAccao = pMapa[iLocalizacaoJogador].oeste;
	}

	if ( strcmp(sComando, "G") == 0 ) {					// carregar jogo
		iAccao = 100;
	}

	if ( strcmp(sComando, "C") == 0 ) {					// gravar jogo
		// gravar jogo
		iAccao = 101;
	}

	if ( strcmp(sComando, "B") == 0 ) {					// converte mapa para binário

		iAccao = 102;
	}

	// retorna o movimento que foi feito
	return iAccao;
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
	/*printf("+------------------------------\n");
	printf("| DADOS DO JOGADOR\n");
	printf("|\n");
	printf("| Nome   : %s\n", pJogador->nome);
	printf("| Energia: %d\n", pJogador->energia);
	printf("+------------------------------\n");*/

	int nLinhaInicio = 0;				//linha da consola
	int nColunaInicio = 7;				//coluna da consola

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	/*Guarda os atributos currentes do texto para reposiçãoo no final*/
	CONSOLE_SCREEN_BUFFER_INFO strConsoleInfo;
	GetConsoleScreenBufferInfo( hStdout, &strConsoleInfo );

	//define a posição do cursor na consula e imprime naquela posição
	COORD pos1 = {nColunaInicio, nLinhaInicio};
	SetConsoleCursorPosition( hStdout, pos1 );
	printf("********************************");
	//-----------------------------
	
	COORD pos2 = {nColunaInicio + 8, nLinhaInicio + 1};
	SetConsoleCursorPosition( hStdout, pos2 );

	/*Texto e fundo com cores*/
	SetConsoleTextAttribute( hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY  | BACKGROUND_INTENSITY );

	printf("DADOS DO JOGADOR");
	//-----------------------------

	COORD pos3 = {nColunaInicio, nLinhaInicio + 2};
	SetConsoleCursorPosition( hStdout, pos3 );

	SetConsoleTextAttribute( hStdout, strConsoleInfo.wAttributes );

	printf("*------------------------------*");
	//-----------------------------

	COORD pos4 = {nColunaInicio, nLinhaInicio + 3};
	SetConsoleCursorPosition( hStdout, pos4 );
	
	SetConsoleTextAttribute( hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);

	printf("* Nome      : %s", pJogador->nome);
	//----------------------------

	COORD pos5 = {nColunaInicio, nLinhaInicio + 4};
	SetConsoleCursorPosition( hStdout, pos5 );
	printf("* Energia   : %d", pJogador->energia);
	//----------------------------

	COORD pos6 = {nColunaInicio, nLinhaInicio + 5};
	SetConsoleCursorPosition( hStdout, pos6 );

	SetConsoleTextAttribute( hStdout, strConsoleInfo.wAttributes );

	printf("*");
	//----------------------------

	COORD pos7 = {nColunaInicio, nLinhaInicio + 6};
	SetConsoleCursorPosition( hStdout, pos7 );
	printf("*------------------------------*");

	COORD pos8 = {nColunaInicio, nLinhaInicio + 7};
	SetConsoleCursorPosition( hStdout, pos8 );
	printf("********************************");

	/*Repoe os atributos iniciais*/
	SetConsoleTextAttribute( hStdout, strConsoleInfo.wAttributes );
}

// Descreve monstro
void descreve_monstro(struct Monstro *pMonstro, struct Celula pMapa[], bool blnSuperUser)
{
	printf("+------------------------------\n");
	printf("| DESCRIÇÃO DOS MONSTROS\n");
	printf("|\n");
	printf("| %s   Energia:%d", pMonstro->nome, pMonstro->energia);

	int nLinhaInicio = 0;				//linha da consola
	int nColunaInicio = 38;				//coluna da consola

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//define a posição do cursor na consula e imprime naquela posição
	COORD pos1 = {nColunaInicio, nLinhaInicio};
	SetConsoleCursorPosition( hStdout, pos1 );
	printf("********************************");

	COORD pos2 = {nColunaInicio + 4, nLinhaInicio + 1};
	SetConsoleCursorPosition( hStdout, pos2 );
	printf("DESCRIÇÃO DOS MONSTROS");

	COORD pos3 = {nColunaInicio, nLinhaInicio + 2};
	SetConsoleCursorPosition( hStdout, pos3 );
	printf("*------------------------------*");

	COORD pos4 = {nColunaInicio, nLinhaInicio + 3};
	SetConsoleCursorPosition( hStdout, pos4 );
	printf("* Nome       : %s", pMonstro->nome);

	COORD pos5 = {nColunaInicio, nLinhaInicio + 4};
	SetConsoleCursorPosition( hStdout, pos5 );

	// se o monstro estiver morto informa que morreu
	if (pMonstro->energia <= 0)
	{
		printf("* Energia    : Morto");
	}
	else
	{
		printf("* Energia    : %d", pMonstro->energia);
	}

	// se o modo super user estiver activado mostra a sala do monstro
	if ( blnSuperUser == true )
	{
		// escreve a designação da sala se o monstro estiver vivo
		if (pMonstro->energia >= 0)
		{
			COORD pos6 = {nColunaInicio, nLinhaInicio + 5};
			SetConsoleCursorPosition( hStdout, pos6 );
			printf("* Localização: %s", pMapa[pMonstro->localizacao].descricao);
		}
	}
	else
	{
		COORD pos6 = {nColunaInicio, nLinhaInicio + 5};
		SetConsoleCursorPosition( hStdout, pos6 );
		printf("*", pMapa[pMonstro->localizacao].descricao);
	}

	COORD pos7 = {nColunaInicio, nLinhaInicio + 6};
	SetConsoleCursorPosition( hStdout, pos7 );
	printf("*------------------------------*");

	COORD pos8 = {nColunaInicio, nLinhaInicio + 7};
	SetConsoleCursorPosition( hStdout, pos8 );
	printf("********************************");
}

// Desenha no ecrã o que ocorre no jogo
void descreve_status(struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[], bool blnSuperUser)
{
	system("cls");							// limpa ecrã

	descreve_jogador(pJogador);

	printf("\n");
	printf("+------------------------------+\n");
	printf("|   DESCRIÇÃO DA LOCALIZAÇÃO   |\n");
	printf("|                              |\n");
	printf("| %s                       |\n", pMapa[pJogador->localizacao].descricao);
	printf("+------------------------------+\n");

	// se o modo superUser estiver activado mostra o status do monstro
	if (blnSuperUser == true)
	{
		descreve_monstro(pMonstro, pMapa, blnSuperUser);
	}

	printf("\n\n\n\n\n\n");
	
}

// Simula a luta entre jogador e monstro
int lutar(struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[], bool blnSuperUser)
{
	int MAX_DANO = 30;
	int iReturn = 1;
	int iHandyCap = 0;				// desvantagem do monstro

	// valida se o modo é superUser
	if (blnSuperUser == true)
	{
		iHandyCap = 10;
	}


	// descreve status
		system("cls");
		printf("+------------------------------\n");
		printf("| COMBATE\n");
		printf("+------------------------------\n");
		descreve_jogador(pJogador);
		descreve_monstro(pMonstro, pMapa, blnSuperUser);

	// imprime legenda
		printf("     @  - 1\n");
		printf("3 - /|\\ - 4\n");
		printf("    / \\ - 2\n");
		
	// solicita a posição para atacar (cima, baixo, esquerda, direita, foge)
		int iJogadorAtaque;
		printf("Qual a posição em que quer atacar?:");
		scanf( "%d", &iJogadorAtaque );


	// solicita a posição para defender
		int iJogadorDefesa;
		printf("Qual a posição em que quer defender?:");
		scanf( "%d", &iJogadorDefesa );

	// random de da posição onde o monstro defende/ataca
	// (cima, baixo, esquerda, direita, foge)
		int iMonstroAtaque = GetRandomNumber(0, 4);
		int iMonstroDefesa = GetRandomNumber(0, 4 + iHandyCap);
	
	// calcula dano
		int iDanoJogador = GetRandomNumber(1, MAX_DANO);
		int iDanoMonstro = GetRandomNumber(1, MAX_DANO - iHandyCap);

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
	printf("apanha_tesouro\n");
	// se exitir tesouro apanha-o
	printf("Localização do jogador: %d\n", pJogador->localizacao);
	system("pause");
	printf("Item do mapa: %d\n", pMapa[pJogador->localizacao].item);
	system("pause");

	/*int iLocalizacao = pJogador->localizacao;
	int iItem = pMapa[iLocalizacao].item;
*/

	if (pMapa[pJogador->localizacao].item == 0)
	{
		// define o jogador como tendo o tesouro
		pJogador->flg_tem_tesouro = 0;

		// retira o tesouro da célula
		pMapa[pJogador->localizacao].item = -1;

		// o tesouro foi apanhado
		printf("apanhou o tesouro retorna true\n");
		system("pause");
		return true;
	}


	printf("não tem tesouro retorna false\n");
	system("pause");
	// o tesouro não foi apanhado
	return false;
}

// valida os comandos disponíveis para o jogador
char* valida_comandos_disponiveis(struct Celula *pMapa)
{
	int MAX_CHARS = 200;
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

	// Opções funcionais
	// adiciona return
		strcat((char*) sComandosDisponiveis, "|\n");
	// Carregar Jogo
		strcat((char*) sComandosDisponiveis, "| C - Carregar Jogo\n");
	// Gravar Jogo
		strcat((char*) sComandosDisponiveis, "| G - Gravar Jogo\n");
	// Converte Mapa para binário
		strcat((char*) sComandosDisponiveis, "| B - Converter mapa para binário\n");

	return (char*) sComandosDisponiveis;
}

// valida switches
void validaSwitches(int argc, char* args[], bool *pSuperUser, char *pFicheiroMapa)
{
	bool godMode = false;

	for (int i = 1; i < argc; i++)
	{
		if ( strcmp(strupr(args[i]), "SU") == 0 ) { *pSuperUser = true; }			     // modo SuperUser
		if ( strcmp(strupr(args[i]), "M") == 0  ) { strcpy(pFicheiroMapa, args[i+1]); }  // faz load do mapa
	}
}

//	Se a Localização do Jogador for igual à do Monstro
void valida_condicoes_luta(struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[], bool blnSuperUser)
{
	if (pJogador->localizacao == pMonstro->localizacao)
	{
		// avisa o jogador que se encontra na mesma localização que o monstro e que tem de lutar
		printf("Há um monstro na sala... tens que lutar!!\n");
		system("pause");
		int iResultado = 1;

		// Lutar
		while (iResultado != 0)
		{
			// descreve status
			iResultado = lutar(pJogador, pMonstro, pMapa, blnSuperUser);
		}
	}
}

// carrega um jogo previamente gravado
void carrega_jogo(struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[])
{
	printf("carrega jogo\n");
	
	// lê cada linha do ficheiro
	#define MAX_COL 80
		
	FILE *f;
	char l[ MAX_COL ];

	// carrega o jogo com o nome do jogador
	char* sNomeFicheiro[50];
	strcpy((char*) sNomeFicheiro, (char*) pJogador->nome);
	f = fopen( strcat((char*) sNomeFicheiro, ".txt"), "r" );

	if ( f != NULL )
	{
		// lê o conteúdo do ficheiro
		while( fgets(l, MAX_COL, f) != NULL ){

			printf("entrou no ciclo\n");

			// se a linha for igual a mapa
			if (strcmp(strupr(trim(l)),":MAPA") == 0)
			{
				printf("encontrou a string :MAPA\n");
				system("pause");

				// carrega cada uma das células do mapa
				for (int i = 0; i < MAX_CELULAS; i++)
				{
					fgets(l, MAX_COL, f);
					strcpy((char*) pMapa[i].descricao, trim(l));		// nome da célula
					
					fgets(l, MAX_COL, f);
					pMapa[i].norte = atoi(l);							// norte

					fgets(l, MAX_COL, f);
					pMapa[i].sul = atoi(l);								// sul

					fgets(l, MAX_COL, f);
					pMapa[i].este = atoi(l);							// este

					fgets(l, MAX_COL, f);
					pMapa[i].oeste = atoi(l);							// oeste

					fgets(l, MAX_COL, f);
					pMapa[i].item = atoi(l);							// item
				}
			}

			// se a linha for igual a jogador
			if (strcmp(strupr(trim(l)),":JOGADOR") == 0)
			{
				printf("encontrou a string :JOGADOR\n");
				system("pause");
				
				fgets(l, MAX_COL, f);
				strcpy((char*) pJogador->nome, trim(l));				// nome do jogador

				fgets(l, MAX_COL, f);
				pJogador->energia = atoi (l);							// energia

				fgets(l, MAX_COL, f);
				pJogador->localizacao = atoi (l);						// localizacao

				fgets(l, MAX_COL, f);
				pJogador->flg_tem_tesouro = atoi (l);					// tesouro
			}

			// se a linha for igual a monstro
			if (strcmp(strupr(trim(l)),":MONSTRO") == 0)
			{
				printf("encontrou a string :MONSTRO\n");
				system("pause");

				fgets(l, MAX_COL, f);
				strcpy((char*) pMonstro->nome, trim(l));				// nome do monstro

				fgets(l, MAX_COL, f);
				pMonstro->energia = atoi (l);							// energia

				fgets(l, MAX_COL, f);
				pMonstro->localizacao = atoi (l);						// localizacao
			}
		}

		printf("saiu do ciclo\n");
		system("pause");
	
		fclose( f );
	}
	else
	{
		printf("Ficheiro de jogo inválido!\n");
		system("pause");
	}
}

// TODO: grava o estado actual do jogo
void grava_jogo(struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[])
{
	printf("grava jogo\n");

	// define as variaveis iniciais
	#define MAX_COL 80				// tamanho máximo da linha
	FILE *f;						// ficheiro
	char l[ MAX_COL ];				// linha
	char* sResposta[2];
	strcpy((char*) sResposta, "");
	
	// valida se já existe uma gravação
	char* sNomeFicheiro[50];
	strcpy((char*) sNomeFicheiro, (char*) pJogador->nome);
	
	// tenta abrir um ficheiro de gravação já existente
	f = fopen( strcat((char*) sNomeFicheiro, ".txt"), "r");

	if (f != NULL )
	{
		// se existir pergunta se deseja gravar por cima
		while (strcmp(strupr((char*) sResposta), "S") != 0 && strcmp(strupr((char*) sResposta), "N") != 0)
		{
			printf("Já existe um ficheiro de gravação para este utilizador, deseja gravar por cima?(S/N):");
			scanf( "%s", sResposta );
		}
	}

	if (strcmp(strupr((char*) sResposta), "S") == 0 || f == NULL )
	{
		// abre o ficheiro para escrita
		f = fopen((char*) sNomeFicheiro, "w");

		// grava estrutura do jogador
		//---------------------------
		fputs(":JOGADOR\n", f);											// cabeçalho :JOGADOR
		
		strcpy(l, trim((char*) pJogador->nome));						// nome
		strcat(l, "\n");
		fputs(l, f);

		itoa(pJogador->energia, l, 10);									// energia
		fputs(strcat(trim(l), "\n"), f);
		
		itoa(pJogador->localizacao, l, 10);								// localização
		fputs(strcat(trim(l), "\n"), f);
		
		itoa(pJogador->flg_tem_tesouro, l, 10);							// tesouro
		fputs(strcat(trim(l), "\n"), f);

		// grava estrutura do monstro
		//---------------------------
		fputs(":MONSTRO\n", f);											// cabeçalho :MONSTRO
		
		strcpy(l, trim((char*) pMonstro->nome));						// nome
		strcat(l, "\n");
		fputs(l, f);
		
		itoa(pMonstro->energia, l, 10);									// energia
		fputs(strcat(trim(l), "\n"), f);
		
		itoa(pMonstro->localizacao, l, 10);								// localização
		fputs(strcat(trim(l), "\n"), f);
		
		// grava estrutura do mapa
		//------------------------
		fputs(":MAPA\n", f);											// cabeçalho :MAPA

		// grava cada uma das células do mapa
		for (int i = 0; i < MAX_CELULAS; i++)
		{
			strcpy(l, trim((char*) pMapa[i].descricao));				// nome da célula
			strcat(l, "\n");
			fputs(l, f);
			
			itoa(pMapa[i].norte, l, 10);								// norte
			fputs(strcat(trim(l), "\n"), f);
			
			itoa(pMapa[i].sul, l, 10);									// sul
			fputs(strcat(trim(l), "\n"), f);
			
			itoa(pMapa[i].este, l, 10);									// este
			fputs(strcat(trim(l), "\n"), f);
			
			itoa(pMapa[i].oeste, l, 10);								// oeste
			fputs(strcat(trim(l), "\n"), f);
			
			itoa(pMapa[i].item, l, 10);									// item
			fputs(strcat(trim(l), "\n"), f);
		}

		// fecha o ficheiro
		fclose(f);
	}
}

// executa os comandos funcionais
void comandos_funcionais(int iAccao, struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[])
{
	printf("Comandos funcionais acção: %d\n", iAccao);
	system ("pause");
	// TODO: grava jogo
	if (iAccao == 100) {
		printf("Foi identificada a acção 100 grava jogo\n");
		system("pause");
		grava_jogo(pJogador, pMonstro, pMapa); 
	}
	// carrega jogo
	if (iAccao == 101) {
		printf("Foi identificada a acção 101 carrega jogo\n");
		system("pause");
		carrega_jogo(pJogador, pMonstro, pMapa);
	}

	// Converte mapa
	if (iAccao == 102) {
		printf("Foi identificada a acção 102 converte mapa\n");
		system("pause");
		converte_mapa();
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
	//Chama a função para validar os switches
	//--------------------------------
	bool blnSuperUser = false;						// define se está ou não no modo superuser
	char* ficheiroMapa[100];						// nome do ficheiro do mapa
	strcpy((char*) ficheiroMapa, "");

	validaSwitches(argc, argv, &blnSuperUser, (char*) ficheiroMapa);

	//--------------------------------
	//Chama a função para inicializar o jogador
	//--------------------------------

	struct Jogador jogador;
	//jogador = ( struct Jogador )malloc( sizeof ( struct Jogador ) );
	//struct jsw_node *rn = ( struct jsw_node*)malloc(sizeof(struct jsw_node));
	char * nomeJogador[50];
	// solicita o nome do jogador
	printf( "Indique o nome do jogador:" );
	scanf( "%s", &nomeJogador );

	inicializa_jogador(&jogador, (char *) nomeJogador, blnSuperUser );

	//--------------------------------
	//Chama a função para inicializar o mapa
	//--------------------------------
	struct Celula mapa[MAX_CELULAS];				//Cria um array de células para o mapa do jogo
	inicializa_mapa( mapa, (char *) ficheiroMapa );
	system("pause");

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
		int iAccao = -1;

		while (iAccao < 0)
		{
			//	Descrever a Localização do Jogador
			descreve_status(&jogador, &monstro, mapa, blnSuperUser);

			// valida se o monstro encontrou o jogador, se encontrou inicia a luta
			valida_condicoes_luta(&jogador, &monstro, mapa, blnSuperUser);
		
			//	Aceitar Comando do Jogador
			char* sComando[2];
			strcpy((char*) sComando, "");

			// validar/imprimir comandos disponíveis
			char* sComandosDisponiveis = valida_comandos_disponiveis(&mapa[jogador.localizacao]);
			printf("%s\n", sComandosDisponiveis);

			// solicita comando ao jogador
			printf("Insira um Comando: ");
			scanf( "%s", sComando );

			iAccao = aceita_comando_jogador((char*) sComando, &jogador, mapa);

			// se o comando for inválido dá mensagem de erro
			if (iAccao < 0)
			{
				printf("Comando inválido!\n");
				system("pause");
			}
		}

		//system("pause");
		printf ("Aceitou o Comando do Jogador %d\n", iAccao);

		// se a acção for igual ou superior a 100 é uma acção funcional
		if (iAccao >= 100)
		{
			printf("Comando funcional\n");
			system("pause");
	
			comandos_funcionais(iAccao, &jogador, &monstro, mapa);

			inicializa_mapa_teste (mapa);
			inicializa_jogador_teste (&jogador);
			inicializa_monstro_teste (&monstro);
		}
		else
		{
			//	Movimentar Monstro
			movimenta_monstro(&monstro, mapa);

			//	Movimentar Jogador
			movimenta_jogador(iAccao, &jogador);

			printf("Movimentou-se para a localização %d\n", iAccao);

			//  apanha o tesouro
			bool tesouro = apanha_tesouro(&jogador, mapa);

			if (tesouro == true)
			{
				printf("Apanhou o tesouro! %d\n", jogador.flg_tem_tesouro);
				system("pause");
			}

			// valida localizações para luta
			valida_condicoes_luta(&jogador, &monstro, mapa, blnSuperUser);
		}
	}

	// terminou o jogo
	system("cls");
	printf("____ _ _  _    ___  ____     _ ____ ____ ____   /\n");
	printf("|___ | |\/|    |  \ |  |     | |  | | __ |  |  / \n");
	printf("|    | |  |    |__/ |__|    _| |__| |__] |__| .  \n");
                                                 
	system( "pause" );
	return 0;
}

