#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>

#define TAMANHO_MES 30 // Assumindo um mÃªs de 30 dias

int main() {
    FILE *arquivo;
    char buffer[1024];
    json_t *root;
    json_error_t error;

    // Abre o arquivo JSON
    arquivo = fopen("faturamento.json", "r");
    if (!arquivo) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        return 1;
    }

    // LÃª o conteÃºdo do arquivo JSON
    fread(buffer, 1024, 1, arquivo);
    fclose(arquivo);

    // Faz o parsing do JSON
    root = json_loads(buffer, 0, &error);
    if (!root) {
        fprintf(stderr, "Erro ao fazer parsing do JSON: %s\n", error.text);
        return 1;
    }

    // ObtÃ©m o array de faturamento diÃ¡rio
    json_t *faturamento_diario = json_object_get(root, "faturamento_diario");

    // VariÃ¡veis para calcular a mÃ©dia mensal e o nÃºmero de dias acima da mÃ©dia
    double soma = 0.0;
    int dias_acima_media = 0;
    int menor_valor = INT_MAX;
    int maior_valor = INT_MIN;

    // Calcula a mÃ©dia mensal e encontra o menor e maior valor de faturamento
    for (int i = 0; i < TAMANHO_MES; i++) {
        int valor_diario = json_integer_value(json_array_get(faturamento_diario, i));
        if (valor_diario > 0) { // Ignora os dias sem faturamento
            soma += valor_diario;
            if (valor_diario < menor_valor) {
                menor_valor = valor_diario;
            }
            if (valor_diario > maior_valor) {
                maior_valor = valor_diario;
            }
        }
    }

    // Calcula a mÃ©dia mensal
    double media = soma / (TAMANHO_MES - dias_acima_media);

    // Conta o nÃºmero de dias em que o faturamento foi superior Ã  mÃ©dia
    for (int i = 0; i < TAMANHO_MES; i++) {
        int valor_diario = json_integer_value(json_array_get(faturamento_diario, i));
        if (valor_diario > media) {
            dias_acima_media++;
        }
    }

    // Imprime os resultados
    printf("Menor valor de faturamento diario: %d\n", menor_valor);
    printf("Maior valor de faturamento diario: %d\n", maior_valor);
    printf("Numero de dias com faturamento acima da media mensal: %d\n", dias_acima_media);

    // Libera a memÃ³ria alocada para o JSON
    json_decref(root);

    return 0;
}
