//Descritivo:Primeiro trabalho de grupo da disciplina de SO
//Titulo:Jogo de Aventura
//Autores: Lu�s Costa N�6032, Bruno Moreira N�6170

#include "stdafx.h"
#include "string.h"
#include <ctime>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define MAX_CELULAS 3

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
	int		flg_tem_tesouro;	//Se o jogador tem ou n�o tesouro
};

//Celula
//---------------------
// lista de valores poss�veis
// **
// norte, sul, este, oeste
//		-1, porta inv�lida
//	   >=0, �n�mero da c�lula
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
	char	descricao[400];		//Descri��o da celula
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
//	FUN��ES
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
	printf( "Localiza��o:%d\n", pJogador->localizacao );
	printf( "Flag:%d\n", pJogador->flg_tem_tesouro );
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

	// percorre o ficheiro at� encontrar o fim
	while( fgets(l, MAX_LIN, f) != NULL ){

		// se o resto da divis�o do n�mero da linha pelo n�mero de linhas por c�lula
		// for igual a 0, quer dizer que � um novo registo
		if (iLinha % CAMPOS == 0)
		{
			// incrementa o indice
			iIndice = iIndice + 1;
		}

		// imprime a linha
		int iResto = iLinha % CAMPOS;

		switch ( iResto )
		{
			case 0:	// Descri��o
				strcpy(pMapa[iIndice].descricao, rtrim(l));
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

		// incrementa o n�mero da linha
		iLinha = iLinha + 1;
	}
	
	fclose( f );

	printf("concluiu a inicializa��o do mapa com base num ficheiro\n");
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

	// se o tamanho da string pFicheiroMapa for superior a 0 ent�o �
	// para carregar o mapa do ficheiro
	if (strlen(pFicheiroMapa) > 1)
	{
		printf("Inicializa Mapa %d\n", strlen(pFicheiroMapa));
		// carrega mapa do ficheiro
		inicializa_mapa_ficheiro(pMapa, pFicheiroMapa);
	}
	else
	{
		//Constru��o da sala 0
		//----------------------
		strcpy( pMapa[0].descricao, "Sala 0");
		pMapa[0].norte	= -1;
		pMapa[0].sul	= -1;
		pMapa[0].este	= 1;
		pMapa[0].oeste	= -1;
		pMapa[0].item	= -1;

		//Constru��o da sala 1
		//----------------------
		strcpy( pMapa[1].descricao, "Sala 1");
		pMapa[1].norte	= -1;
		pMapa[1].sul	= 4;
		pMapa[1].este	= -1;
		pMapa[1].oeste	= 0;
		pMapa[1].item	= -1;

		//Constru��o da sala 2
		//----------------------
		strcpy( pMapa[2].descricao, "Sala 2");
		pMapa[2].norte	= -1;
		pMapa[2].sul	= 5;
		pMapa[2].este	= -1;
		pMapa[2].oeste	= -1;
		pMapa[2].item	= -1;

		//Constru��o da sala 3
		//----------------------
		strcpy( pMapa[3].descricao, "Sala 3");
		pMapa[3].norte	= -1;
		pMapa[3].sul	= 6;
		pMapa[3].este	= 4;
		pMapa[3].oeste	= -1;
		pMapa[3].item	= -1;

		//Constru��o da sala 4
		//----------------------
		strcpy( pMapa[4].descricao, "Sala 4");
		pMapa[4].norte	= 1;
		pMapa[4].sul	= -1;
		pMapa[4].este	= 5;
		pMapa[4].oeste	= 3;
		pMapa[4].item	= -1;

		//Constru��o da sala 5
		//----------------------
		strcpy( pMapa[5].descricao, "Sala 5");
		pMapa[5].norte	= 2;
		pMapa[5].sul	= -1;
		pMapa[5].este	= -1;
		pMapa[5].oeste	= 4;
		pMapa[5].item	= 0;

		//Constru��o da sala 6
		//----------------------
		strcpy( pMapa[6].descricao, "Sala 6");
		pMapa[6].norte	= 3;
		pMapa[6].sul	= -1;
		pMapa[6].este	= 7;
		pMapa[6].oeste	= -1;
		pMapa[6].item	= -1;

		//Constru��o da sala 7
		//----------------------
		strcpy( pMapa[7].descricao, "Sala 7");
		pMapa[7].norte	= -1;
		pMapa[7].sul	= -1;
		pMapa[7].este	= 8;
		pMapa[7].oeste	= 6;
		pMapa[7].item	= -1;

		//Constru��o da sala 8
		//----------------------
		strcpy( pMapa[8].descricao, "Sala 8");
		pMapa[8].norte	= -1;
		pMapa[8].sul	= -1;
		pMapa[8].este	= -1;
		pMapa[8].oeste	= 7;
		pMapa[8].item	= -1;
	}
}

