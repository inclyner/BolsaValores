// Client.c : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif

#define BUFFER_SIZE 1024



int _tmain(int argc, TCHAR* argv[])
{

	// Criar Pipe?
    int IsLogged = 0;
    int IsLeaving = 0;

    #pragma region LoginForm
    do {

        TCHAR login_input[250];
        TCHAR* login_info[102];
        TCHAR* token;
        int i = 0;
        int IsLoging = 0;
        
        _tprintf(_T("Insira o Comando que pretende utilizar (login ou exit)\n"));
        _tprintf(_T("Comando Login -> login username password\n\n"));
        _tprintf(_T("Comando: "));
        _fgetts(login_input, sizeof(login_input) / sizeof(login_input[0]), stdin);

        TCHAR* login_Dup = _tcsdup(login_input);

        token = _tcstok_s(login_Dup, _T(" "), &login_Dup);
        while (token != NULL) {
            login_info[i] = _tcsdup(token); // Use _tcsdup for TCHAR strings
            i++;
            token = _tcstok_s(NULL, _T(" "), &login_Dup);
        }

        if (_tcsstr(login_input, _T("login")) != NULL) {
            if (i == 3) {

                _tprintf(_T("Username: %s\n"), login_info[1]);
                _tprintf(_T("Password: %s\n"), login_info[2]);
                IsLoging = 1;
            }
            else
                _tprintf(_T("Comando de Login com parâmetros em falta.\n"));
        }
        else if (_tcsstr(login_input, _T("exit")) != NULL) {
            _tprintf(_T("Obrigado por ter entrado no nosso programa de cliente.\n"));
            IsLogged = 1;
            IsLeaving = 1;
        }
        else {
            _tprintf(_T("Comando Inexistente ou sem acesso a ele\n"));
        }

        if (IsLoging == 1) {
            // Envia Dados pelo PIPE

            // Recebe Resposta

            TCHAR resposta[250];
            if (_tcsstr(resposta, _T("Sucesso")) != NULL) { // Sucesso e Entrou logo
                _tprintf(_T("Utilizador Logado com Sucesso\n"));
                IsLogged = 1;
            }
            else if (_tcsstr(resposta, _T("Erro")) != NULL) {
                _tprintf(_T("Autenticação Falhada - Erro no Login\n")); // Enviar se foi erro de Utilizador ou Password?
            }
            else { // Sucesso mas foi para Lista de Espera
                _tprintf(_T("Foi colocado na Lista de Espera\n"));

                // Thread? //Check se pode entrar

                _tprintf(_T("Escreva o Comando (exit) se pretender sair, senão aguarde até conseguir entrar: "));
                _fgetts(login_input, sizeof(login_input) / sizeof(login_input[0]), stdin);

                if (_tcsstr(login_input, _T("exit")) != NULL) {
                    IsLogged = 1;
                    IsLeaving = 1;
                }
            }

            memset(resposta, 0, sizeof(resposta));
        }

        memset(login_input, 0, sizeof(login_input));
        memset(login_info, 0, sizeof(login_info));
        memset(login_Dup, 0, sizeof(login_Dup));

    } while (IsLogged == 0);
    #pragma endregion



    #pragma region Commands
    while (IsLeaving == 0){

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

        if (_tcsstr(command, _T("listc")) != NULL) { //comando players
            if (i == 1) {
                _tprintf(_T("Entrou no listc\n"));
            }
            else {
                _tprintf(_T("O comando não contém os parâmetros respetivos\n"));
            }
        }
        else if (_tcsstr(command, _T("buy")) != NULL) { //comando buy
            if (i == 3) {
                _tprintf(_T("Entrou no buy\n"));
            }
            else {
                _tprintf(_T("O comando não contém os parâmetros respetivos\n"));
            }
        }
        else if (_tcsstr(command, _T("sell")) != NULL) { //comando sell
            if (i == 3) {
                _tprintf(_T("Entrou no sell\n"));
            }
            else {
                _tprintf(_T("O comando não contém os parâmetros respetivos\n"));
            }
        }
        else if (_tcsstr(command, _T("balance")) != NULL) { //comando balance
            if (i == 1) {
                _tprintf(_T("Entrou no balance\n"));
            }
            else {
                _tprintf(_T("O comando não contém os parâmetros respetivos\n"));
            }
        }
        else if (_tcsstr(command, _T("exit")) != NULL) { //comando exit
            if (i == 1) {
                IsLeaving = 1;
            }
        }
        else {
            _tprintf(_T("Comando Inexistente \n"));
        }

        // Limpa os Strings, para evitar lixo no loop do ciclo
        memset(cmd, 0, sizeof(cmd));
        memset(command, 0, sizeof(command));
        memset(cmd_Dup, 0, sizeof(cmd_Dup));

	};
    #pragma endregion


    _tprintf(_T("O programa vai encerrar..."));
}