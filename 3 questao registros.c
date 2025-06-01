#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTAS 100 // Máximo de 100 contas
#define TAM_NOME 100
#define TAM_CPF 15   // Ex: "123.456.789-00\0"
#define TAM_TELEFONE 15 // Ex: "(XX) XXXXX-XXXX\0"
#define NOME_ARQUIVO_CONTAS "contas.dat" // Nome do arquivo binário para persistência

// Estrutura para representar uma conta bancária
typedef struct {
    int numeroConta;
    char nomeTitular[TAM_NOME];
    char cpf[TAM_CPF];
    char telefone[TAM_TELEFONE];
    float saldo;
    int ativa; // 1 se a conta estiver ativa, 0 se estiver "removida" logicamente
} ContaBancaria;

// Variáveis globais para gerenciar o array de contas em memória
ContaBancaria contas[MAX_CONTAS];
int totalContas = 0; // Número de contas atualmente no array

// --- Funções de Manipulação de Arquivos ---

// Carrega as contas do arquivo binário para a memória
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

// Salva as contas da memória para o arquivo binário
void salvarContasNoArquivo() {
    FILE *fp = fopen(NOME_ARQUIVO_CONTAS, "wb");
    if (fp == NULL) {
        printf("Erro ao criar/abrir o arquivo de contas para escrita.\n");
        return;
    }
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].ativa) { // Salva apenas contas ativas
            fwrite(&contas[i], sizeof(ContaBancaria), 1, fp);
        }
    }
    fclose(fp);
    printf("Contas salvas no arquivo %s.\n", NOME_ARQUIVO_CONTAS);
}

// --- Funções Auxiliares de Entrada/Saída ---

// Consome o caractere de nova linha pendente no buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler strings de forma segura
void lerString(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove a quebra de linha
}

// --- Subprogramas Conforme a Questão ---

// (a) Função de busca
// Retorna o índice da conta no array 'contas' se encontrada, ou -1 caso contrário.
int buscarConta(int numeroConta) {
    for (int i = 0; i < totalContas; i++) {
        if (contas[i].ativa && contas[i].numeroConta == numeroConta) {
            return i; // Conta encontrada na posição i
        }
    }
    return -1; // Conta não encontrada
}

// (b) Procedimento para cadastrar uma nova conta
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
    limparBuffer(); // Limpa o buffer após scanf

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

    novaConta.ativa = 1; // Marca a conta como ativa

    contas[totalContas] = novaConta;
    totalContas++;

    printf("Conta %d cadastrada com sucesso!\n", novaConta.numeroConta);
    salvarContasNoArquivo(); // Salva imediatamente após o cadastro
}

// (c) Procedimento para consultar o saldo de uma conta
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

// (d) Procedimento para fazer um depósito em uma conta
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
            salvarContasNoArquivo(); // Salva após a alteração
        } else {
            printf("Valor de depósito inválido. Deve ser maior que zero.\n");
        }
    } else {
        printf("Conta %d não encontrada ou não está cadastrada.\n", numeroConta);
    }
}

// (e) Procedimento para fazer um saque em uma conta
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
            salvarContasNoArquivo(); // Salva após a alteração
        } else {
            printf("Saldo insuficiente. Saldo disponível: R$ %.2f. Valor solicitado: R$ %.2f.\n",
                   contas[indice].saldo, valorSaque);
        }
    } else {
        printf("Conta %d não encontrada ou não está cadastrada.\n", numeroConta);
    }
}

// (f) Procedimento para exibir o número da conta, o nome do titular e o telefone de contato para todas as contas.
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

// Função para "remover" uma conta logicamente (marcar como inativa)
void removerConta() {
    int numeroConta;
    printf("Número da Conta a ser removida: ");
    scanf("%d", &numeroConta);
    limparBuffer();

    int indice = buscarConta(numeroConta);
    if (indice != -1) {
        int confirmacao; // Alterado para int
        printf("Tem certeza que deseja remover a conta %d - %s? (1 para sim / 0 para não): ", contas[indice].numeroConta, contas[indice].nomeTitular); // Mensagem atualizada
        scanf("%d", &confirmacao); // Lendo um inteiro
        limparBuffer();

        if (confirmacao == 1) { // Verificando se é 1
            contas[indice].ativa = 0; // Marca como inativa
            printf("Conta %d removida (marcada como inativa).\n", numeroConta);
            salvarContasNoArquivo(); // Salva para remover do arquivo na próxima carga
        } else {
            printf("Remoção de conta cancelada.\n");
        }
    } else {
        printf("Conta %d não encontrada ou já está inativa.\n", numeroConta);
    }
}

// --- Função Principal (Main) e Menu ---

int main() {
    carregarContasDoArquivo(); // Carrega as contas existentes ao iniciar o programa

    int opcao;
    do {
        printf("\n========== BANCO DINHEIRO CERTO ==========\n");
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
        limparBuffer(); // Limpa o buffer após scanf

        switch (opcao) {
            case 1: cadastrarNovaConta(); break;
            case 2: consultarSaldo(); break;
            case 3: fazerDeposito(); break;
            case 4: fazerSaque(); break;
            case 5: exibirTodasContas(); break;
            case 6: removerConta(); break;
            case 0: printf("Obrigado por usar o Banco Dinheiro Certo. Até logo!\n"); break;
            default: printf("Opção inválida. Por favor, tente novamente.\n");
        }

        // Pausa para o usuário ver a saída antes de limpar a tela (opcional)
        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();
            // system("cls"); // Descomente para limpar a tela no Windows
            // system("clear"); // Descomente para limpar a tela no Linux/macOS
        }

    } while (opcao != 0);

    return 0;
}
