#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define TAM_STRING 100

typedef struct {
    char titulo[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int anoPublicacao;
    int qtdPaginas;
} Livro;

void preencherVetor(Livro livros[], int n) {
    char entrada[TAM_STRING];

    for (int i = 0; i < n; i++) {
        printf("\n Livro %d \n", i + 1);

        printf("Título: ");
        fgets(livros[i].titulo, TAM_STRING, stdin);
        livros[i].titulo[strcspn(livros[i].titulo, "\n")] = '\0';

        printf("Autor: ");
        fgets(livros[i].autor, TAM_STRING, stdin);
        livros[i].autor[strcspn(livros[i].autor, "\n")] = '\0';

        printf("Editora: ");
        fgets(livros[i].editora, TAM_STRING, stdin);
        livros[i].editora[strcspn(livros[i].editora, "\n")] = '\0';

        printf("Ano de Publicação: ");
        fgets(entrada, TAM_STRING, stdin);
        sscanf(entrada, "%d", &livros[i].anoPublicacao);

        printf("Quantidade de Páginas: ");
        fgets(entrada, TAM_STRING, stdin);
        sscanf(entrada, "%d", &livros[i].qtdPaginas);
    }
}

void imprimirVetor(Livro livros[], int n) {
    printf("\n Lista de Livros \n");
    for (int i = 0; i < n; i++) {
        printf("%d - Título: %s  Autor: %s  Editora: %s  Ano: %d  Páginas: %d\n",
               i, livros[i].titulo, livros[i].autor, livros[i].editora,
               livros[i].anoPublicacao, livros[i].qtdPaginas);
    }
}

int buscarPorTitulo(Livro livros[], int n, const char *titulo) {
    for (int i = 0; i < n; i++) {
        if (strcmp(livros[i].titulo, titulo) == 0) {
            return i;
        }
    }
    return -1;
}

void ordenarPorTitulo(Livro livros[], int n) {
    Livro temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(livros[j].titulo, livros[j + 1].titulo) > 0) {
                temp = livros[j];
                livros[j] = livros[j + 1];
                livros[j + 1] = temp;
            }
        }
    }
}

int buscaBinariaPorTitulo(Livro livros[], int n, const char *titulo) {
    int inicio = 0, fim = n - 1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int cmp = strcmp(livros[meio].titulo, titulo);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int main() {
    Livro livros[MAX];
    int n;
    char entrada[TAM_STRING];
    char tituloBusca[TAM_STRING];

    printf("Quantos livros deseja cadastrar? ");
    fgets(entrada, TAM_STRING, stdin);
    sscanf(entrada, "%d", &n);

    preencherVetor(livros, n);

    printf("\n Antes da ordenação:");
    imprimirVetor(livros, n);

    ordenarPorTitulo(livros, n);

    printf("\n Após ordenação por título:");
    imprimirVetor(livros, n);

    printf("\n Digite o título para busca linear: ");
    fgets(tituloBusca, TAM_STRING, stdin);
    tituloBusca[strcspn(tituloBusca, "\n")] = '\0';
    int pos = buscarPorTitulo(livros, n, tituloBusca);
    if (pos != -1)
        printf("Livro encontrado na posição %d (busca linear).\n", pos);
    else
        printf("Livro não encontrado (busca linear).\n");

    printf("\nDigite o título para busca binária: ");
    fgets(tituloBusca, TAM_STRING, stdin);
    tituloBusca[strcspn(tituloBusca, "\n")] = '\0';
    pos = buscaBinariaPorTitulo(livros, n, tituloBusca);
    if (pos != -1)
        printf("Livro encontrado na posição %d (busca binária).\n", pos);
    else
        printf("Livro não encontrado (busca binária).\n");

    return 0;
}
