#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    char email[100];
    char nome[100];
} Usuario;

typedef struct{
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    int status; //0-disponivel, 1-emprestado
    char email_emp[100];

} Livro;

