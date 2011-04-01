//Descritivo:Primeiro trabalho de grupo da disciplina de SO
//Titulo:Jogo de Aventura
//Autores: Luís Costa Nº6032, Bruno Moreira Nº6170

#include "stdafx.h"
#include "stdio.h"
#include "string.h"

#define MAX_CELULAS 9

//--------Estruturas-----------
//-----------------------------

//Jogador
//---------------------
struct Jogador
{
	char*	nome[50];			//Nome do jogador
	int		energia;			//Energia do jogador
	int		localizacao;		//Celula onde o jogador se encontra
	int		flg_tem_tesouro;	//Se o jogador tem ou não tesouro
}

//Celula
//---------------------
struct Celula
{
	int		norte;				//Qual a celula a norte
	int		sul;				//Qual a celula a sul
	int		este;				//Qual a celula a este
	int		oeste;				//Qual a celula a oeste
	char	descricao[400];		//Descrição da celula
	int		item;				//Item	que existe na celula
}

//Monstro
//---------------------
struct Monstro
{
	char*	nome[50];
	int		energia;			//Energia do jogador
	int		localizacao;		//Celula onde o jogador se encontra

}

//Inicializa o mapa da aventura
//--------------------------------
void inicializa_mapa(struct Celula mapa[])
{
	int n;

	//Construção da sala 0
	//----------------------
	strcpy(mapa[0].descricao, "Sala 0");
	mapa[0].norte = -1;
	mapa[0].sul = -1;
	mapa[0].este = 1;
	mapa[0].oeste = -1;
	mapa[0].item = -1;
}

int main(int argc, _TCHAR* argv[])
{
	//Chama a função para inicializar o mapa
	//--------------------------------
	struct Celula mapa[MAX_CELULAS];				//Cria um array de células para o mapa do jogo
	inicializa_mapa(mapa);

	return 0;
}

