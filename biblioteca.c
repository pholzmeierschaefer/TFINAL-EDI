/*  
    AVISO DE USO DE LLM
    1 - Funções "excluirLivro" e "excluirUsuario"
        foi utilizada para auxiliar na estruturação da exclusão em arvores, para entender e implementar
            corretamente o caso de remoção de nós com dois filhos(buscando o sucessor em-ordem para substituição)

    2 - Funções "menuConsulta" e de buscas 
        para utiliza~çao do operador ternario (ex: status ? "Emprestado" : "Disponivel") 
            para simplificar a exibição de dados no terminal, deixando o código mais limpo e legível 
            eliminando a necessidade de if's/else's extras apenas para formatação de texto

*/

#include "biblioteca.h"

//implementacao inserir usuario
NoUser* inserirUsuario(NoUser *raiz, Usuario u) {
    if (raiz == NULL) {
        NoUser *novo = (NoUser*)malloc(sizeof(NoUser));
        novo->usuario = u; novo->esquerda = NULL; novo->direita = NULL;
        return novo;
    }
    int cmp = strcmp(u.email, raiz->usuario.email);
    if (cmp < 0) raiz->esquerda = inserirUsuario(raiz->esquerda, u);
    else if (cmp > 0) raiz->direita = inserirUsuario(raiz->direita, u);
    else printf("Erro: Email ja cadastrado!\n");
    return raiz;
}

//implementacao buscar por email
NoUser* buscarUsuarioEmail(NoUser *raiz, char *email) {
    if (raiz == NULL) return NULL;
    int cmp = strcmp(email, raiz->usuario.email);
    if (cmp == 0) return raiz;
    if (cmp < 0) return buscarUsuarioEmail(raiz->esquerda, email);
    return buscarUsuarioEmail(raiz->direita, email);
}
//implementacao buscar por nome
void buscarUsuarioNome(NoUser *raiz, char *nome, int *encontrou) {
    if (raiz == NULL) return;
    buscarUsuarioNome(raiz->esquerda, nome, encontrou);
    if (strcmp(raiz->usuario.nome, nome) == 0) {
        printf("Email: %s | Nome: %s\n", raiz->usuario.email, raiz->usuario.nome);
        *encontrou = 1;
    }
    buscarUsuarioNome(raiz->direita, nome, encontrou);
}

//implementação exlcuir usuario
NoUser* excluirUsuario(NoUser *raiz, char *email) {
    if (raiz == NULL) { printf("Usuario nao encontrado!\n"); return raiz; }
    int cmp = strcmp(email, raiz->usuario.email);
    if (cmp < 0) raiz->esquerda = excluirUsuario(raiz->esquerda, email);
    else if (cmp > 0) raiz->direita = excluirUsuario(raiz->direita, email);
    else {
        if (raiz->esquerda == NULL){
            NoUser *aux = raiz->direita; free(raiz); printf("Usuario excluido\n");
            return aux; 
        }
        else if (raiz->direita == NULL){
            NoUser *aux = raiz->esquerda; free(raiz); printf("Usuario excluido\n");
            return aux;
        }
        NoUser *aux = raiz->direita;
        while (aux->esquerda != NULL) aux = aux->esquerda;
        raiz->usuario = aux->usuario;
        raiz->direita = excluirUsuario(raiz->direita, aux->usuario.email);
    }
    return raiz;
}

