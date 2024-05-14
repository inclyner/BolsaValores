// utils.cpp
//
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "estruturas.h"


#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif

#define BUFFER_SIZE 1024



Utilizador LeUsers(TCHAR* filename) {
	//abrir ficheiro criar e inserir users na lista ligada
	HANDLE hFile;
	DWORD bytesRead;
	TCHAR buffer[BUFFER_SIZE];



	// Abre o arquivo para leitura
	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("Erro ao abrir o arquivo.\n"));
	}

	// Lê o conteúdo do arquivo
	if (!ReadFile(hFile, buffer, BUFFER_SIZE, &bytesRead, NULL)) {
		_tprintf(_T("Erro ao ler o arquivo.\n"));
		CloseHandle(hFile);
	}

	// Fecha o arquivo
	CloseHandle(hFile);

	// Imprime o conteúdo lido
	_tprintf(_T("Conteúdo do arquivo:\n%s\n"), buffer);
	Utilizador a;
	return a;

}




void PrintErrorMessage(DWORD errorCode) {
	LPWSTR buffer = NULL;
	FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&buffer,
		0,
		NULL);
	if (buffer != NULL) {
		_tprintf(_T("Erro: %s\n"), buffer);
		LocalFree(buffer);
	}
	else {
		_tprintf(_T("Erro desconhecido ocorreu.\n"));
	}
}


// Função para criar um novo nó com um Utilizador
Utilizador* criarUtilizador(const TCHAR* username, const TCHAR* password, double saldo) {
	Utilizador* novoUtilizador = (Utilizador*)malloc(sizeof(Utilizador));
	if (novoUtilizador != NULL) {
		_tcscpy_s(novoUtilizador->username, _countof(novoUtilizador->username), username);
		_tcscpy_s(novoUtilizador->password, _countof(novoUtilizador->password), password);

		novoUtilizador->saldo = saldo;
		novoUtilizador->proximo = NULL; // Defina o próximo como NULL
	}
	return novoUtilizador;
}


// Função para inserir um novo Utilizador no final da lista
void inserirUtilizador(Utilizador** lista, Utilizador* novoUtilizador) {
	if (*lista == NULL) {
		*lista = novoUtilizador;
	}
	else {
		Utilizador* atual = *lista;
		while (atual->proximo != NULL) {
			atual = atual->proximo;
		}
		atual->proximo = novoUtilizador;
	}
}