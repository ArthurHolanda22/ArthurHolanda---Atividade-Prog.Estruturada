#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTAS 100
#define TAM_NOME 100
#define TAM_CPF 15
#define TAM_TELEFONE 15
#define NOME_ARQUIVO_CONTAS "contas.dat"

typedef struct {
    int numeroConta;
    char nomeTitular[TAM_NOME];
    char cpf[TAM_CPF];
    char telefone[TAM_TELEFONE];
    float saldo;
    int ativa;
} ContaBancaria;

ContaBancaria contas[MAX_CONTAS];
int totalContas = 0;

void carregarContasDoArquivo() {
    FILE *fp = fopen(NOME_ARQUIVO_CONTAS, "rb");
    if (fp == NULL) {
        printf("Arquivo de contas não encontrado. Iniciando com nenhuma conta.\n");
        totalContas = 0;
        return;
    }
    totalContas = 0;
    while (fread(&contas[totalContas], sizeof(ContaBancaria), 1, fp) == 1) {
        totalContas++;
        if (totalContas >= MAX_CONTAS) {
            printf("Limite de contas excedido na leitura do arquivo. Algumas contas podem não ter sido carregadas.\n");
            break;
        }
    }
    fclose(fp);
    printf("Contas carregadas do arquivo %s.\n", NOME_ARQUIVO_CONTAS);
}

void salvarContasNoArquivo() {
    FILE *fp = fopen(NOME_ARQUIVO_CONTAS, "wb");
    if (fp == NULL) {
        printf("Erro ao criar/abrir o arquivo de contas para escrita.\n");
        return;
    }
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].ativa) {
            fwrite(&contas[i], sizeof(ContaBancaria), 1, fp);
        }
    }
    fclose(fp);
    printf("Contas salvas no arquivo %s.\n", NOME_ARQUIVO_CONTAS);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerString(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0;
}

int buscarConta(int numeroConta) {
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].ativa && contas[i].numeroConta == numeroConta) {
            return i;
        }
    }
    return -1;
}

void cadastrarNovaConta() {
    if (totalContas >= MAX_CONTAS) {
        printf("Limite máximo de contas atingido (%d).\n", MAX_CONTAS);
        return;
    }

    ContaBancaria novaConta;
    int numeroContaDigitado;

    printf("\n--- Cadastro de Nova Conta ---\n");
    printf("Número da Conta (inteiro): ");
    scanf("%d", &numeroContaDigitado);
    limparBuffer();

    if (buscarConta(numeroContaDigitado) != -1) {
        printf("Erro: Já existe uma conta com o número %d. Cadastro não permitido.\n", numeroContaDigitado);
        return;
    }

    novaConta.numeroConta = numeroContaDigitado;

    printf("Nome do Titular: ");
    lerString(novaConta.nomeTitular, TAM_NOME);

    printf("CPF do Titular: ");
    lerString(novaConta.cpf, TAM_CPF);

    printf("Telefone de Contato: ");
    lerString(novaConta.telefone, TAM_TELEFONE);

    printf("Saldo Inicial: R$ ");
    scanf("%f", &novaConta.saldo);
    limparBuffer();

    novaConta.ativa = 1;

    contas[totalContas] = novaConta;
    totalContas++;

    printf("Conta %d cadastrada com sucesso!\n", novaConta.numeroConta);
    salvarContasNoArquivo();
}

void consultarSaldo() {
    int numeroConta;
    printf("Número da Conta para consulta de saldo: ");
    scanf("%d", &numeroConta);
    limparBuffer();

    int indice = buscarConta(numeroConta);
    if (indice != -1) {
        printf("--- Saldo da Conta %d ---\n", contas[indice].numeroConta);
        printf("Titular: %s\n", contas[indice].nomeTitular);
        printf("Saldo Atual: R$ %.2f\n", contas[indice].saldo);
    } else {
        printf("Conta %d não encontrada ou não está cadastrada.\n", numeroConta);
    }
}