// testes da inicializa��o do mapa
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

// testes da inicializa��o do jogador
void inicializa_jogador_teste ( struct Jogador *pJogador )
{
	printf ("inicializa_jogador_teste\n");
	printf("Nome: %s\n", pJogador->nome);
	printf("Energia:   %d\n", pJogador->energia);
	printf("Localiza��o:  %d\n", pJogador->localizacao);
	printf("Tesouro: %d\n", pJogador->flg_tem_tesouro);
	system("pause");
}

// testes da inicializa��o do monstro
void inicializa_monstro_teste ( struct Monstro *pMonstro )
{
	printf ("inicializa_monstro_teste\n");
	printf("Nome: %s\n", pMonstro->nome);
	printf("Energia:   %d\n", pMonstro->energia);
	printf("Localiza��o:  %d\n", pMonstro->localizacao);
	system("pause");
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
	printf( "Localiza��o:%d\n", pMonstro->localizacao );
}

// Generate a random number between nLow and nHigh (inclusive)
unsigned int GetRandomNumber(int nLow, int nHigh)
{
	return (rand() % (nHigh - nLow + 1)) + nLow;
}

// movimenta o monstro
void movimenta_monstro(struct Monstro *pMonstro, struct Celula pMapa[])
{
	// faz random para decidir se movimenta ou n�o
	int iMovimenta = GetRandomNumber(0, 1);
	
	// � para movimentar
	if ( iMovimenta == 1 && pMonstro->localizacao != -1)
	{
		// verifica quais as sa�das existentes na localiza��o actual do monstro
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

		//printf("Sa�das: Norte:%d || Sul:%d || Este:%d || Oeste:%d\n", iNorte, iSul, iEste, iOeste);
		//printf("Localiza��o do Monstro Antes:%d\n", pMonstro->localizacao);

		// faz random das sa�das existentes
		int iNovaLocalizacao = iSaidas[GetRandomNumber(0, iPos)];

		// altera a localiza��o do monstro
		pMonstro->localizacao = iNovaLocalizacao;
		//printf("Localiza��o do Monstro Depois:%d\n", pMonstro->localizacao);
	}

}

// Aceita comando do jogador
int aceita_comando_jogador(char *sComando, struct Jogador *pJogador, struct Celula pMapa[])
{
	// valida a localiza��o do jogador
	int iLocalizacaoJogador = pJogador->localizacao;
	int iAccao = -1;

	// validar comandos dispon�veis
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

	// retorna o movimento que foi feito
	return iAccao;
}

// Movimenta ao jogador para a localiza��o pretendida
void movimenta_jogador(int iLocalizacao, struct Jogador *pJogador)
{
	// validar se o comando recebido est� nos comandos dispon�veis
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
void descreve_monstro(struct Monstro *pMonstro, struct Celula pMapa[], bool blnSuperUser)
{
	printf("+------------------------------\n");
	printf("| DESCRI��O DOS MONSTROS\n");
	printf("|\n");
	printf("| %s   Energia:%d", pMonstro->nome, pMonstro->energia);

	// se o modo super user estiver activado mostra a sala do monstro
	if ( blnSuperUser == true )
	{
		// escreve a designa��o da sala
		// se o monstro estiver morto informa que morreu
		if (pMonstro->energia <= 0)
		{
			printf("   Morto\n");
		}
		else
		{
			printf("   Localiza��o: %s\n", pMapa[pMonstro->localizacao].descricao);
		}
	}
	else
	{
		// muda de linha
		printf("\n");
	}

	printf("+------------------------------\n");
}

// Desenha no ecr� o que ocorre no jogo
void descreve_status(struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[], bool blnSuperUser)
{
	system("cls");							// limpa ecr�

	// descreve jogador
	descreve_jogador(pJogador);

	printf("+------------------------------\n");
	printf("| DESCRI��O DA LOCALIZA��O\n");
	printf("|\n");
	printf("| %s\n", pMapa[pJogador->localizacao].descricao);
	printf("+------------------------------\n");

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

	// valida se o modo � superUser
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
		
	// solicita a posi��o para atacar (cima, baixo, esquerda, direita, foge)
		int iJogadorAtaque;
		printf("Qual a posi��o em que quer atacar?:");
		scanf( "%d", &iJogadorAtaque );


	// solicita a posi��o para defender
		int iJogadorDefesa;
		printf("Qual a posi��o em que quer defender?:");
		scanf( "%d", &iJogadorDefesa );

	// random de da posi��o onde o monstro defende/ataca
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
			printf("Parab�ns! Matou o monstro %s!\n", pMonstro->nome);

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
	printf("Localiza��o do jogador: %d\n", pJogador->localizacao);
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

		// retira o tesouro da c�lula
		pMapa[pJogador->localizacao].item = -1;

		// o tesouro foi apanhado
		printf("apanhou o tesouro retorna true\n");
		system("pause");
		return true;
	}


	printf("n�o tem tesouro retorna false\n");
	system("pause");
	// o tesouro n�o foi apanhado
	return false;
}