//implementacao inserir livro
NoLivro* inserirLivro(NoLivro *raiz, Livro l) {
    if (raiz == NULL) {
        NoLivro *novo = (NoLivro*)malloc(sizeof(NoLivro));
        novo->livro = l;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    if (l.codigo < raiz->livro.codigo){
        raiz->esquerda = inserirLivro(raiz->esquerda, l);
    }
    else if (l.codigo > raiz->livro.codigo){
        raiz->direita = inserirLivro(raiz->direita, l);
    }
    else{ 
        printf("ID cadastrado\n");
    }
    return raiz;
}

//implementacao buscar por codigo
NoLivro* buscarLivroCodigo(NoLivro *raiz, int codigo) {
    if (raiz == NULL){
        return NULL;
    }
    if (raiz->livro.codigo == codigo){
        return raiz;
    }
    if (codigo < raiz->livro.codigo){
        return buscarLivroCodigo(raiz->esquerda, codigo);
    }
    return buscarLivroCodigo(raiz->direita, codigo);
}

//iplementacao buscar por autor
void buscarLivroAutor(NoLivro *raiz, char *autor, int *encontrou) {
    if (raiz == NULL) return;
    buscarLivroAutor(raiz->esquerda, autor, encontrou);
    if (strcmp(raiz->livro.autor, autor) == 0) {
        printf("ID: %d\n Titulo: %s\n Ano: %d\n Status: %s\n", 
               raiz->livro.codigo, raiz->livro.titulo, raiz->livro.ano, raiz->livro.status ? "Emprestado" : "Disponivel");
        *encontrou = 1;
    }
    buscarLivroAutor(raiz->direita, autor, encontrou);
}

//implementacao excluir livor
NoLivro* excluirLivro(NoLivro *raiz, int codigo) {
    if (raiz == NULL){
        printf("Livro nao encontrado\n");
        return raiz;
    }
    if (codigo < raiz->livro.codigo){
        raiz->esquerda = excluirLivro(raiz->esquerda, codigo);
    }
    else if (codigo > raiz->livro.codigo){
        raiz->direita = excluirLivro(raiz->direita, codigo);
    }
    else {
        if (raiz->esquerda == NULL){
            NoLivro *aux = raiz->direita;
            free(raiz);
            printf("Livro excluido\n");
            return aux;
        }
        else if (raiz->direita == NULL){
            NoLivro *aux = raiz->esquerda;
            free(raiz);
            printf("Livro excluido\n");
            return aux;
        }
        NoLivro *aux = raiz->direita;
        while (aux->esquerda != NULL) aux = aux->esquerda;
        raiz->livro = aux->livro;
        raiz->direita = excluirLivro(raiz->direita, aux->livro.codigo);
    }
    return raiz;
}

//implementacao listar os emprestimos do usuario
void listarEmprestimosUsuario(NoLivro *raiz, char *email, int *encontrou) {
    if (raiz == NULL)
        return;
    listarEmprestimosUsuario(raiz->esquerda, email, encontrou);
    if (raiz->livro.status == 1 && strcmp(raiz->livro.email_emprestimo, email) == 0){
        printf("ID: %d\n Titulo: %s\n Autor: %s\n", raiz->livro.codigo, raiz->livro.titulo, raiz->livro.autor);
        *encontrou = 1;
    }
    listarEmprestimosUsuario(raiz->direita, email, encontrou);
}

//implementacao do menu para cadastros
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

//implementacao menu de consulta
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

//implementacao menu para atualizar cadastros
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

//implementacao para emprestar
void fazerEmprestimo(NoLivro *raizLivros, NoUser *raizUsuarios) {
    int id;
    char email[100];
    printf("ID do livro: "); scanf("%d", &id);
    NoLivro *livro = buscarLivroCodigo(raizLivros, id);
    
    if (livro && livro->livro.status == 0) {
        printf("Email do Usuario: "); scanf("%s", email);
        NoUser *user = buscarUsuarioEmail(raizUsuarios, email);
        if (user) {
            livro->livro.status = 1;
            strcpy(livro->livro.email_emprestimo, email);
            printf("Emprestimo registrado\n");
        } else {
            printf("Usuario nao cadastrado\n");
        }
    } else {
        printf("Livro nao existe ou ja esta emprestado.\n");
    }
}


//implementacao para devolver
void fazerDevolucao(NoLivro *raizLivros) {
    int id;
    printf("ID do Livro a ser devolvido: "); scanf("%d", &id);
    NoLivro *livro = buscarLivroCodigo(raizLivros, id);
    
    if (livro && livro->livro.status == 1) {
        livro->livro.status = 0;
        strcpy(livro->livro.email_emprestimo, "");
        printf("Devolucao realizada\n");
    } else {
        printf("O livro nao estava emprestado ou nao existe\n");
    }
}