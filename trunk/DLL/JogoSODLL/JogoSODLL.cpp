//Descritivo:Primeiro trabalho de grupo da disciplina de SO
//Titulo:DLL para o jogo de aventura
//Autores: Luís Costa Nº6032, Bruno Moreira Nº6170

#include "stdafx.h"
#include "JogoSODLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CJogoSODLLApp, CWinApp)
END_MESSAGE_MAP()


// CJogoSODLLApp construction

CJogoSODLLApp::CJogoSODLLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CJogoSODLLApp object

CJogoSODLLApp theApp;


// CJogoSODLLApp initialization

BOOL CJogoSODLLApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

__declspec( dllexport ) char* WINAPI rtrim(char *s)
{
	char* back = s + strlen(s);

    while(isspace(*--back));

    *(back+1) = '\0';

    return s;
}

__declspec( dllexport ) char * WINAPI ltrim(char *s)
{
	while(isspace(*s)) s++;
    return s;
}

__declspec( dllexport ) char * WINAPI trim(char *s)
{
	return rtrim(ltrim(s));
}

// Generate a random number between nLow and nHigh (inclusive)
__declspec( dllexport ) unsigned int WINAPI GetRandomNumber(int nLow, int nHigh)
{
	return (rand() % (nHigh - nLow + 1)) + nLow;
}

__declspec( dllexport ) void WINAPI converte_ficheiro()
{
	#define MAX_COL 400

	printf("A converter o ficheiro para binário...");
	system("pause");

	FILE *forigem;					// ficheiro de origem
	FILE *fdestino;					// ficheiro dedestino
	char l[ MAX_COL ];				// linha

	char* nomeMapaOrigem[100];						// nome do ficheiro do mapa
	char* nomeMapaDestino[100];

	strcpy((char*) nomeMapaOrigem, "");
	strcpy((char*) nomeMapaDestino, "");

	//Pede o nome do ficheiro do mapa a converte
	printf("Nome do ficheiro a converter (não indicar extensão):");
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
				printf("Dados:%s\n",l);
				system("pause");

				//grava a linha no ficheiro binário
				fwrite(l, sizeof(char), MAX_COL, fdestino);
			}

			fclose(fdestino);
		}
		else
		{
			printf("Erro a abrir/criar o ficheiro binário/n"); 
		}

		fclose(forigem);

		printf("Ficheiro convertido com sucesso!/n");
		system("pause");
	}
	else
	{
		printf("Erro a ler o ficheiro %s/n", nomeMapaOrigem);
	}
}