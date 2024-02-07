#include <stdio.h>

// Função para obter o comprimento de uma string
int comprimentoString(char string[]) {
    int comprimento = 0;
    while (string[comprimento] != '\0') {
        comprimento++;
    }
    return comprimento;
}

// Função para inverter os caracteres de uma string
void inverterString(char string[]) {
    int comprimento = comprimentoString(string);
    for (int i = 0; i < comprimento / 2; i++) {
        char temp = string[i];
        string[i] = string[comprimento - 1 - i];
        string[comprimento - 1 - i] = temp;
    }
}

int main() {
    char string[] = "exemplo";

    printf("String original: %s\n", string);

    // Chamando a função para inverter a string
    inverterString(string);

    printf("String invertida: %s\n", string);

    return 0;
}
