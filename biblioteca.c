#include "biblioteca.h"

void menuCadastro(NoLivro **raizLivros, NoUser **raizUsuarios) {
    int op;
    printf("\nCadastro\n1- Livros\n2- Usuarios\n0- Voltar\nDigite a opcao: ");
    scanf("%d", &op);
    
    if (op == 1) {
        Livro livro;
        printf("codigo do livro: "); scanf("%d", &livro.codigo);
        printf("digite a informacao a seguir sem usar espacos\n");
        printf("titulo: "); scanf("%s", livro.titulo);
        printf("digite a informacao a seguir sem usar espacos\n");
        printf("autor: "); scanf("%s", livro.autor);
        printf("ano: "); scanf("%d", &livro.ano);
        livro.status = 0;
        *raizLivros = inserirLivro(*raizLivros, livro);
        printf("Cadastro concluido\n");
    } else if (op == 2) {
        Usuario user;
        printf("Email: "); scanf("%s", user.email);
        printf("digite a informacao a seguir sem usar espacos\n");
        printf("Nome: "); scanf("%s", user.nome);
        *raizUsuarios = inserirUsuario(*raizUsuarios, user);
        printf("Cadastro concluido\n");
    }
}

void menuConsulta(NoLivro *raizLivros, NoUser *raizUsuarios) {
    int op;
    printf("\nConsulta\n1- Livros\n2- Usuarios\n3- Emprestimos\n0- Voltar\nDigite a opcao: ");
    scanf("%d", &op);
    
    if (op == 1) {
        int tipo;
        printf("1- Por codigo\n2- Por autor\nDigite a opcao: ");
        scanf("%d", &tipo);
        if (tipo == 1) {
            int id; printf("ID: "); scanf("%d", &id);
            NoLivro *res = buscarLivroCodigo(raizLivros, id);
            if(res) printf("Achou: %s\n  Autor: %s\n  Status: %s\n", res->livro.titulo, res->livro.autor, res->livro.status ? "Emprestado" : "Disponivel");
            else printf("Nao encontrado\n");
        } else if (tipo == 2) {
            char aut[100]; printf("Autor: "); scanf("%s", aut);
            int encontrou = 0;
            buscarLivroAutor(raizLivros, aut, &encontrou);
            if(!encontrou) printf("Nao encontrado\n");
        }
    } else if (op == 2) {
        int tipo;
        printf("1- Por email\n2- Por nome\nDigite a opcao: ");
        scanf("%d", &tipo);
        if (tipo == 1) {
            char email[100]; printf("Email: "); scanf("%s", email);
            NoUser *res = buscarUsuarioEmail(raizUsuarios, email);
            if(res) printf("Achou: %s\n", res->usuario.nome);
            else printf("Nao cadastrado\n");
        } else if (tipo == 2) {
            char nome[100]; printf("Nome: "); scanf("%s", nome);
            int encontrou = 0;
            buscarUsuarioNome(raizUsuarios, nome, &encontrou);
            if(!encontrou) printf("Nao cadastrado\n");
        }
    } else if (op == 3) {
        char email[100]; printf("Email do usuario: "); scanf("%s", email);
        int encontrou = 0;
        listarEmprestimosUsuario(raizLivros, email, &encontrou);
        if(!encontrou) printf("Nenhum emprestimo para este usuario\n");
    }
}

void menuAtualizacao(NoLivro *raizLivros, NoUser *raizUsuarios) {
    int op;
    printf("\nAtualizacao\n1- Livros\n2- Usuarios\n0- Voltar\nDigite a opcao: ");
    scanf("%d", &op);
    
    if (op == 1) {
        int id; printf("ID do livro: "); scanf("%d", &id);
        NoLivro *res = buscarLivroCodigo(raizLivros, id);
        if (res) {
            printf("Novo Titulo: "); scanf("%s", res->livro.titulo);
            printf("Novo Autor: "); scanf("%s", res->livro.autor);
            printf("Novo Ano: "); scanf("%d", &res->livro.ano);
            printf("Atualizado\n");
        } else {
            printf("Nao encontrado\n");
        }
    } else if (op == 2) {
        char email[100]; printf("Email do usuario: "); scanf("%s", email);
        NoUser *res = buscarUsuarioEmail(raizUsuarios, email);
        if (res) {
            printf("Novo Nome: "); scanf("%s", res->usuario.nome);
            printf("Atualizado com sucesso\n");
        } else {
            printf("Nao encontrado\n");
        }
    }
}