// valida os comandos dispon�veis para o jogador
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

	// Op��es funcionais
	// adiciona return
		strcat((char*) sComandosDisponiveis, "|\n");
	// Carregar Jogo
		strcat((char*) sComandosDisponiveis, "| C - Carregar Jogo\n");
	// Gravar Jogo
		strcat((char*) sComandosDisponiveis, "| G - Gravar Jogo\n");

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

//	Se a Localiza��o do Jogador for igual � do Monstro
void valida_condicoes_luta(struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[], bool blnSuperUser)
{
	if (pJogador->localizacao == pMonstro->localizacao)
	{
		// avisa o jogador que se encontra na mesma localiza��o que o monstro e que tem de lutar
		printf("H� um monstro na sala... tens que lutar!!\n");
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

// TODO: carrega um jogo previamente gravado
void carrega_jogo(struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[])
{
	printf("carrega jogo\n");

	// l� cada linha do ficheiro
	#define MAX_COL 80
		
	FILE *f;
	char l[ MAX_COL ];

	// carrega o jogo com o nome do jogador
	f = fopen( strcat(pJogador->nome, ".txt"), "r" );

	if ( f != NULL )
	{
		// l� o conte�do do ficheiro
		while( fgets(l, MAX_COL, f) != NULL ){

			printf("entrou no ciclo\n");

			// se a linha for igual a mapa
			if (strcmp(strupr(trim(l)),":MAPA") == 0)
			{
				printf("encontrou a string :MAPA\n");
				system("pause");
				char ficheiroMapa[MAX_COL];						// nome do ficheiro do mapa
				strcpy(ficheiroMapa, "");				
				fgets(ficheiroMapa, MAX_COL, f);				// l� a linha seguinte que cont�m o nome do ficheiro que tem o mapa
				printf("nome do ficheiro :%s\n", ficheiroMapa);
				system("pause");
				strcpy(ficheiroMapa, trim(ficheiroMapa));
				inicializa_mapa_ficheiro(pMapa, ficheiroMapa);
			}

			// se a linha for igual a jogador
			if (strcmp(strupr(trim(l)),":JOGADOR") == 0)
			{
				printf("encontrou a string :JOGADOR\n");
				system("pause");
				
				//nome
				fgets(l, MAX_COL, f);
				strcpy(pJogador->nome, trim(l));
				//energia
				fgets(l, MAX_COL, f);
				pJogador->energia = atoi (l);
				//localizacao
				fgets(l, MAX_COL, f);
				pJogador->localizacao = atoi (l);
				//tesouro
				fgets(l, MAX_COL, f);
				pJogador->flg_tem_tesouro = atoi (l);
			}
			
				//jogador
				//d_nome
				//d_energia
				//d_localizacao
				//d_flg_tem_tesouro
			// se a linha for igual a monstro
			if (strcmp(strupr(trim(l)),":MONSTRO") == 0)
			{
				printf("encontrou a string :MONSTRO\n");
				system("pause");

				//nome
				fgets(l, MAX_COL, f);
				strcpy(pMonstro->nome, trim(l));
				//energia
				fgets(l, MAX_COL, f);
				pMonstro->energia = atoi (l);
				//localizacao
				fgets(l, MAX_COL, f);
				pMonstro->localizacao = atoi (l);
			}
		}

		printf("saiu do ciclo\n");
		system("pause");
	
		fclose( f );
	}
	else
	{
		printf("Ficheiro de jogo inv�lido!\n");
		system("pause");
	}
}

// executa os comandos funcionais
void comandos_funcionais(int iAccao, struct Jogador *pJogador, struct Monstro *pMonstro, struct Celula pMapa[])
{
	printf("Comandos funcionais ac��o: %d\n", iAccao);
	system ("pause");
	// TODO: carrega jogo
	//if (iAccao == 100) { grava_jogo(); };
	// grava jogo
	if (iAccao == 101) {
		printf("Foi identificada a ac��o 101 carrega jogo\n");
		system("pause");
		carrega_jogo(pJogador, pMonstro, pMapa);
	};
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
	//Chama a fun��o para validar os switches
	//--------------------------------
	bool blnSuperUser = false;						// define se est� ou n�o no modo superuser
	char* ficheiroMapa[100];						// nome do ficheiro do mapa
	strcpy((char*) ficheiroMapa, "");

	validaSwitches(argc, argv, &blnSuperUser, (char*) ficheiroMapa);

	//--------------------------------
	//Chama a fun��o para inicializar o jogador
	//--------------------------------
	struct Jogador jogador;
	char * nomeJogador[50];
	// solicita o nome do jogador
	printf( "Indique o nome do jogador:" );
	scanf( "%s", &nomeJogador );

	inicializa_jogador(&jogador, (char *) nomeJogador, blnSuperUser );

	//--------------------------------
	//Chama a fun��o para inicializar o mapa
	//--------------------------------
	struct Celula mapa[MAX_CELULAS];				//Cria um array de c�lulas para o mapa do jogo
	inicializa_mapa( mapa, (char *) ficheiroMapa );
	system("pause");

	//--------------------------------
	//Chama a fun��o para inicializar o monstro
	//--------------------------------
	struct Monstro monstro;
	inicializa_monstro( &monstro );

	//--------------------------------
	// Inicia o jogo
	//--------------------------------
	
	//Enquanto n�o for Fim de Jogo 
	while (jogador.energia > 0 && jogador.flg_tem_tesouro == -1)
	{
		int iAccao = -1;

		while (iAccao < 0)
		{
			//	Descrever a Localiza��o do Jogador
			descreve_status(&jogador, &monstro, mapa, blnSuperUser);

			// valida se o monstro encontrou o jogador, se encontrou inicia a luta
			valida_condicoes_luta(&jogador, &monstro, mapa, blnSuperUser);
		
			//	Aceitar Comando do Jogador
			char* sComando[2];
			strcpy((char*) sComando, "");

			// validar/imprimir comandos dispon�veis
			char* sComandosDisponiveis = valida_comandos_disponiveis(&mapa[jogador.localizacao]);
			printf("%s\n", sComandosDisponiveis);

			// solicita comando ao jogador
			printf("Insira um Comando: ");
			scanf( "%s", sComando );

			iAccao = aceita_comando_jogador((char*) sComando, &jogador, mapa);

			// se o comando for inv�lido d� mensagem de erro
			if (iAccao < 0)
			{
				printf("Comando inv�lido!\n");
				system("pause");
			}
		}

		//system("pause");
		printf ("Aceitou o Comando do Jogador %d\n", iAccao);

		// se a ac��o for igual ou superior a 100 � uma ac��o funcional
		if (iAccao >= 100)
		{
			printf("Comando funcional\n");
			system("pause");
			//TODO: chama fun��o de comandos funcionais
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
			printf("Movimentou-se para a localiza��o %d\n", iAccao);

			//  apanha o tesouro
			bool tesouro = apanha_tesouro(&jogador, mapa);

			//if (tesouro == true) { printf("Apanhou o tesouro! %d\n", jogador.flg_tem_tesouro); system("pause"); }

			// valida localiza��es para luta
			valida_condicoes_luta(&jogador, &monstro, mapa, blnSuperUser);
		}
	}

	printf("----O jogo terminou----");
	system( "pause" );
	return 0;
}

