#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100

typedef struct {
    int numeroConta;
    char nome[50];
    char cpf[15];
    char telefone[20];
    float saldo;
} Conta;

// (a) Função de busca
int buscarConta(Conta contas[], int total, int numero) {
    if (total == 0) return -2;
    for (int i = 0; i < total; i++) {
        if (contas[i].numeroConta == numero)
            return i;
    }
    return -1;
}

// (b) Procedimento para cadastrar nova conta
void cadastrarConta(Conta contas[], int *total) {
    if (*total >= MAX_CONTAS) {
        printf("Limite de contas atingido.\n");
        return;
    }

    int numero;
    printf("Digite o número da nova conta: ");
    scanf("%d", &numero);

    int pos = buscarConta(contas, *total, numero);
    if (pos >= 0) {
        printf("Número de conta já cadastrado. Operação cancelada.\n");
        return;
    }

    contas[*total].numeroConta = numero;
    printf("Nome do titular: ");
    scanf(" %[^\n]", contas[*total].nome);
    printf("CPF do titular: ");
    scanf(" %[^\n]", contas[*total].cpf);
    printf("Telefone: ");
    scanf(" %[^\n]", contas[*total].telefone);
    contas[*total].saldo = 0.0;
    (*total)++;
    printf("Conta cadastrada com sucesso!\n");
}

// (c) Procedimento para consultar saldo
void consultarSaldo(Conta contas[], int total) {
    int numero;
    printf("Digite o número da conta: ");
    scanf("%d", &numero);
    int pos = buscarConta(contas, total, numero);

    if (pos == -2 || pos == -1) {
        printf("Conta não encontrada.\n");
        return;
    }

    printf("Saldo da conta %d: R$ %.2f\n", numero, contas[pos].saldo);
}

// (d) Procedimento para depósito
void depositar(Conta contas[], int total) {
    int numero;
    float valor;
    printf("Número da conta para depósito: ");
    scanf("%d", &numero);
    int pos = buscarConta(contas, total, numero);

    if (pos < 0) {
        printf("Conta não encontrada.\n");
        return;
    }

    printf("Valor do depósito: ");
    scanf("%f", &valor);
    contas[pos].saldo += valor;
    printf("Depósito realizado com sucesso. Novo saldo: R$ %.2f\n", contas[pos].saldo);
}

// (e) Procedimento para saque
void sacar(Conta contas[], int total) {
    int numero;
    float valor;
    printf("Número da conta para saque: ");
    scanf("%d", &numero);
    int pos = buscarConta(contas, total, numero);

    if (pos < 0) {
        printf("Conta não encontrada.\n");
        return;
    }

    printf("Valor do saque: ");
    scanf("%f", &valor);

    if (contas[pos].saldo >= valor) {
        contas[pos].saldo -= valor;
        printf("Saque realizado com sucesso. Novo saldo: R$ %.2f\n", contas[pos].saldo);
    } else {
        printf("Saldo insuficiente.\n");
    }
}

// (f) Procedimento para exibir dados resumidos
void exibirContas(Conta contas[], int total) {
    printf("\nContas cadastradas:\n");
    for (int i = 0; i < total; i++) {
        printf("Conta: %d | Titular: %s | Telefone: %s\n",
               contas[i].numeroConta, contas[i].nome, contas[i].telefone);
    }
}

int main() {
    Conta corrente[MAX_CONTAS], poupanca[MAX_CONTAS];
    int totalCorrente = 0, totalPoupanca = 0;
    int tipo, opcao;

    do {
        printf("\n=== SISTEMA BANCO DINHEIRO CERTO ===\n");
        printf("1. Cadastrar nova conta\n");
        printf("2. Consultar saldo\n");
        printf("3. Depositar\n");
        printf("4. Sacar\n");
        printf("5. Exibir contas cadastradas\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao != 0) {
            printf("Tipo de conta (1 - Corrente | 2 - Poupança): ");
            scanf("%d", &tipo);
        }

        switch (opcao) {
            case 1:
                if (tipo == 1)
                    cadastrarConta(corrente, &totalCorrente);
                else
                    cadastrarConta(poupanca, &totalPoupanca);
                break;

            case 2:
                if (tipo == 1)
                    consultarSaldo(corrente, totalCorrente);
                else
                    consultarSaldo(poupanca, totalPoupanca);
                break;

            case 3:
                if (tipo == 1)
                    depositar(corrente, totalCorrente);
                else
                    depositar(poupanca, totalPoupanca);
                break;

            case 4:
                if (tipo == 1)
                    sacar(corrente, totalCorrente);
                else
                    sacar(poupanca, totalPoupanca);
                break;

            case 5:
                if (tipo == 1)
                    exibirContas(corrente, totalCorrente);
                else
                    exibirContas(poupanca, totalPoupanca);
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
