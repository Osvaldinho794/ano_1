    //  INCLUSÕES  //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    //  CONSTANTES ARQUIVOS  //

#define ARQUIVO_USUARIOS "fm_usuarios.bin" // Arquivo onde estão armazendados os usuários
#define ARQUIVO_PRODUTOS "fm_produtos.bin" // Arquivo onde estão armazendados os produtos
#define ARQUIVO_AVALIACOES "fm_avaliacoes.bin" // Arquivo onde estão armazendados as avaliações

    //  CONSTANTES GERAIS  //


    //  CONSTANTES USUÁRIOS  //

#define USUARIO_CARACTERES_EMAIL (40 + 1) // Máximo de caracteres de um e-mail
#define USUARIO_CARACTERES_NOME (40 + 1) // Máximo de caracteres de um nome de usuário
#define USUARIO_CARACTERES_ID (30 + 1)  // Máximo de caracteres de um identificador de usuário
#define USUARIO_CARACTERES_SENHA (30 + 1)  // Máximo de caracteres de uma senha
#define USUARIO_SENHA_MINIMO_CARACTERES (8)  // Mínimo de caracteres de uma senha
#define USUARIO_SENHA_MINIMO_MAIUSCULAS (1)  // Mínimo de caracteres de uma senha
#define USUARIO_SENHA_MINIMO_NUMEROS (1)  // Mínimo de caracteres de uma senha

    //  CONSTANTES PRODUTOS  //

#define PRODUTO_CARACTERES_NOME (40 + 1)  // Máximo de caracteres de um nome de produto
#define PRODUTO_CARACTERES_ID (20)  // Máximo de caracteres de um identificador de produto
#define PRODUTO_CARACTERES_DESCRICAO (40 + 1)  // Máximo de caracteres de uma descrição de produto

    //  CONSTANTES AVALIAÇÕES  //

#define AVALIACAO_CARACTERES_MENSAGEM (300 + 1)  // Máximo de caracteres de uma avaliação
#define AVALIACAO_CARACTERES_ID (USUARIO_CARACTERES_ID + PRODUTO_CARACTERES_ID + 1)  // Máximo de caracteres de uma avaliação

    //  CONSTANTES RETORNO  //

#define SUCESSO 0  // Saída genérica de sucesso
#define ERRO -1  // Saída genérica de erro

#define ERRO_SENHA_CARACTERES_INSUFICIENTES  1 // Saída de erro para senha com caracteres insuficientes
#define ERRO_SENHA_SEM_NUMEROS               2 // Saída de erro para senha sem o mínimo de números
#define ERRO_SENHA_SEM_MAIUSCULAS            3 // Saída de erro para senha sem o minimo de maiúsculas

    //  CONSTANTES LOGIN  //

#define LOGIN_SEM_LOGIN -1 // Valor de login usado para usuário sem login

    //  CONSTANTES GERAIS  //

typedef unsigned int bool;
#define true (1 == 1)
#define false (1 == 0)

    //  ESTRUTURAS  //
    
/* 
    #### Usuário
    - email : E-mail do usuário
    - senha : Senha do usuário
    - id: Identificador do usuário
    - nomeExibicao: Nome de exibição do usuário
*/
typedef struct usuario_e {
    char email[USUARIO_CARACTERES_EMAIL];
    char senha[USUARIO_CARACTERES_SENHA];
    char id[USUARIO_CARACTERES_ID];
    char nome[USUARIO_CARACTERES_NOME];
} usuario_t;

/* 
    #### Produto
    - idVendedor : Identificador do vendedor
    - id : Identificador do produto
    - nome: Nome do produto
    - nota: Nota média do produto
*/
typedef struct produto_e {
    char idVendedor[PRODUTO_CARACTERES_ID];
    char id[PRODUTO_CARACTERES_ID];
    char nome[PRODUTO_CARACTERES_NOME];
    char descricao[PRODUTO_CARACTERES_DESCRICAO];
    int  estoque;
} produto_t;

/*
    #### Avaliacao
    - idAvaliacao: Identificador da avaliação
    - idProduto: Identificador do produto avaliado
    - idComprador: Identificador do comprador que avaliou
    - mensagem: Mensagem da avaliação
    - nota: Nota dada para o produto
*/
typedef struct avaliacao_e {
    char idAvaliacao[AVALIACAO_CARACTERES_ID];
    char idProduto[PRODUTO_CARACTERES_ID];
    char idComprador[USUARIO_CARACTERES_ID];
    char mensagem[AVALIACAO_CARACTERES_MENSAGEM];
    int  nota;
} avaliacao_t;

    //  FUNCOES  //

