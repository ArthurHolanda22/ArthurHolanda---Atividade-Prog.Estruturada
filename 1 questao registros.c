#include <stdio.h>
#include <string.h>

#define TAM 27
#define TAM_NOME 30

typedef struct {
    char nome[TAM_NOME];
    int veiculos;
    int acidentes;
} Estado;

void lerStr(char *str, int count);
void lerDados(Estado estados[]);

void lerStr(char *str, int count) {
  fgets(str, count, stdin);
  int tam = strlen(str);
  if (tam > 0 && str[tam - 1] == '\n') {
    str[tam - 1] = '\0';
  }
}

// (a) Procedimento para coletar os dados dos 26 estados
void lerDados(Estado estados[]) {
    char tempStr[256];
    for (int i = 0; i < TAM; i++) {
        printf("\nEstado %d:\n", i+1);
        printf("Nome: ");
        lerStr(estados[i].nome,TAM_NOME);
        printf("Número de veículos em 2007: ");
        scanf("%d", &estados[i].veiculos);
        printf("Número de acidentes em 2007: ");
        scanf("%d", &estados[i].acidentes);
        lerStr(tempStr, 256); 
    }
}

// (b) Procedimento para encontrar índices do maior e menor número de acidentes
void encontrarExtremos(Estado estados[], int *indMenor, int *indMaior) {
    *indMenor = 0;
    *indMaior = 0;
    for (int i = 1; i < TAM; i++) {
        if (estados[i].acidentes < estados[*indMenor].acidentes) {
            *indMenor = i;
        }
        if (estados[i].acidentes > estados[*indMaior].acidentes) {
            *indMaior = i;
        }
    }
}

// (c) Função para calcular o percentual de veículos envolvidos em acidentes em um estado
float percentualAcidentes(Estado estados[], int i) {
    if (estados[i].veiculos == 0) return 0.0;
    return (100.0 * estados[i].acidentes) / estados[i].veiculos;
}

// (d) Função para calcular a média de acidentes no país
float mediaAcidentes(Estado estados[]) {
    int total = 0;
    for (int i = 0; i < TAM; i++) {
        total += estados[i].acidentes;
    }
    return total / (float)TAM;
}

// (e) Procedimento para exibir os estados com acidentes acima da média
void exibirAcimaMedia(Estado estados[], float media) {
    printf("\nEstados com número de acidentes acima da média nacional (%.2f):\n", media);
    for (int i = 0; i < TAM; i++) {
        if (estados[i].acidentes > media) {
            printf("%s - Acidentes: %d\n", estados[i].nome, estados[i].acidentes);
        }
    }
}

int main() {
    Estado estados[TAM];
    int indMenor, indMaior;
    float media;

    // (a)
    lerDados(estados);

    // (b)
    encontrarExtremos(estados, &indMenor, &indMaior);
    printf("\nEstado com MENOR número de acidentes: %s (%d acidentes)\n",
           estados[indMenor].nome, estados[indMenor].acidentes);
    printf("Estado com MAIOR número de acidentes: %s (%d acidentes)\n",
           estados[indMaior].nome, estados[indMaior].acidentes);

    // (c)
    printf("\nPercentual de veículos envolvidos em acidentes por estado:\n");
    for (int i = 0; i < TAM; i++) {
        float p = percentualAcidentes(estados, i);
        printf("%s: %.2f%%\n", estados[i].nome, p);
    }

    // (d)
    media = mediaAcidentes(estados);
    printf("\nMédia de acidentes no país: %.2f\n", media);

    // (e)
    exibirAcimaMedia(estados, media);

    return 0;
}
