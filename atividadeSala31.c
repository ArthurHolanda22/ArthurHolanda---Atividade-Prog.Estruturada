#include <stdio.h>

int contarVogais(char frase[]) {
    int i = 0;
    int vogais = 0;

    while (frase[i] != '\0') {
        if (frase[i] == 'a') vogais++;
        if (frase[i] == 'A') vogais++;
        if (frase[i] == 'e') vogais++;
        if (frase[i] == 'E') vogais++;
        if (frase[i] == 'i') vogais++;
        if (frase[i] == 'I') vogais++;
        if (frase[i] == 'o') vogais++;
        if (frase[i] == 'O') vogais++;
        if (frase[i] == 'u') vogais++;
        if (frase[i] == 'U') vogais++;
        i++;
    }

    return vogais;
}

void colocarIniciaisMaiusculas(char frase[]) {
    int i = 0;
    int nova_palavra = 1;

    while (frase[i] != '\0') {
        if (frase[i] == ' ') {
            nova_palavra = 1;
        } else {
            if (nova_palavra == 1) {
                if (frase[i] >= 'a' && frase[i] <= 'z') {
                    frase[i] = frase[i] - 32;
                }
                nova_palavra = 0;
            }
        }
        i++;
    }
}

int main() {
    char frase[201];

    printf("Digite uma frase: ");
    scanf(" %[^\n]s", frase);

    printf("\nFrase digitada: %s\n", frase);

    int total = contarVogais(frase);
    printf("Número de vogais: %d\n", total);

    colocarIniciaisMaiusculas(frase);
    printf("Frase com iniciais maiúsculas: %s\n", frase);

    return 0;
}
