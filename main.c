#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

int main(){

    int op = -1;
    NoLivro *raizLivros = NULL;
    NoUser *raizUsuarios = NULL;

    while (op != 0)
    {
        printf("\n================\n");
        printf(" SISTEMA DE BIBLIOTECA");
        printf("================\n");
        printf("1. Cadastro\n");
        printf("2. Consultar\n");
        printf("3. Atulizacao\n");
        printf("4. exclusao\n");
        printf("5. Emprestimo\n");
        printf("6. Devolucao\n");
        printf("0. sair\n");
        printf("\n>>>");
        scanf("%d", &op);

        switch (op)
        {
        case 1: menuCadastro(&raizLivros, &raizUsuarios); break;
        
        case 2: menuConsulta(raizLivros, raizUsuarios); break;
            
        case 3:menuAtualizacao(raizLivros, raizUsuarios); break;
        
        case 4: menuExclusao(&raizLivros, &raizUsuarios); break;

        case 5:realizarEmprestimo(raizLivros, raizUsuarios); break;

        case 6:realizarDevolucao(raizLivros); break;

        case 0:
            liberaLivros(raizLivros);
            liberaUsuario(raizUsuarios);
            printf("Programa encerrado. Memoria liberada.\n");
            break;


        default:
            printf("Opcao invalida.\n ");
            break;
        }

    }
    
return 0;
}