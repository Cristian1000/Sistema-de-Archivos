#ifndef GLOBAL_H
#define GLOBAL_H
#include <cstdio>
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

struct Token{
    int numero;
    string nombre;
};

struct Nodo{
    Token lexema;
    Nodo *sig = NULL;
};

struct Particion
{
    char status = 'N';
    char tipe;
    char fit[2];
    int start = 0;
    int size = 0;
    char nombre[16];
};

struct EBR
{
    char status = 'N';
    char fit[2];
    int start = 0;
    int size;
    int next = -1;
    char nombre[16];
};

struct MBR{
    int tamano;
    char fecha[20];
    int asignature;
    char fit[2];
    Particion particion1;
    Particion particion2;
    Particion particion3;
    Particion particion4;
};

struct ParticionM
{
    string id = "";
    string nombre = "";
};

struct Disco
{
    string path = "";
    int num = 0;
    ParticionM particon_montad[50];
};

char letras[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

Disco discos[26];


#endif