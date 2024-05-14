#pragma once


#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H


#ifdef _UNICODE
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif


struct Acoes {
    TCHAR username[20];
    int quantidade;
    int qnt_em_espera;
} Acoes;

typedef struct Utilizador {
    TCHAR username[20];
    TCHAR password[20];
    double saldo;
    struct Acoes carteira_acoes[100];
    int pipefd[2];
    struct Utilizador* proximo; // Ponteiro para o próximo user
} Utilizador;


struct Empresa {
    char nome[50];
    int num_acoes;
    float preco_atual;
};

#endif // ESTRUTURAS_H