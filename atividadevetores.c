#include <stdio.h>

#define MAX 50

void imprimirVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int buscaBinaria(int vetor[], int tamanho, int valor) {
    int inicio = 0, fim = tamanho - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (vetor[meio] == valor) return meio;
        else if (vetor[meio] < valor) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

void removerElemento(int vetor[], int *tamanho, int valor) {
    int pos = buscaBinaria(vetor, *tamanho, valor);
    if (pos == -1) {
        printf("Valor nao encontrado.\n");
        return;
    }
    for (int i = pos; i < *tamanho - 1; i++) {
        vetor[i] = vetor[i + 1];
    }
    (*tamanho)--;
}

void inserirOrdenado(int vetor[], int tam, int valor) {
    
    int i;
    int j;
    for (i = 0; i < tam; i++) {
        if (vetor[i] > valor) {
                break;
            }
        }
    for (j = (tam); j > i; j--) {
        vetor[j] = vetor[j - 1];
        }
        vetor[i] = valor;
        //(tam)++;
    
    
    
}

int main() {
    int vetor[MAX], tamanho, opcao, valor;
    
    do {
        printf("Digite o tamanho do vetor (3 a 50): ");
        scanf("%d", &tamanho);
    } while (tamanho < 3 || tamanho > MAX);
    
    printf("Digite %d valores :\n", tamanho);
    for (int i = 0; i < tamanho; i++) {
        printf("Insira o valor %d: ", i + 1);
        scanf("%d", &valor);
        inserirOrdenado(vetor, tamanho, valor);
        //tamanho++;
    }
    
    do {
        printf("\nMenu:\n1. Imprimir vetor\n2. Consultar elemento\n3. Remover elemento\n4. Inserir elemento\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                imprimirVetor(vetor, tamanho);
                break;
            case 2:
                printf("Digite o valor a buscar: ");
                scanf("%d", &valor);
                printf("Posicao: %d\n", buscaBinaria(vetor, tamanho, valor));
                break;
            case 3:
                printf("Digite o valor a remover: ");
                scanf("%d", &valor);
                removerElemento(vetor, &tamanho, valor);
                break;
            case 4:
                printf("Digite o valor a inserir: ");
                scanf("%d", &valor);
                inserirOrdenado(vetor, tamanho, valor);
                tamanho++;
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    
    return 0;
}
