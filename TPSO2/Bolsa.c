// Bolsa.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "utils.c"


#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif

#define BUFFER_SIZE 1024



int _tmain(int argc, TCHAR* argv[])
{
	//verifica se � a primeira instancia e garante que s� existe uma  
	// Cria��o de um mutex
	HANDLE hMutex = CreateMutex(NULL, TRUE, "mutex_uma_instancia");

	// Verifica se o mutex j� existe
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		printf("J� existe uma inst�ncia do programa em execu��o.\n");
		// Fecha o handle do mutex
		CloseHandle(hMutex);
		return 0;
	}



	//recebe o nome do ficheiro das contas como argumento
	if (argc < 2 || argc > 3) {
		printf_s("N�mero de argumentos incorreto.\n");
		//CloseHandle(hMutex);
		//? comentado temporariamente!!!!!!!!!!!!
		// return 1; // Sai do programa com erro 
	//	wcscpy_s(argv[1], wcslen(L"teste") + 1, L"teste");// temporario tb
	}
	TCHAR nome_ficheiro_contas[20];
	//_tcscpy_s(nome_ficheiro_contas, argv[1]);
	_tcscpy_s(nome_ficheiro_contas, _T("contasUsers.txt"));

	LeUsers(nome_ficheiro_contas);





	//mem�ria partilhada (nao testado)
	HANDLE hMapFile = CreateFileMappingW(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 256, L"BoardInfo");
	LPVOID address = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);


	//REGISTRY (nao testado) cria��o funciona, leitura funciona
	//tenta obter valor do registry, e se n�o existir escreve 5
	HKEY hKey;
	LPCWSTR nome_chave = L"Software\\Bolsa\\numUsers";
	LPCSTR nome_chave2 = "Software\\Bolsa\\numUsers";
	LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, nome_chave, 0, KEY_ALL_ACCESS, &hKey);
	if (result != ERROR_SUCCESS) {
		// Se a chave n�o existe, criar e definir o valor para 5
		if (result == ERROR_FILE_NOT_FOUND) {
			result = RegCreateKeyEx(HKEY_LOCAL_MACHINE, nome_chave2, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
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
		// A chave j� existe, n�o � necess�rio fazer nada
		printf_s("Sucesso!\nN�mero de utilizadores permitidos: %d", valor);
		RegCloseKey(hKey);
	}











	printf_s("\nchegou ao sleep");
	Sleep(10000); // Aguarda 10 segundos





	// Ultimas a��es antes de fechar o programa
	// Fecha o handle da mem�ria partilhada
	CloseHandle(hMapFile);
	// Desmapeia a vista de mem�ria do processo
	UnmapViewOfFile(address);
	// Fecha 
	CloseHandle(hMutex);

}

