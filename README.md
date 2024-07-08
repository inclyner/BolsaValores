# Online Stock Exchange

## Operating Systems 2 – 2023 / 2024
ISEC - Bachelor in Computer Engineering

### Authors:
- Francisco Andrade Carvalho – 2019129635
- Gabriel Fontes – 2019130292

---

## Index

1. [Introduction](#introduction)
2. [General Program Architecture](#general-program-architecture)
3. [Data Structures](#data-structures)
    - [Client Structures](#client-structures)
    - [Stock Exchange Structures](#stock-exchange-structures)
    - [Board Structures](#board-structures)
4. [General Application Functionality](#general-application-functionality)
5. [Implemented Requirements](#implemented-requirements)

---

## Introduction

In this repository, we present the Online Stock Exchange project, developed for the Operating Systems 2 course in the academic year 2023/2024. This report describes the general program architecture, the data structures used, the general functionality of the application, and the implemented requirements.

## General Program Architecture

The program architecture consists of three main modules:
- Client
- Stock Exchange
- Board

## Data Structures

### Client Structures

In the Client program, we have two main structures:
- `InfoLogin`: Contains two `TCHAR` (username and password) of size 20. It is used to send login information to the Pipe.
- `Comando`: Contains two integers (`comando` and `numAcoes`), and a `TCHAR` (company) of size 25. It is used to send client commands to the stock exchange through the pipe.

### Stock Exchange Structures

In the Stock Exchange program, we have a total of seven main structures:
- `Acoes`: Contains a `TCHAR` (company) of size 25 and an `int` (quantity). It supports the `Utilizador` structure.
- `Utilizador`: Contains two `TCHAR` (username and password), a `double` (balance), an array of `Acoes` (carteira_acoes) of size 100, and four `int` (estado, threadId, user_valid, numCartAcoes). It is responsible for creating the list of users.
- `Empresa`: Contains a `TCHAR` (name) of size 25, an `int` (num_acoes), and a `double` (preco_atual). It creates the list of companies.
- `InfoLogin` and `Comando`: Also implemented in the Stock Exchange program for the same functions as in the Client.
- `InfoThreads`: Stores pointers to lists and variables used in the different Threads of the program.
- `InfoSM`: Stores the latest transactions of each client to shared memory, used by the Board program.

### Board Structures

In the Board program, we have two main structures:
- `Empresa`: Same as the structure used in the Stock Exchange program.
- `InfoSM`: Used to read data from shared memory and display it on the Board.

## General Application Functionality

### Client

The Client program uses only the `main` function to operate, without the use of threads. Each client tries to connect to a Pipe instance, performs login, sends commands, receives responses, and repeats the cycle until termination.

### Stock Exchange

The Stock Exchange program uses threads to manage events. One thread is for the Administrator to enter commands and make changes, while another creates the Pipe and its instances, creating a new thread for communication with each connected Client.

### Board

The Board program reads shared memory with the help of mutexes and displays the existing companies to the user.

## Implemented Requirements

| ID  | Description Functionality / Requirement                       | Status              |
|-----|---------------------------------------------------------------|---------------------|
| 1   | Stock Exchange: Receive client file as argument                | Implemented         |
| 2   | Stock Exchange: Have only one execution                       | Implemented         |
| 3   | Stock Exchange: Register NCLIENTES in Registry                | Implemented         |
| 4   | Stock Exchange: Only 1 user interacting with commands         | Implemented         |
| 5   | Stock Exchange: Command: addc                                 | Implemented         |
| 6   | Stock Exchange: Command: listc                                | Implemented         |
| 7   | Stock Exchange: Command: stock                                | Implemented         |
| 8   | Stock Exchange: Command: pause                                | Not Implemented     |
| 9   | Stock Exchange: Command: close                                | Not Implemented     |
| 10  | Stock Exchange: Command: loadcompanies                        | Implemented         |
| 11  | Client: Communicate with Stock Exchange                       | Implemented         |
| 12  | Client: Command: login                                        | Implemented         |
| 13  | Client: Command: listc                                        | Implemented         |
| 14  | Client: Command: buy                                          | Implemented         |
| 15  | Client: Command: sell                                         | Implemented         |
| 16  | Client: Command: balance                                      | Implemented         |
| 17  | Client: Command: wallet                                       | Implemented         |
| 18  | Client: Command: help                                         | Implemented         |
| 19  | Client: Command: exit                                         | Implemented         |
| 20  | Stock Exchange: Only NCLIENTES can be logged in               | Implemented         |
| 21  | Stock Exchange and Client: Interact using named pipes         | Implemented         |
| 22  | Stock price variation                                         | Implemented         |
| 23  | Write and Read from Shared Memory                             | Implemented         |
| 24  | Board                                                         | Semi-Implemented    |
