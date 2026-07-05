#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Constante: Define o tamanho máximo do acervo.
#define TAM_ACERVO 20

//Estrutura (Struct): Para armazenar os dados de cada livro.
struct Livro {
    int codigo;
    char titulo[50];
    char autor[30];
    char area[30];
    int ano;
    char editora[30];
};

//Assinaturas das Funções

// Exibe o menu de opções e recebe a escolha do usuário.
int menu();

// Cadastra novos livros no acervo.
void cadastrarLivros(struct Livro acervo[], int tamanho);

// Imprime todos os livros cadastrados no acervo.
void imprimirLivros(struct Livro acervo[], int tamanho);

// Pesquisa um livro pelo código.
void pesquisarLivro(struct Livro acervo[], int tamanho);

// Ordena os livros preenchidos por ano de publicação.
void ordenarLivros(struct Livro acervo[], int tamanho);

// Retorna o número de livros preenchidos no acervo.
int contarLivrosPreenchidos(struct Livro acervo[], int tamanho);

// Funcao para limpar o buffer de entrada 
void limparBuffer();


//Função Principal (main)
int main() {
     struct Livro acervo[TAM_ACERVO] = {0};
    int opcao;

    // Estrutura de Repetição (do-while) para o Menu Principal
    do {
        opcao = menu();
        // Estrutura Condicional (switch-case) para decidir a ação
        switch (opcao) {
            case 1:
                cadastrarLivros(acervo, TAM_ACERVO);
                break;
            case 2:
                imprimirLivros(acervo, TAM_ACERVO);
                break;
            case 3:
                pesquisarLivro(acervo, TAM_ACERVO);
                break;
            case 4:
                ordenarLivros(acervo, TAM_ACERVO);
                break;
            case 5:
                printf("\nSistema Encerrado!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente....\n");
        }
        printf("\n");
    } while (opcao != 5);

    return 0;
}

//Funções Auxiliares

void limparBuffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int menu() {
    int opcao;
    // Entrada e Saída de Dados
    printf("------------------\n");
    printf("MENU PRINCIPAL\n");
    printf("------------------\n");
    printf("1 - Cadastrar livros\n");
    printf("2 - Imprimir todos os livros\n");
    printf("3 - Pesquisar livro por código\n");
    printf("4 - Ordenar livros por ano de publicação\n");
    printf("5 - Sair do programa\n");
    printf("Digite a opção: ");
    scanf("%d", &opcao);
   
    limparBuffer(); 
    return opcao;
}

void cadastrarLivros(struct Livro acervo[], int tamanho) {
    printf("\n--- CADASTRO DE LIVROS ---\n");
    
    // Variável para controlar quantos livros o usuário deseja cadastrar
    int num_cadastro = 0; 
    printf("Quantos livros deseja cadastrar nesta sessao? (Maximo %d): ", tamanho);
    scanf("%d", &num_cadastro);
    limparBuffer();

    int pos_inicial = contarLivrosPreenchidos(acervo, tamanho);

    if (pos_inicial + num_cadastro > tamanho) {
        printf("ERRO: O limite do acervo seria ultrapassado! Maximo de %d livros restantes.\n", tamanho - pos_inicial);
        return;
    }
    
    if (pos_inicial == tamanho) {
        printf("Acervo já está completo (%d livros cadastrados)!\n", tamanho);
        return;
    }

    // Estrutura de Repetição (for)
    for (int i = 0; i < num_cadastro; i++) {
        int indice = pos_inicial + i;

        printf("\n--- LIVRO %d ---\n", indice + 1);
        
        // Entrada e Saída de Dados para cada campo da Struct
        printf("Código:\n ");
        scanf("%d", &acervo[indice].codigo);
        limparBuffer();

        printf("Título:\n ");
        fgets(acervo[indice].titulo, 50, stdin); 
        acervo[indice].titulo[strcspn(acervo[indice].titulo, "\n")] = 0;
        
        printf("Autor:\n ");
        fgets(acervo[indice].autor, 30, stdin);
        acervo[indice].autor[strcspn(acervo[indice].autor, "\n")] = 0;
        
        printf("Área:\n ");
        fgets(acervo[indice].area, 30, stdin);
        acervo[indice].area[strcspn(acervo[indice].area, "\n")] = 0;

        printf("Ano de Publicação:\n ");
        scanf("%d", &acervo[indice].ano);
        limparBuffer(); 

        printf("Editora:\n ");
        fgets(acervo[indice].editora, 30, stdin);
        acervo[indice].editora[strcspn(acervo[indice].editora, "\n")] = 0;

        printf("Livro %d cadastrado com sucesso!\n", indice + 1);
    }
}

