// Bolsa.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <strsafe.h>
#include "utils.h"
#include "utils.c"


#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif

#define BUFFER_SIZE 1024
    

DWORD WINAPI leComandos(void* data) {
	wchar_t command[5];
	wchar_t company_name[100];
	int num_shares;
	double share_price;

	wchar_t texto[20];
	while (wcscmp(texto, L"sair") != 0) {

		printf_s("\nestou na thread!");
		fgetws(texto, sizeof(texto) / sizeof(wchar_t), stdin);
		wprintf_s(L"\n texto: %ls\n", texto);

		// se o utilizador escrever addc <nome-empresa> <numero_acoes> <preco_acao>
		if (wcscmp(L"addc\n", texto) == 0) {
			// le o nome da empresa
			
			
			printf_s("tetinhas ");

		}

		int num_matched = swscanf_s(texto, L"%4s %99s %d %lf", command, company_name, &num_shares, &share_price);
		printf_s("num_matched: %d\n", num_matched);

		

	}
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);


#pragma region mutex_garante_so_uma_instancia

	//verifica se é a primeira instancia e garante que só existe uma  
	// Criação de um mutex
	HANDLE hMutex = CreateMutex(NULL, TRUE, L"mutex_uma_instancia");

	// Verifica se o mutex já existe
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		printf("Já existe uma instância do programa em execução.\n");
		// Fecha o handle do mutex
		CloseHandle(hMutex);
		return 0;
	}
#pragma endregion


	//recebe o nome do ficheiro das contas como argumento
#pragma region Leficheiro

	if (argc < 2 || argc > 3) {
		_tprintf_s(_T("Número de argumentos incorreto.\n"));
		//CloseHandle(hMutex);
		//? comentado temporariamente!!!!!!!!!!!!
		// return 1; // Sai do programa com erro 
	//	wcscpy_s(argv[1], wcslen(L"teste") + 1, L"teste");// temporario tb
	}
	TCHAR nome_ficheiro_contas[20];
	//_tcscpy_s(nome_ficheiro_contas, argv[1]);
	_tcscpy_s(nome_ficheiro_contas, _T("contasUsers.txt"));
	LeUsers(nome_ficheiro_contas);
#pragma endregion


	//memória partilhada (nao testado)
	HANDLE hMapFile = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 256, L"BoardInfo");
	LPVOID address = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);

#pragma region REGISTRY

	//REGISTRY (nao testado) criação funciona, leitura funciona
	//tenta obter valor do registry, e se não existir escreve 5
	HKEY hKey;
	LPCWSTR nome_chave = L"Software\\Bolsa\\numUsers";
	LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, nome_chave, 0, KEY_ALL_ACCESS, &hKey);
	if (result != ERROR_SUCCESS) {
		// Se a chave não existe, criar e definir o valor para 5
		if (result == ERROR_FILE_NOT_FOUND) {
			result = RegCreateKeyExW(HKEY_LOCAL_MACHINE, nome_chave, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
			if (result != ERROR_SUCCESS) {
				printf_s("Erro ao criar a chave no Registro.");
				PrintErrorMessage(result);
				return 1;
			}
			DWORD valor = 5;
			result = RegSetValueExW(hKey, L"numUsers", 0, REG_DWORD, (BYTE*)(&valor), sizeof(DWORD));
			if (result != ERROR_SUCCESS) {
				printf_s("Erro ao definir o valor na chave do Registro.");
				RegCloseKey(hKey);
				return 1;
			}

		}
		else {
			printf_s("Erro ao abrir a chave no Registro.");
			return 1;
		}
	}
	else {
		DWORD tipo;
		DWORD valor=0;
		DWORD tamanho = sizeof(DWORD);
		result = RegQueryValueExW(hKey, L"numUsers", NULL, &tipo, (BYTE*)(&valor), &tamanho);
		if (result != ERROR_SUCCESS) {
			printf_s("Erro a ler valor do registry.");
			RegCloseKey(hKey);
			return 1;
		}
		// A chave já existe, não é necessário fazer nada
		_tprintf_s(L"Sucesso!\nNúmero de utilizadores permitidos: %d", valor);
		RegCloseKey(hKey);
	}

#pragma endregion



#pragma region Thread

	HANDLE thread = CreateThread(NULL, 0, leComandos, NULL, 0, NULL);
	if (thread) {
		// Optionally do stuff, such as wait on the thread.
	}


#pragma endregion







	printf_s("\nchegou ao sleep");
	Sleep(10000); // Aguarda 10 segundos





	// Ultimas ações antes de fechar o programa
	// Fecha o handle da memória partilhada
	CloseHandle(hMapFile);
	// Desmapeia a vista de memória do processo
	UnmapViewOfFile(address);
	// Fecha 
	CloseHandle(hMutex);

}



