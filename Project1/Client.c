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
        
        printf_s("Insira o Comando que pretende utilizar (login ou exit)\n");
        printf_s("Comando Login -> login username password\n\n");
        printf_s("Comando: ");
        fgets(login_input, sizeof(login_input), stdin);

        TCHAR* login_Dup = strdup(login_input);

        token = strtok_s(login_Dup, " ", &login_Dup);
        while (token != NULL) {
            login_info[i] = _strdup(token); // Allocate memory and copy token
            i++;
            token = strtok_s(NULL, " ", &login_Dup);
        };

        if (strstr(login_input, "login") != NULL) {
            if (i == 3) {
                TCHAR username = login_info[1];
                TCHAR passwrod = login_info[2];
            }
            else
                printf_s("Comando de Login com parametros em falta.");
        }
        else if (strstr(login_input, "sair") != NULL) {
            printf_s("Obrigado por ter entrado no nosso Client side.");
            IsLogged = 1;
            IsLeaving = 1;
        }
        else {
            printf("Comando Inexistente ou sem acesso a ele");
        }


        // Envia Dados pelo PIPE

        // Recebe Resposta

        TCHAR resposta[250];
        if (strstr(resposta, "Sucesso") != NULL) { // Sucesso e Entrou logo
            printf_s("Utilizador Logado com Sucesso");
            IsLogged = 1;
        }
        else if (strstr(resposta, "Erro") != NULL) {
            printf_s("Autenticação Falhada - Erro no Login "); // Enviar se foi erro de Utilizador ou Password?
        }
        else { // Sucesso mas foi para Lista de Espera
            printf_s("Foi colocado na Lista de Espera");

            // Thread? //Check se pode entrar

            printf_s("Escreva o Comando (exit) se pretender sair : ");
            fgets(login_input, sizeof(login_input), stdin);

            if (strstr(resposta, "exit") != NULL) {
                IsLogged = 1;
                IsLeaving = 1;
            }
        }

        memset(login_input, 0, sizeof(login_input));
        memset(login_info, 0, sizeof(login_info));
        memset(login_Dup, 0, sizeof(login_Dup));
        memset(resposta, 0, sizeof(resposta));

    } while (IsLogged == 0);
    #pragma endregion



    #pragma region Commands
    while (IsLeaving == 0){

        TCHAR command[250];
        TCHAR* cmd[102];
        TCHAR* token;
        int i = 0;

        printf_s("Comando: ");
        fgets(command, sizeof(command), stdin);

        TCHAR* cmd_Dup = strdup(command);

        token = strtok_s(cmd_Dup, " ", &cmd_Dup);
        while (token != NULL) {
            cmd[i] = _strdup(token); // Allocate memory and copy token
            i++;
            token = strtok_s(NULL, " ", &cmd_Dup);
        };

        if (strstr(command, "listc") != NULL) { //comando players
            if (i == 1) {
                printf_s("Entrou no listc\n");
            }
            else {
                printf_s("O comando não contém os parâmetros respetivos\n");
            }
        }
        else if (strstr(command, "buy") != NULL) { //comando buy
            if (i == 3) {
                printf_s("Entrou no buy\n");
            }
            else {
                printf_s("O comando não contém os parâmetros respetivos\n");
            }
        }
        else if (strstr(command, "sell") != NULL) { //comando sell
            if (i == 3) {
                printf_s("Entrou no sell\n");
            }
            else {
                printf_s("O comando não contém os parâmetros respetivos\n");
            }
        }
        else if (strstr(command, "balance") != NULL) { //comando balance
            if (i == 1) {
                printf_s("Entrou no balance\n");
            }
            else {
                printf_s("O comando não contém os parâmetros respetivos\n");
            }
        }
        else if (strstr(command, "exit") != NULL) { //comando exit
            if (i == 1) {
                IsLeaving = 1;
            }
        }
        else {
            printf_s("Comando Inexistente \n");
        }

        // Limpa os Strings, para evitar lixo no loop do ciclo
        memset(cmd, 0, sizeof(cmd));
        memset(command, 0, sizeof(command));
        memset(cmd_Dup, 0, sizeof(cmd_Dup));

	};
    #pragma endregion


    printf_s("O programa vai encerrar...");
}