#include <stdio.h>
#include <string.h>

#define MAX_PRODUTOS 40
#define TAM_DESCRICAO 50

typedef struct {
    int codigo;
    char descricao[TAM_DESCRICAO];
    float valorUnitario;
    int quantidadeEstoque;
} Produto;

int tamanhoVetorProdutos =0;
void lerStr(char *str, int count);
void lerProdutos(Produto produtos[]);


void lerStr(char *str, int count) {
  fgets(str, count, stdin);
  int tam = strlen(str);
  if (tam > 0 && str[tam - 1] == '\n') {
    str[tam - 1] = '\0';
  }
}
void cadastrarProduto(Produto produtos[], int tamanhoVetor) {
    char tempStr[256];
    if ( tamanhoVetor >= MAX_PRODUTOS) {
        printf("Limite máximo de produtos atingido. %d\n", tamanhoVetor);
        return;
    } else {
        printf("%d\n",tamanhoVetor);
    }
    
    printf("\nCadastro de novo produto:\n");
    printf("Código: ");
    scanf("%d", &produtos[tamanhoVetor].codigo);
    printf("Descrição: ");
    //lerStr(produtos[tamanhoVetor].descricao, TAM_DESCRICAO);
    scanf("%s", produtos[tamanhoVetor].descricao);
    printf("Valor unitário: ");
    scanf("%f", &produtos[tamanhoVetor].valorUnitario);
    printf("Quantidade inicial do estoque: ");
    scanf("%d", &produtos[tamanhoVetor].quantidadeEstoque);
    lerStr(tempStr, 256);
    tamanhoVetorProdutos++;
    
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




void obterValorUnitario(Produto produtos[], int quantidade) {
    int cod;
    int achou = 0;
    printf("Digite o código do produto para busca: ");
    scanf("%d", &cod);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == cod) {
            printf("Valor unitario do produto %d - %s: %.2f\n", cod, produtos[i].descricao, produtos[i].valorUnitario);
            achou = 1;
        }
    }
    if (!achou) printf("Produto %d não encontrado\n", cod);
    
}

void obterQuantidadeEstoque(Produto produtos[], int quantidade) {
    int cod;
    int achou = 0;
    printf("Digite o código do produto para busca: ");
    scanf("%d", &cod);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == cod) {
            printf("A quantidade em estoque do produto %d - %s: %d\n", cod, produtos[i].descricao, produtos[i].quantidadeEstoque);
            achou = 1;
        }
    }
    if (!achou)  printf("Produto %d não encontrado\n", cod);
}

void venderProduto(Produto produtos[], int quantidade) {
    int cod, qtdDesejada, achou=0;
    printf("Informe o Código do produto a ser vendido: ");
    scanf("%d", &cod);
    for (int i = 0; i < quantidade; i++) {
        if (produtos[i].codigo == cod) {
            if (produtos[i].quantidadeEstoque == 0) {
                printf("Produto com estoque zero.\n");
                return;
            } else {
                printf("Quantidade desejada: ");
                scanf("%d", &qtdDesejada);
                if (qtdDesejada <= produtos[i].quantidadeEstoque) {
                    produtos[i].quantidadeEstoque -= qtdDesejada;
                    float valor = qtdDesejada * produtos[i].valorUnitario;
                    printf("Código: %d | Descrição: %s | Valor unitário: %.2f | Quantidade vendida: %d\n", produtos[i].codigo, produtos[i].descricao, produtos[i].valorUnitario, qtdDesejada);
                    printf("Venda realizada. Valor a pagar: R$ %.2f\n", valor);
                } else {
                    printf("Estoque insuficiente. Há apenas %d unidades.\n", produtos[i].quantidadeEstoque);
                    printf("Deseja comprar o que há disponível? (1=sim / 0=não): ");
                    int opcao;
                    scanf("%d", &opcao);
                    if (opcao == 1) {
                        float valor = produtos[i].quantidadeEstoque * produtos[i].valorUnitario;
                        printf("Código: %d | Descrição: %s | Valor unitário: %.2f | Quantidade vendida: %d\n", produtos[i].codigo, produtos[i].descricao, produtos[i].valorUnitario, produtos[i].quantidadeEstoque);
                        printf("Venda parcial realizada. Valor a pagar: R$ %.2f\n", valor);
                        produtos[i].quantidadeEstoque = 0;
                    } else {
                        printf("Venda cancelada.\n");
                    }
                }
            }
            return;
        }
    }
    if (!achou) printf("Produto não encontrado.\n");
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
            printf("Código: %d | Descrição: %s | Valor unitário: %f | Quantidade no Estoque: %d\n", produtos[i].codigo, produtos[i].descricao, produtos[i].valorUnitario, produtos[i].quantidadeEstoque);
            printf("Estoque atualizado.\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void exibirTodosProdutos(Produto produtos[], int tamanho) {
    printf("\nProdutos cadastrados:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Código: %d | Descrição: %s | Valor unitário: %.2f | Quantidade em estoque: %d\n", produtos[i].codigo, produtos[i].descricao, produtos[i].valorUnitario, produtos[i].quantidadeEstoque);
    }
}

void exibirProdutosZerados(Produto produtos[], int tamanho) {
    printf("\nProdutos com estoque zerado:\n");
    for (int i = 0; i < tamanho; i++) {
        if (produtos[i].quantidadeEstoque == 0) {
            printf("Código: %d | Descrição: %s | Valor unitário: %.2f | Quantidade em estoque: %d\n", produtos[i].codigo, produtos[i].descricao, produtos[i].valorUnitario, produtos[i].quantidadeEstoque);
        }
    }
}

int main() {
    Produto produtos[MAX_PRODUTOS];
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
            case 1:
                cadastrarProduto(produtos, tamanhoVetorProdutos); 
                break;
            case 2: alterarValorUnitario(produtos, tamanhoVetorProdutos); 
                break;
            case 3: obterValorUnitario(produtos, tamanhoVetorProdutos);
                break;
            case 4:obterQuantidadeEstoque(produtos, tamanhoVetorProdutos);
                break;
            case 5: venderProduto(produtos, tamanhoVetorProdutos);
            printf("Opção Vender Produto selecionado.\n"); 
            break;
            case 6: atualizarEstoque(produtos, tamanhoVetorProdutos); 
            printf("Opção Atualizar Estoque selecionado.\n");
            break;
            case 7: 
                exibirTodosProdutos(produtos, tamanhoVetorProdutos);
            printf("Opção Exibir Todos os Produtos selecionados.\n"); 
            break;
            case 8: 
                exibirProdutosZerados(produtos, tamanhoVetorProdutos);
            printf("Opção Exibir Produtos Zerados selecionada.\n"); 
            break;
            case 0: 
            printf("Saindo...\n"); 
            break;
            default:
            printf("Opção inválida.\n");
            break;
        }
} while (opcao != 0);

    return 0;
}