// Verifica se existe o e-mail digitado
bool emailExiste(char email[USUARIO_CARACTERES_EMAIL]) {
    if(fopen(ARQUIVO_USUARIOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return true;
    }
    FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    usuario_t * usuarios;
    int nUsuarios;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);
    if(nUsuarios > 0) {
        fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
        if(usuarios == NULL) printf("Erro ao ler dados do arquivo\n");
        fclose(arquivoUsuarios);
    } else return false;

    // Passa por todos os usuários, comparando o e-mail digitado para verificar se o e-mail já está cadastrado
    for(int i = 0; i < nUsuarios; i++) {
        if(strcmp(email, usuarios[i].email) == 0) {
            return true;
        }
    }

    // Se chegou aqui, o e-mail não foi cadastrado anteriormente
    return false;
}

// Verifica se existe o ID de usuário digitado
bool idUsuarioExiste(char id[USUARIO_CARACTERES_ID]) {
    if(fopen(ARQUIVO_USUARIOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return false;
    }
    FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    usuario_t * usuarios;
    int nUsuarios;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);
    if(nUsuarios > 0) {
        fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
        if(usuarios == NULL) printf("Erro ao ler dados do arquivo\n");
        fclose(arquivoUsuarios);
    } else return false;

    // Passa por todos os usuários, comparando o ID digitado para verificar se o ID já está cadastrado
    for(int i = 0; i < nUsuarios; i++) {
        if(strcmp(id, usuarios[i].id) == 0) {
            return true;
        }
    }

    return false;
}
// Verifica se existe o ID de usuário digitado
bool idProdutoExiste(char id[PRODUTO_CARACTERES_ID]) {
    if(fopen(ARQUIVO_USUARIOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return false;
    }
    FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    usuario_t * usuarios;
    int nUsuarios;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);
    if(nUsuarios > 0) {
        fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
        if(usuarios == NULL) printf("Erro ao ler dados do arquivo\n");
        fclose(arquivoUsuarios);
    } else return false;

    // Passa por todos os usuários, comparando o ID digitado para verificar se o ID já está cadastrado
    for(int i = 0; i < nUsuarios; i++) {
        if(strcmp(id, usuarios[i].id) == 0) {
            return true;
        }
    }

    return false;
}

/* Verifica se a senha é válida
 - ERRO_SENHA_CARACTERES_INSUFICIENTES 
 - ERRO_SENHA_SEM_NUMEROS
 - ERRO_SENHA_SEM_MAIUSCULAS
*/
int validaSenha(char senha[USUARIO_CARACTERES_SENHA]) {
    int tamanho = strlen(senha);
    int nNumeros = 0, nMaiusculas = 0;
    for(int i = 0; i < tamanho; i++) {
        if(senha[i] > '0' && senha[i] < '9') nNumeros++;
        if(senha[i] > 'A' && senha[i] < 'Z') nMaiusculas++;
    }

    if(tamanho < USUARIO_SENHA_MINIMO_CARACTERES) return ERRO_SENHA_CARACTERES_INSUFICIENTES;
    if(nMaiusculas < USUARIO_SENHA_MINIMO_MAIUSCULAS) return ERRO_SENHA_SEM_MAIUSCULAS;
    if(nNumeros < USUARIO_SENHA_MINIMO_NUMEROS) return ERRO_SENHA_SEM_NUMEROS;

    return SUCESSO;
}

// Verifica se o e-mail é válido (formatado como "#@#.#")
bool validaEmail(char email[USUARIO_CARACTERES_EMAIL]) {
    int tamanho = strlen(email);
    int nArrobas = 0;
    int posicaoArroba;

    // Verifica cada caractere do e-mail
    for (int i = 0; i < tamanho; i++) {
        // Conta a quantidade de arrobas no e-mail
        if (email[i] == '@') {
            nArrobas++;
            // Armazena a posição da arroba
            posicaoArroba = i; 
        }
    }

    // Se houver mais de um arroba ou nenhum, retorna falso
    if (nArrobas != 1) return false;

    // Verifica os pontos após o arroba
    int nPontosDepoisDoArroba = 0;
    for (int j = posicaoArroba + 1; j < tamanho; j++) {
        if (email[j] == '.') {
            nPontosDepoisDoArroba++;
            // Verifica se o próximo caractere é um ponto
            if (j + 1 < tamanho && email[j + 1] == '.') {
                // Retorna falso se houver ponto seguido de ponto
                return false; 
            }
        }
    }

    // Se não houver um ponto após o arroba, retorna falso
    if (nPontosDepoisDoArroba < 1) return false;

    // Se chegou até aqui, o e-mail é válido
    return true; 
} 