void imprimirLivros(struct Livro acervo[], int tamanho) {
    int total = contarLivrosPreenchidos(acervo, tamanho);
    printf("\n---  ACERVO DE LIVROS (%d/%d) ---\n", total, tamanho);

    if (total == 0) {
        printf("Não há livros cadastrados no acervo.\n");
        return;
    }

    // Estrutura de Repetição (for)
    for (int i = 0; i < tamanho; i++) {
        // Estrutura Condicional para exibir apenas os livros preenchidos
        if (acervo[i].codigo > 0) {
            printf("\n-- Posicao %d --\n", i + 1);
            printf("Codigo: %d\n", acervo[i].codigo);
        
            printf("Titulo: %s\n", acervo[i].titulo); 
            printf("Autor: %s\n", acervo[i].autor);
            printf("Area: %s\n", acervo[i].area);
            printf("Ano: %d\n", acervo[i].ano);
            printf("Editora: %s\n", acervo[i].editora);
        }
    }
}

void pesquisarLivro(struct Livro acervo[], int tamanho) {
    int codigoBusca;
    int encontrado = 0;
    
    printf("\n--- PESQUISA DE LIVRO POR CÓDIGO ---\n");
    printf("Digite o código do livro que deseja pesquisar: ");
    scanf("%d", &codigoBusca);
    limparBuffer(); 

    // Estrutura de Repetição (for) 
    for (int i = 0; i < tamanho; i++) {
        // Estrutura Condicional para checar o critério de busca
        if (acervo[i].codigo > 0 && acervo[i].codigo == codigoBusca) {
            printf("\n--- Livro Encontrado ---\n");
            printf("Codigo: %d\n", acervo[i].codigo);
            printf("Titulo: %s\n", acervo[i].titulo);
            printf("Autor: %s\n", acervo[i].autor);
            printf("Area: %s\n", acervo[i].area);
            printf("Ano: %d\n", acervo[i].ano);
            printf("Editora: %s\n", acervo[i].editora);
            encontrado = 1;
            break; 
        }
    }

    if (!encontrado) {
        printf("\nLivro com código %d não encontrado no acervo.\n", codigoBusca);
    }
}

void ordenarLivros(struct Livro acervo[], int tamanho) {
    int num_preenchidos = contarLivrosPreenchidos(acervo, tamanho);
    printf("\n--- ORDENAÇÃO DE LIVROS POR ANO ---\n");
    
    if (num_preenchidos <= 1) {
        printf("Não há livros suficientes (mínimo 2) para realizar a ordenação.\n");
        return;
    }

    // Implementação do Bubble Sort
    for (int i = 0; i < num_preenchidos - 1; i++) {
        for (int j = 0; j < num_preenchidos - 1 - i; j++) {

            if (acervo[j].ano > acervo[j+1].ano) {
                struct Livro temp = acervo[j];
                acervo[j] = acervo[j+1];
                acervo[j+1] = temp;
            }
        }
    }

    printf("Acervo ordenado com sucesso por ano de publicação.\n");
    imprimirLivros(acervo, tamanho); 
}

int contarLivrosPreenchidos(struct Livro acervo[], int tamanho) {
    int contador = 0;
    // Estrutura de Repetição para contar quantos livros estão ativos
    for (int i = 0; i < tamanho; i++) {
        if (acervo[i].codigo > 0) {
            contador++;
        }
    }
    return contador;
}