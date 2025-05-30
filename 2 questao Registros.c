#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 40

typedef struct {
    int codigo;
    char descricao[50];
    float valorUnitario;
    int quantidadeEstoque;
} Produto;

void cadastrarProduto(Produto produtos[], int *quantidade) {
    if (*quantidade >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }
    printf("\nCadastro de novo produto:\n");
    printf("Código: ");
    scanf("%d", &produtos[*quantidade].codigo);
    printf("Descrição: ");
    scanf(" %[^\n]", produtos[*quantidade].descricao);
    printf("Valor unitário: ");
    scanf("%f", &produtos[*quantidade].valorUnitario);
    printf("Quantidade em estoque: ");
    scanf("%d", &produtos[*quantidade].quantidadeEstoque);
    (*quantidade)++;
}

void alterarValorUnitario(Produto produtos[], int quantidade) {
    int cod;
    float novoValor;
    printf("Digite o código do produto para alterar o valor: ");
    scanf("%d", &cod);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == cod) {
            printf("Valor atual: %.2f\n", produtos[i].valorUnitario);
            printf("Novo valor: ");
            scanf("%f", &novoValor);
            produtos[i].valorUnitario = novoValor;
            printf("Valor atualizado com sucesso.\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

float obterValorUnitario(Produto produtos[], int quantidade, int cod) {
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == cod) {
            return produtos[i].valorUnitario;
        }
    }
    return -1;
}

int obterQuantidadeEstoque(Produto produtos[], int quantidade, int cod) {
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == cod) {
            return produtos[i].quantidadeEstoque;
        }
    }
    return -1;
}

void venderProduto(Produto produtos[], int quantidade) {
    int cod, qtdDesejada;
    printf("Código do produto: ");
    scanf("%d", &cod);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == cod) {
            if (produtos[i].quantidadeEstoque == 0) {
                printf("Produto com estoque zero.\n");
                return;
            }
            printf("Quantidade desejada: ");
            scanf("%d", &qtdDesejada);
            if (qtdDesejada <= produtos[i].quantidadeEstoque) {
                produtos[i].quantidadeEstoque -= qtdDesejada;
                float valor = qtdDesejada * produtos[i].valorUnitario;
                printf("Venda realizada. Valor a pagar: R$ %.2f\n", valor);
            } else {
                printf("Estoque insuficiente. Há apenas %d unidades.\n", produtos[i].quantidadeEstoque);
                printf("Deseja comprar o que há disponível? (1=sim / 0=não): ");
                int opcao;
                scanf("%d", &opcao);
                if (opcao == 1) {
                    float valor = produtos[i].quantidadeEstoque * produtos[i].valorUnitario;
                    printf("Venda parcial realizada. Valor a pagar: R$ %.2f\n", valor);
                    produtos[i].quantidadeEstoque = 0;
                } else {
                    printf("Venda cancelada.\n");
                }
            }
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void atualizarEstoque(Produto produtos[], int quantidade) {
    int cod, novaQtd;
    printf("Digite o código do produto: ");
    scanf("%d", &cod);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == cod) {
            printf("Quantidade atual: %d\n", produtos[i].quantidadeEstoque);
            printf("Nova quantidade: ");
            scanf("%d", &novaQtd);
            produtos[i].quantidadeEstoque = novaQtd;
            printf("Estoque atualizado.\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void exibirTodosProdutos(Produto produtos[], int quantidade) {
    printf("\nProdutos cadastrados:\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Código: %d | Descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
    }
}

void exibirProdutosZerados(Produto produtos[], int quantidade) {
    printf("\nProdutos com estoque zerado:\n");
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].quantidadeEstoque == 0) {
            printf("Código: %d | Descrição: %s\n", produtos[i].codigo, produtos[i].descricao);
        }
    }
}

int main() {
    Produto produtos[MAX_PRODUTOS];
    int quantidade = 0;
    int opcao;

    do {
        printf("\n===== MENU PAPELARIA =====\n");
        printf("1. Cadastrar novo produto\n");
        printf("2. Alterar valor unitário\n");
        printf("3. Consultar valor unitário\n");
        printf("4. Consultar quantidade em estoque\n");
        printf("5. Realizar venda\n");
        printf("6. Atualizar quantidade em estoque\n");
        printf("7. Exibir todos os produtos\n");
        printf("8. Exibir produtos com estoque zero\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        int cod;
        switch (opcao) {
            case 1: cadastrarProduto(produtos, &quantidade); break;
            case 2: alterarValorUnitario(produtos, quantidade); break;
            case 3:
                printf("Código do produto: ");
                scanf("%d", &cod);
                {
                    float valor = obterValorUnitario(produtos, quantidade, cod);
                    if (valor >= 0)
                        printf("Valor unitário: R$ %.2f\n", valor);
                    else
                        printf("Produto não encontrado.\n");
                }
                break;
            case 4:
                printf("Código do produto: ");
                scanf("%d", &cod);
                {
                    int qtd = obterQuantidadeEstoque(produtos, quantidade, cod);
                    if (qtd >= 0)
                        printf("Quantidade em estoque: %d\n", qtd);
                    else
                        printf("Produto não encontrado.\n");
                }
                break;
            case 5: venderProduto(produtos, quantidade); break;
            case 6: atualizarEstoque(produtos, quantidade); break;
            case 7: exibirTodosProdutos(produtos, quantidade); break;
            case 8: exibirProdutosZerados(produtos, quantidade); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
