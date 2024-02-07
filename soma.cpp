#include <iostream>

// Função para verificar se um número pertence à sequência de Fibonacci
bool pertenceFibonacci(int n) {
    int a = 0, b = 1;
    while (b < n) {
        int temp = b;
        b = a + b;
        a = temp;
    }
    return b == n;
}

int main() {
    int numero;
    std::cout << "Digite um numero: ";
    std::cin >> numero;

    if (pertenceFibonacci(numero)) {
        std::cout << "O numero informado pertence a sequencia de Fibonacci." << std::endl;
    } else {
        std::cout << "O numero informado NAO pertence a sequencia de Fibonacci." << std::endl;
    }

    return 0;
}