void fazerDeposito() {
    int numeroConta;
    float valorDeposito;

    printf("Número da Conta para depósito: ");
    scanf("%d", &numeroConta);
    limparBuffer();

    int indice = buscarConta(numeroConta);
    if (indice != -1) {
        printf("Conta encontrada: %s. Saldo atual: R$ %.2f\n", contas[indice].nomeTitular, contas[indice].saldo);
        printf("Valor do Depósito: R$ ");
        scanf("%f", &valorDeposito);
        limparBuffer();

        if (valorDeposito > 0) {
            contas[indice].saldo += valorDeposito;
            printf("Depósito de R$ %.2f realizado com sucesso na conta %d.\n", valorDeposito, numeroConta);
            printf("Novo saldo: R$ %.2f\n", contas[indice].saldo);
            salvarContasNoArquivo();
        } else {
            printf("Valor de depósito inválido. Deve ser maior que zero.\n");
        }
    } else {
        printf("Conta %d não encontrada ou não está cadastrada.\n", numeroConta);
    }
}

void fazerSaque() {
    int numeroConta;
    float valorSaque;

    printf("Número da Conta para saque: ");
    scanf("%d", &numeroConta);
    limparBuffer();

    int indice = buscarConta(numeroConta);
    if (indice != -1) {
        printf("Conta encontrada: %s. Saldo atual: R$ %.2f\n", contas[indice].nomeTitular, contas[indice].saldo);
        printf("Valor do Saque: R$ ");
        scanf("%f", &valorSaque);
        limparBuffer();

        if (valorSaque <= 0) {
            printf("Valor de saque inválido. Deve ser maior que zero.\n");
        } else if (contas[indice].saldo >= valorSaque) {
            contas[indice].saldo -= valorSaque;
            printf("Saque de R$ %.2f realizado com sucesso na conta %d.\n", valorSaque, numeroConta);
            printf("Novo saldo: R$ %.2f\n", contas[indice].saldo);
            salvarContasNoArquivo();
        } else {
            printf("Saldo insuficiente. Saldo disponível: R$ %.2f. Valor solicitado: R$ %.2f.\n",
                   contas[indice].saldo, valorSaque);
        }
    } else {
        printf("Conta %d não encontrada ou não está cadastrada.\n", numeroConta);
    }
}

void exibirTodasContas() {
    if (totalContas == 0) {
        printf("Nenhuma conta cadastrada.\n");
        return;
    }

    printf("\n--- Todas as Contas Cadastradas ---\n");
    printf("--------------------------------------------------------------------------\n");
    printf("| Nº Conta | Nome do Titular                   | CPF             | Telefone       |\n");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].ativa) {
            printf("| %-9d| %-33s | %-15s | %-14s |\n",
                   contas[i].numeroConta,
                   contas[i].nomeTitular,
                   contas[i].cpf,
                   contas[i].telefone);
        }
    }
    printf("--------------------------------------------------------------------------\n");
}

void removerConta() {
    int numeroConta;
    printf("Número da Conta a ser removida: ");
    scanf("%d", &numeroConta);
    limparBuffer();

    int indice = buscarConta(numeroConta);
    if (indice != -1) {
        int confirmacao;
        printf("Tem certeza que deseja remover a conta %d - %s? (1 para sim / 0 para não): ", contas[indice].numeroConta, contas[indice].nomeTitular);
        scanf("%d", &confirmacao);
        limparBuffer();

        if (confirmacao == 1) {
            contas[indice].ativa = 0;
            printf("Conta %d removida (marcada como inativa).\n", numeroConta);
            salvarContasNoArquivo();
        } else {
            printf("Remoção de conta cancelada.\n");
        }
    } else {
        printf("Conta %d não encontrada ou já está inativa.\n", numeroConta);
    }
}

int main() {
    carregarContasDoArquivo();

    int opcao;
    do {
        printf("\n========== BANCO BRASILEIRO ==========\n");
        printf("1. Cadastrar Nova Conta\n");
        printf("2. Consultar Saldo\n");
        printf("3. Fazer Depósito\n");
        printf("4. Fazer Saque\n");
        printf("5. Exibir Todas as Contas\n");
        printf("6. Remover Conta (Lógica)\n");
        printf("0. Sair do Programa\n");
        printf("===========================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: cadastrarNovaConta(); break;
            case 2: consultarSaldo(); break;
            case 3: fazerDeposito(); break;
            case 4: fazerSaque(); break;
            case 5: exibirTodasContas(); break;
            case 6: removerConta(); break;
            case 0: printf("Obrigado por usar o Banco Brasileiro. Até logo!\n"); break;
            default: printf("Opção inválida. Por favor, tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (opcao != 0);

    return 0;
}
