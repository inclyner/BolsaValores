// Bolsa.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <strsafe.h>
#include <fcntl.h>  // Para _O_WTEXT
#include <io.h>     // Para _setmode
#include "utils.h"
#include "utils.c"



#ifdef _UNICODE
typedef wchar_t TCHAR;
#include <wchar.h>  // Para funções wide-char (w_tprintf, wscanf, etc.)
#else
typedef char TCHAR;
#endif

#define BUFFER_SIZE 1024



    

DWORD WINAPI leComandos(void* data) {
	wchar_t command[5];
	wchar_t company_name[100];
	int num_shares;
	double share_price;
	int IsLeaving = 0;

	wchar_t texto[20];

	while (IsLeaving == 0) {

		TCHAR command[250];
		TCHAR* cmd[102];
		TCHAR* token;
		int i = 0;

		_tprintf(_T("Comando: "));
		_fgetts(command, sizeof(command) / sizeof(command[0]), stdin);

		TCHAR* cmd_Dup = _tcsdup(command);

		token = _tcstok_s(cmd_Dup, _T(" "), &cmd_Dup);
		while (token != NULL) {
			cmd[i] = _tcsdup(token); // Use _tcsdup for TCHAR strings
			i++;
			token = _tcstok_s(NULL, _T(" "), &cmd_Dup);
		}

		if (_tcsstr(command, _T("addc")) != NULL) { 
			if (i == 4 ) {
				_tprintf(_T("Entrou no addc\n"));
				_tprintf(_T("1: %s,2: %s, 3 : %s"), cmd[1], cmd[2], cmd[3]);
			}
			else {
				_tprintf(_T("O comando não contém os parâmetros respetivos\n"));
			}
		}
		else if (_tcsstr(command, _T("listc")) != NULL) {
			if (i == 1) {
				_tprintf(_T("Entrou no listc\n"));
			}
			else {
				_tprintf(_T("O comando não contém os parâmetros respetivos\n"));
			}
		}
		else if (_tcsstr(command, _T("stock ")) != NULL) {
			if (i == 2) {
				_tprintf(_T("Entrou no stock \n"));
			}
			else {
				_tprintf(_T("O comando não contém os parâmetros respetivos\n"));
			}
		}
		else if (_tcsstr(command, _T("users")) != NULL) {
			if (i == 1) {
				_tprintf(_T("Entrou no users\n"));
			}
			else {
				_tprintf(_T("O comando não contém os parâmetros respetivos\n"));
			}
		}
		else if (_tcsstr(command, _T("pause")) != NULL) {
			if (i == 2) {
				_tprintf(_T("Entrou no pause\n"));
			}
			else {
				_tprintf(_T("O comando não contém os parâmetros respetivos\n"));
			}
		}
		else if (_tcsstr(command, _T("close")) != NULL) {
			if (i == 1) {
				_tprintf(_T("Entrou no close\n"));
			}
			else {
				_tprintf(_T("O comando não contém os parâmetros respetivos\n"));
			}
		}
		else {
			_tprintf(_T("Comando Inexistente \n"));
		}

	}

		int num_matched = swscanf_s(texto, L"%4s %99s %d %lf", command, company_name, &num_shares, &share_price);
		_tprintf_s(_T("num_matched: %d\n"), num_matched);

		

	
	return 0;
}

int _tmain(int argc, TCHAR* argv[])
{

#ifdef UNICODE
_setmode(_fileno(stdin), _O_WTEXT);
_setmode(_fileno(stdout), _O_WTEXT);
#endif

	





#pragma region mutex_garante_so_uma_instancia

	//verifica se é a primeira instancia e garante que só existe uma  
	// Criação de um mutex
	HANDLE hMutex = CreateMutex(NULL, TRUE, L"mutex_uma_instancia");

	// Verifica se o mutex já existe
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		_tprintf(_T("Já existe uma instância do programa em execução.\n"));
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
				_tprintf_s(_T("Erro ao criar a chave no Registro."));
				PrintErrorMessage(result);
				return 1;
			}
			DWORD valor = 5;
			result = RegSetValueExW(hKey, L"numUsers", 0, REG_DWORD, (BYTE*)(&valor), sizeof(DWORD));
			if (result != ERROR_SUCCESS) {
				_tprintf_s(_T("Erro ao definir o valor na chave do Registro."));
				RegCloseKey(hKey);
				return 1;
			}

		}
		else {
			_tprintf_s(_T("Erro ao abrir a chave no Registro."));
			return 1;
		}
	}
	else {
		DWORD tipo;
		DWORD valor=0;
		DWORD tamanho = sizeof(DWORD);
		result = RegQueryValueExW(hKey, L"numUsers", NULL, &tipo, (BYTE*)(&valor), &tamanho);
		if (result != ERROR_SUCCESS) {
			_tprintf_s(_T("Erro a ler valor do registry."));
			RegCloseKey(hKey);
			return 1;
		}
		// A chave já existe, não é necessário fazer nada
		_tprintf_s(_T("Sucesso!\nNúmero de utilizadores permitidos: %d"), valor);
		RegCloseKey(hKey);
	}

#pragma endregion



#pragma region Thread

	HANDLE thread = CreateThread(NULL, 0, leComandos, NULL, 0, NULL);
	if (thread) {
		// Optionally do stuff, such as wait on the thread.
	}


#pragma endregion







	_tprintf_s(_T("\nchegou ao sleep"));
	Sleep(100000); // Aguarda 100 segundos





	// Ultimas ações antes de fechar o programa
	// Fecha o handle da memória partilhada
	CloseHandle(hMapFile);
	// Desmapeia a vista de memória do processo
	UnmapViewOfFile(address);
	// Fecha 
	CloseHandle(hMutex);

}