// Verifica se o ID é válido (apenas letras minúsculas, números, pontos e underline)
bool validaIDUsuario(char id[USUARIO_CARACTERES_ID]) {
    int tamanho = strlen(id);

    for(int i = 0; i < tamanho; i++) {
        if(!((id[i] >= 'a' && id[i] <= 'z') || (id[i] >= '0' && id[i] <= '9') || id[i] == '.' || id[i] == '_')) return false;
    }

    return true;
}

// Gera um ID para o produto usando apenas letras minúsculas, hífens e numeros
void geraIDProduto(char id[PRODUTO_CARACTERES_ID], char nome[PRODUTO_CARACTERES_NOME]) {
    int tamanho = strlen(nome);
    int nCaracteresPulados = 0;

    for(int i = 0; i < tamanho; i++) { if(nome[i] >= 'A' && nome[i] <= 'Z') id[i - nCaracteresPulados] = nome[i] + 32;
        else if(nome[i] >= 'a' && nome[i] <= 'z') id[i - nCaracteresPulados] = nome[i];
        else if(nome[i] >= '0' && nome[i] <= '9') id[i - nCaracteresPulados] = nome[i];
        else if(nome[i] == '-' || nome[i] == '.' || nome[i] == ' ') id[i - nCaracteresPulados] = '-';
        else nCaracteresPulados++;
    }
    id[tamanho - nCaracteresPulados] = '\0';

    return;
}

// Remove a quebra de linha ('\n') no final de uma string
void removeQuebra(char string[]) {
    int tamanho = strlen(string);
    if(tamanho > 0 && string[tamanho - 1] == '\n') string[tamanho - 1] = '\0';
    return;
}

// Retorna o índice do usuário com o e-mail passado
int indiceUsuarioPorEmail(char email[USUARIO_CARACTERES_EMAIL]) {
    if(fopen(ARQUIVO_USUARIOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return ERRO;
    }
    FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    usuario_t * usuarios;
    int nUsuarios;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);

    fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
    fclose(arquivoUsuarios);

    for(int i = 0; i < nUsuarios; i++) {
        if(strcmp(email, usuarios[i].email) == 0) return i;
    }

    return ERRO;
}

// Retorna o índice do usuário com o identificador passado
int indiceUsuarioPorID(char id[USUARIO_CARACTERES_ID]) {
    if(fopen(ARQUIVO_USUARIOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return ERRO;
    }
    FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    usuario_t * usuarios;
    int nUsuarios;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);

    fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
    fclose(arquivoUsuarios);

    for(int i = 0; i < nUsuarios; i++) {
        if(strcmp(id, usuarios[i].id) == 0) return i;
    }

    return ERRO;
}

