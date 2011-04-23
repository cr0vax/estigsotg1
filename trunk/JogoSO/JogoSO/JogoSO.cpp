//Descritivo:Primeiro trabalho de grupo da disciplina de SO
//Titulo:Jogo de Aventura
//Autores: Luís Costa Nº6032, Bruno Moreira Nº6170

#include "stdafx.h"
#include "string.h"
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
	for (int i = 0; i < MAX_CELULAS; i++) {
		printf("[%s]\n", pMapa[i].descricao);
		printf("Norte: %d\n", pMapa[i].norte);
		printf("Sul:   %d\n", pMapa[i].sul);
		printf("Este:  %d\n", pMapa[i].este);
		printf("Oeste: %d\n", pMapa[i].oeste);
		printf("Item:  %d\n\n", pMapa[i].item);
	}
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

int main(int argc, _TCHAR* argv[])
{
	setlocale( LC_ALL, "Portuguese" );

	//--------------------------------
	//Chama a função para inicializar o jogador
	//--------------------------------
	struct Jogador jogador;
	char * nomeJogador[50];
	// solicita o nome do jogador
	printf( "Indique o nome:" );
	scanf( "%s", &nomeJogador );

	inicializa_jogador(&jogador, (char *) nomeJogador, true );

	//--------------------------------
	//Chama a função para inicializar o mapa
	//--------------------------------
	struct Celula mapa[MAX_CELULAS];				//Cria um array de células para o mapa do jogo
	inicializa_mapa( mapa );

	//--------------------------------
	//Chama a função para inicializar o monstro
	//--------------------------------
	struct Monstro monstro;
	inicializa_monstro( &monstro );

	//--------------------------------
	//TODO: Inicia o jogo
	//--------------------------------
		//Enquanto não for Fim de Jogo 
		//
		//{
		//	Movimentar Monstro
		//	Descrever a Localização do Jogador
		//	Aceitar Comando do Jogador
		//	Movimentar Jogador
		//		Se a Localização do Jogador for igual à do Monstro
		//			Lutar 
		//}
		//
		//Apresentar Resultado Final

	system( "pause" );
	return 0;
}

