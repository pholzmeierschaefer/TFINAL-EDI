#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct usuario
typedef struct{
    char email[100];
    char nome[100];
} Usuario;

//struct livro
typedef struct{
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    int status; //0-disponivel, 1-emprestado
    char email_emprestimo[100];

} Livro;

//no arvore livro
typedef struct _NoLivro{
    Livro livro;
    struct _NoLivro *esquerda, *direita;
} NoLivro;

//no arvore usuarios
typedef struct _NoUser{
    Usuario usuario;
    struct _NoUser *esquerda, *direita;
} NoUser;


//cadastrar usuario
NoUser* inserirUsuario(NoUser *raiz, Usuario usuario);

//buscar usuario por email
NoUser* buscarUsuarioEmail(NoUser *raiz, char *email);

//buscar usuario por nome
void buscarUsuarioNome(NoUser *raiz, char *nome, int *encontrou);

//excluir usuario usando email
NoUser* excluirUsuario(NoUser *raiz, char *email);

//inserir livro
NoLivro* inserirLivro(NoLivro *raiz, Livro livro);

//buscar livro pelo codigo
NoLivro* buscarLivroCodigo(NoLivro *raiz, int codigo);

//buscar livro pelo autor
void buscarLivroAutor(NoLivro *raiz, char *autor, int *encontrou);

//excluir livro usando codigo
NoLivro* excluirLivro(NoLivro *raiz, int codigo);

//listar os emprestimos do usuario usando email
void listarEmprestimosUsuario(NoLivro *raiz, char *email, int *encontrou);

//cadastrar
void menuCadastro(NoLivro **raizLivros, NoUser **raizUsuarios);

//consultar
void menuConsulta(NoLivro *raizLivros, NoUser *raizUsuarios);

//atualizar
void menuAtualizacao(NoLivro *raizLivros, NoUser *raizUsuarios);

//excluir
void menuExclusao(NoLivro **raizLivros, NoUser **raizUsuarios);

//emprestar
void realizarEmprestimo(NoLivro *raizLivros, NoUser *raizUsuarios);

//devolver
void realizarDevolucao(NoLivro *raizLivros);

void liberaLivros(NoLivro *raiz);

void liberaUsuario(NoUser *raiz);