// Cadastra um novo usuário e o adiciona ao arquivo
void cadastraUsuario() {
    if(fopen(ARQUIVO_USUARIOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }
    FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    usuario_t * usuarios;
    int nUsuarios;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);
    if(nUsuarios > 0) {
        fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
        if(usuarios == NULL) printf("Erro ao ler dados do arquivo\n");
    }
    fclose(arquivoUsuarios);

    nUsuarios++;
    usuarios = realloc(usuarios, sizeof(usuario_t) * nUsuarios);
    if(usuarios == NULL) printf("Erro ao realocar a memoria\n");
    char email[USUARIO_CARACTERES_EMAIL];
    char senha[USUARIO_CARACTERES_SENHA];
    char id[USUARIO_CARACTERES_ID];
    char nome[USUARIO_CARACTERES_NOME];

    // Lê o e-mail digitado até ser um e-mail válido
    do {
        printf("E-MAIL\n");
        printf(" : ");
        fgets(email, USUARIO_CARACTERES_EMAIL, stdin);
        removeQuebra(email);
        if(emailExiste(email) == true) printf("E-MAIL JA CADASTRADO\n");
        if(validaEmail(email) == false) printf("E-MAIL INVALIDO\n");
    } while(emailExiste(email) == true || validaEmail(email) == false);

    // Lê a senha digitada até ser uma senha válida
    do {
        printf("SENHA\n");
        // printf("deve conter:\n");
        // printf(" - %d caracteres;\n", USUARIO_SENHA_MINIMO_CARACTERES);
        // printf(" - %d letras maiusculas;\n", USUARIO_SENHA_MINIMO_MAIUSCULAS);
        // printf(" - %d numeros;\n", USUARIO_SENHA_MINIMO_NUMEROS);
        printf(" : ");
        fgets(senha, USUARIO_CARACTERES_SENHA, stdin);
        removeQuebra(senha);
        if(validaSenha(senha) != SUCESSO) {
            switch (validaSenha(senha)) {
            case ERRO_SENHA_CARACTERES_INSUFICIENTES:
                printf(" - A SENHA DEVE CONTER AO MENOS %d CARACTERES\n", USUARIO_SENHA_MINIMO_CARACTERES);
            break;

            case ERRO_SENHA_SEM_MAIUSCULAS:
                printf(" - A SENHA DEVE CONTER AO MENOS %d LETRA MAIUSCULAS\n", USUARIO_SENHA_MINIMO_MAIUSCULAS);
            break;

            case ERRO_SENHA_SEM_NUMEROS:
                printf(" - A SENHA DEVE CONTER AO MENOS %d NUMEROS\n", USUARIO_SENHA_MINIMO_NUMEROS);
            break;
            }
        }
    } while(validaSenha(senha) != SUCESSO);

    // Lê o identificador do usuário
    do {
        printf("NOME DE USUARIO\n");
        printf(" : ");
        fgets(id, USUARIO_CARACTERES_ID, stdin);
        removeQuebra(id);
        if(idUsuarioExiste(id) == true) printf("NOME DE USUARIO JA CADASTRADO\n");
    } while(idUsuarioExiste(id) == true);

    printf("NOME DE EXIBICAO\n");
    printf(" : ");
    fgets(nome, USUARIO_CARACTERES_NOME, stdin);
    removeQuebra(nome);

    strcpy(usuarios[nUsuarios - 1].email, email);
    strcpy(usuarios[nUsuarios - 1].id, id);
    strcpy(usuarios[nUsuarios - 1].nome, nome);
    strcpy(usuarios[nUsuarios - 1].senha, senha);

    arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "wb");
    if(arquivoUsuarios == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }
    fwrite(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    fwrite(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
    fclose(arquivoUsuarios);

    return;
}

// Lista todos os usuários cadastrados
void listaUsuarios() {
    if(fopen(ARQUIVO_USUARIOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }
    FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    usuario_t * usuarios;
    int nUsuarios;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);
    if(nUsuarios > 0) {
        fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
        if(usuarios == NULL) printf("Erro ao ler dados do arquivo\n");
    }
    fclose(arquivoUsuarios);

    printf("Numero de usuarios cadastrado: %d\n", nUsuarios);

    printf("%-*s\t", USUARIO_CARACTERES_EMAIL, "E-mail");
    printf("%-*s\t", USUARIO_CARACTERES_SENHA, "Senha");
    printf("%-*s\t", USUARIO_CARACTERES_ID, "Identificador");
    printf("%-*s\n", USUARIO_CARACTERES_NOME, "Nome");
    for(int i = 0; i < nUsuarios; i++) {
        printf("%-*s\t", USUARIO_CARACTERES_EMAIL, usuarios[i].email);
        printf("%-*s\t", USUARIO_CARACTERES_SENHA, usuarios[i].senha);
        printf("%-*s\t", USUARIO_CARACTERES_ID, usuarios[i].id);
        printf("%-*s\n", USUARIO_CARACTERES_NOME, usuarios[i].nome);
    }
}

// Cadastra um novo produto e o adiciona ao arquivo
void cadastraProduto(int loginAtual) {
    
    if(fopen(ARQUIVO_USUARIOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }
    
    FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    usuario_t * usuarios;
    int nUsuarios;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);
    if(nUsuarios > 0) {
        fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
        if(usuarios == NULL) printf("Erro ao ler dados do arquivo\n");
    }
    fclose(arquivoUsuarios);

    nUsuarios++;
    usuarios = realloc(usuarios, sizeof(usuario_t) * nUsuarios);
    if(usuarios == NULL) printf("Erro ao realocar a memoria\n");

    if(fopen(ARQUIVO_PRODUTOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }
    FILE * arquivoProdutos = fopen(ARQUIVO_PRODUTOS, "rb");//Abre para ler os produtos
    produto_t * produtos;
    int nProdutos;

    fread(&nProdutos, sizeof(int), 1, arquivoProdutos);//Le nProdutos e aloca para produtos
    produtos = malloc(sizeof(produto_t) * nProdutos);
    if(nProdutos > 0) {
        fread(produtos, sizeof(produto_t), nProdutos, arquivoProdutos);//Le todos os produtos
        if(usuarios == NULL) printf("Erro ao ler dados do arquivo\n");
    }
    fclose(arquivoProdutos);//Depois que jogou na memória, cadastra um novo produto

    nProdutos++;
    //Incrementa e realoca para o novo número de produtos
    produtos = realloc(produtos, sizeof(produto_t) * nProdutos);
    if(produtos == NULL) printf("Erro ao realocar a memoria\n");

    char idVendedor[USUARIO_CARACTERES_ID];
    char id[PRODUTO_CARACTERES_ID];
    char nome[PRODUTO_CARACTERES_NOME];
    char descricao[PRODUTO_CARACTERES_DESCRICAO];
    int  estoque;

    strcpy(idVendedor, usuarios[loginAtual].id);//Id do usuario atual é o id do vendedor

    printf("NOME DO PRODUTO\n");
    printf(" : ");
    fgets(nome, PRODUTO_CARACTERES_NOME, stdin);
    removeQuebra(nome);
    
    printf("DESCRICAO DO PRODUTO\n");
    printf(" : ");
    fgets(descricao, PRODUTO_CARACTERES_DESCRICAO, stdin);
    removeQuebra(descricao);

    printf("ESTOQUE DO PRODUTO\n");
    printf(" : ");
    scanf("%d%*c", &estoque);

    geraIDProduto(id, nome);

    strcpy(produtos[nProdutos - 1].nome, nome);
    strcpy(produtos[nProdutos - 1].descricao, descricao);
    strcpy(produtos[nProdutos - 1].idVendedor, idVendedor);
    strcpy(produtos[nProdutos - 1].id, id);
    produtos[nProdutos - 1].estoque = estoque;
    //Após as verificações, guarda as ifnormações dentro da struct
    
    //Abre pra leitura pra armazenar o novo produto cadastrado
    arquivoProdutos = fopen(ARQUIVO_PRODUTOS, "wb");
    if(arquivoProdutos == NULL) {
        perror("Erro ao abrir arquivo");
        fclose(arquivoProdutos);
        return;
    }
    //Guarda no arquivo
    fwrite(&nProdutos, sizeof(int), 1, arquivoProdutos);
    fwrite(produtos, sizeof(produto_t), nProdutos, arquivoProdutos);
    fclose(arquivoProdutos);

    return;
}

void listaProdutos() {
    if(fopen(ARQUIVO_PRODUTOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return;
    }
    //Abre para leitura
    FILE * arquivoProdutos = fopen(ARQUIVO_PRODUTOS, "rb");
    produto_t * produtos;
    int nProdutos;
    
    //Le o numero de produtos e aloca
    fread(&nProdutos, sizeof(int), 1, arquivoProdutos);
    produtos = malloc(sizeof(produto_t) * nProdutos);
    if(nProdutos > 0) {
        //Le todos os produtos
        fread(produtos, sizeof(produto_t), nProdutos, arquivoProdutos);
        if(produtos == NULL) printf("Erro ao ler dados do arquivo\n");
    }
    fclose(arquivoProdutos);

    printf("%-*s\t", PRODUTO_CARACTERES_ID, "IDENTIFICADOR");
    printf("%-*s\t", USUARIO_CARACTERES_ID, "VENDEDOR");
    printf("%-*s\t", 10, "ESTOQUE");
    printf("%-*s\t", PRODUTO_CARACTERES_NOME, "NOME");
    printf("%-*s\n", PRODUTO_CARACTERES_DESCRICAO, "DESCRICAO");

    for(int i = 0; i < nProdutos; i++) {
        printf("%-*s\t", PRODUTO_CARACTERES_ID, produtos[i].id);
    printf("%-*s\t", USUARIO_CARACTERES_ID, produtos[i].idVendedor);
        printf("%-*d\t", 10,  produtos[i].estoque);
        printf("%-*s\t", PRODUTO_CARACTERES_NOME,  produtos[i].nome);
        printf("%-*s\n", PRODUTO_CARACTERES_DESCRICAO,  produtos[i].descricao);
    }
}

void cadastraAvaliacao(int loginAtual) {
    // Abre o arquivo de usuários para leitura
    FILE *arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    if (arquivoUsuarios == NULL) {
        printf("Erro na abertura do arquivo de usuários\n");
        return;
    }

    // Lê os usuários existentes
    usuario_t *usuarios;
    int nUsuarios;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);
    if (nUsuarios > 0) {
        fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
    }
    fclose(arquivoUsuarios);

    // Abre o arquivo de produtos para leitura
    FILE *arquivoProdutos = fopen(ARQUIVO_PRODUTOS, "rb");
    if (arquivoProdutos == NULL) {
        printf("Erro na abertura do arquivo de produtos\n");
        return;
    }

    // Lê os produtos existentes
    produto_t *produtos;
    int nProdutos;

    fread(&nProdutos, sizeof(int), 1, arquivoProdutos);
    produtos = malloc(sizeof(produto_t) * nProdutos);
    if (nProdutos > 0) {
        fread(produtos, sizeof(produto_t), nProdutos, arquivoProdutos);
    }
    fclose(arquivoProdutos);

    // Abre o arquivo de avaliações para leitura
    FILE *arquivoAvaliacoes = fopen(ARQUIVO_AVALIACOES, "rb");
    if (arquivoAvaliacoes == NULL) {
        printf("Erro na abertura do arquivo de avaliações\n");
        return;
    }

    // Lê as avaliações existentes
    avaliacao_t *avaliacoes;
    int nAvaliacoes;

    fread(&nAvaliacoes, sizeof(int), 1, arquivoAvaliacoes);
    avaliacoes = malloc(sizeof(avaliacao_t) * nAvaliacoes);
    if (nAvaliacoes > 0) {
        fread(avaliacoes, sizeof(avaliacao_t), nAvaliacoes, arquivoAvaliacoes);
    }
    fclose(arquivoAvaliacoes);

    // Incrementa o número de avaliações e realoca
    nAvaliacoes++;
    avaliacoes = realloc(avaliacoes, sizeof(avaliacao_t) * nAvaliacoes);
    if (avaliacoes == NULL) {
        printf("Erro ao realocar a memória\n");
        return;
    }

    char idAvaliacao[AVALIACAO_CARACTERES_ID];
    char idProduto[PRODUTO_CARACTERES_ID];
    char mensagem[AVALIACAO_CARACTERES_MENSAGEM];
    int nota;

    // Solicita o ID do produto
    printf("ID DO PRODUTO\n");
    printf(" : ");
    fgets(idProduto, PRODUTO_CARACTERES_ID, stdin);
    removeQuebra(idProduto);

    // Solicita a mensagem da avaliação
    printf("MENSAGEM DA AVALIACAO\n");
    printf(" : ");
    fgets(mensagem, AVALIACAO_CARACTERES_MENSAGEM, stdin);
    removeQuebra(mensagem);

    // Solicita a nota da avaliação
    printf("NOTA DA AVALIACAO (0 a 5)\n");
    printf(" : ");
    scanf("%d%*c", &nota);


    strcpy(avaliacoes[nAvaliacoes - 1].idProduto, idProduto);
    strcpy(avaliacoes[nAvaliacoes - 1].idComprador, usuarios[loginAtual].id); // ID do comprador
    strcpy(avaliacoes[nAvaliacoes - 1].mensagem, mensagem);
    avaliacoes[nAvaliacoes - 1].nota = nota;

    // Abre para escrita para armazenar a nova avaliação
    arquivoAvaliacoes = fopen(ARQUIVO_AVALIACOES, "wb");
    if (arquivoAvaliacoes == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return;
    }

    // Guarda no arquivo
    fwrite(&nAvaliacoes, sizeof(int), 1, arquivoAvaliacoes);
    fwrite(avaliacoes, sizeof(avaliacao_t), nAvaliacoes, arquivoAvaliacoes);
    fclose(arquivoAvaliacoes);

    printf("Avaliação cadastrada com sucesso!\n");
}



int fazerLogin() {
    if(fopen(ARQUIVO_USUARIOS, "rb") == NULL) {
        printf("Erro na abertura do arquivo\n");
        return LOGIN_SEM_LOGIN;
    }
    FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    usuario_t * usuarios;
    int nUsuarios;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);
    if(nUsuarios > 0) {
        fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
        if(usuarios == NULL) printf("Erro ao ler dados do arquivo\n");
    }
    fclose(arquivoUsuarios);

    int indiceUsuario;
    char email[USUARIO_CARACTERES_EMAIL];
    char id[USUARIO_CARACTERES_ID];
    char senha[USUARIO_CARACTERES_EMAIL];
    int escolha;
    
    do {
        printf("Fazer login com:\n");
        printf("1 - E-mail\n");
        printf("2 - Nome de usuario\n");
        printf(" : ");
        scanf("%d%*c", &escolha);
    } while(escolha != 1 && escolha != 2);

    switch(escolha) {
        case 1:
            do {
            printf("E-MAIL\n");
            printf(" : ");
            fgets(email, USUARIO_CARACTERES_EMAIL, stdin);
            removeQuebra(email);
            } while(emailExiste(email) == false);//Loop só termina quando digitar um e-mail valido

            indiceUsuario = indiceUsuarioPorEmail(email);
            //Seu indice de usuario é o indice retornado pela função que verifica o e-mail
            do {
                printf("SENHA\n");
                printf(" : ");
                fgets(senha, USUARIO_CARACTERES_SENHA, stdin);
                removeQuebra(senha);
            if(strcmp(senha, usuarios[indiceUsuario].senha) != 0) {
                bool tentarNovamente;
                printf("SENHA INCORRETA\n");
                printf("1 - Tentar novamente\n");
                printf("0 - Sair");
                scanf("%d%*c", &tentarNovamente);
                if(tentarNovamente == false) return LOGIN_SEM_LOGIN;
            }
            } while(strcmp(senha, usuarios[indiceUsuario].senha) != 0);
        break;

        case 2:
            do {
            printf("NOME DE USUARIO\n");
            printf(" : ");
            fgets(id, USUARIO_CARACTERES_ID, stdin);
            removeQuebra(id);
            } while(idUsuarioExiste(id) == false);
            
            indiceUsuario = indiceUsuarioPorID(id);

            do {
                printf("SENHA\n");
                printf(" : ");
                fgets(senha, USUARIO_CARACTERES_SENHA, stdin);
                removeQuebra(senha);
            if(strcmp(senha, usuarios[indiceUsuario].senha) != 0) {
                bool tentarNovamente;
                printf("SENHA INCORRETA\n");
                printf("1 - Tentar novamente\n");
                printf("0 - Sair");
                scanf("%d%*c", &tentarNovamente);
                if(tentarNovamente == false) return LOGIN_SEM_LOGIN;
            }
            } while(strcmp(senha, usuarios[indiceUsuario].senha) != 0);
        break;
    }
    
    return indiceUsuario;
}
void listaProdutosPorID() {
    // Abre o arquivo de produtos para leitura
    FILE *arquivoProdutos = fopen(ARQUIVO_PRODUTOS, "rb");
    if (arquivoProdutos == NULL) {
        printf("Erro na abertura do arquivo de produtos\n");
        return;
    }

    produto_t *produtos;
    int nProdutos;
    
    // Lê o número de produtos
    fread(&nProdutos, sizeof(int), 1, arquivoProdutos);
    produtos = malloc(sizeof(produto_t) * nProdutos);
    if (nProdutos > 0) {
        fread(produtos, sizeof(produto_t), nProdutos, arquivoProdutos);
    }
    fclose(arquivoProdutos);

    // Solicita o ID do vendedor ao usuário
    char idVendedor[USUARIO_CARACTERES_ID];
    printf("Digite o ID do vendedor para listar os produtos:\n");
    printf(" : ");
    fgets(idVendedor, USUARIO_CARACTERES_ID, stdin);
    removeQuebra(idVendedor);

    //Mostra todos os produtos
    printf("Produtos do vendedor com ID %s:\n", idVendedor);
    for (int i = 0; i < nProdutos; i++) {
        if (strcmp(produtos[i].idVendedor, idVendedor) == 0) {
            printf("Produto: %s\n", produtos[i].nome);
                
    
        }
    }
    
    int opcao;
    printf("1 - Ver detalhes de um produto\n0 - Sair\n");
    scanf("%d%*c", &opcao);

    // Se o usuário quiser ver detalhes, solicita o número do produto
    if (opcao == 1) {
        for (int i = 0; i < nProdutos; i++) {
            if (strcmp(produtos[i].idVendedor, idVendedor) == 0) {
                printf("Descrição: %s\n", produtos[i].descricao);
                printf("Estoque: %d\n", produtos[i].estoque);
            }
        }
    }
}



    //  MAIN  //

int main(int argc, char ** argv) {
    // Tenta abrir o arquivo com os usuários, se não existir, cria
    if(fopen(ARQUIVO_USUARIOS, "rb") == NULL) {
        FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "wb");
        int nUsuarios = 0;
        fwrite(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
        fclose(arquivoUsuarios);
    }
    // Tenta abrir o arquivo com os produtos, se não existir, cria
    if(fopen(ARQUIVO_PRODUTOS, "rb") == NULL) {
        FILE * arquivoProdutos = fopen(ARQUIVO_PRODUTOS, "wb");
        int nProdutos = 0;
        fwrite(&nProdutos, sizeof(int), 1, arquivoProdutos);
        fclose(arquivoProdutos);
    }
    // Tenta abrir o arquivo com as avaliações, se não existir, cria
        if(fopen(ARQUIVO_AVALIACOES, "rb") == NULL) {
        FILE * arquivoAvaliacoes = fopen(ARQUIVO_AVALIACOES, "wb");
        int nAvaliacoes = 0;
        fwrite(&nAvaliacoes, sizeof(int), 1, arquivoAvaliacoes);
        fclose(arquivoAvaliacoes);
    }

    FILE * arquivoUsuarios = fopen(ARQUIVO_USUARIOS, "rb");
    usuario_t * usuarios;
    int nUsuarios;
    int loginAtual = LOGIN_SEM_LOGIN;

    fread(&nUsuarios, sizeof(int), 1, arquivoUsuarios);
    usuarios = malloc(sizeof(usuario_t) * nUsuarios);
    if(nUsuarios > 0) {
        fread(usuarios, sizeof(usuario_t), nUsuarios, arquivoUsuarios);
        if(usuarios == NULL) printf("Erro ao ler dados do arquivo\n");
    }
    fclose(arquivoUsuarios);

    int escolha;
    do {
        if(loginAtual != LOGIN_SEM_LOGIN) printf("Logado como: %s\n", usuarios[loginAtual].nome);
        printf("1 - Cadastrar usuario\n");
        printf("2 - Listar usuarios\n");
        if(loginAtual == LOGIN_SEM_LOGIN) {
            printf("3 - Fazer login\n");
        } else {
            printf("3 - Desfazer login\n");
            printf("4 - Cadastrar produto\n");
            printf("5 - Listar produtos\n");
        } 
        printf("0 - Sair\n");
        // printf(" - \n");
        printf(" : ");
        scanf("%d%*c", &escolha);

        switch(escolha) {
            case 1:
            cadastraUsuario();
            break;

            case 2:
            listaUsuarios();
            break;

            case 3:
            if(loginAtual == LOGIN_SEM_LOGIN) loginAtual = fazerLogin();
            else loginAtual = LOGIN_SEM_LOGIN;
            break;

            case 4:
            if(loginAtual != LOGIN_SEM_LOGIN) cadastraProduto(loginAtual);
            else printf("FACA LOGIN PRIMEIRO\n");
            break;

            case 5:
            if(loginAtual != LOGIN_SEM_LOGIN) listaProdutos();
            else printf("FACA LOGIN PRIMEIRO\n");
            break;
            
            case 6:
            if(loginAtual != LOGIN_SEM_LOGIN) cadastraAvaliacao(loginAtual);
            else printf("FACA LOGIN PRIMEIRO\n");
            break;
            
            case 7:
            if(loginAtual != LOGIN_SEM_LOGIN) listaProdutosPorID();
            else printf("FACA LOGIN PRIMEIRO\n");
            break;

        }

    } while(escolha != 0);

    return SUCESSO;
}
