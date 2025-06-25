#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    float preco;
    int quantidade;
} Item;

int main() {
    FILE *menu = fopen("menu.txt", "r");
    if (menu == NULL) {
        printf("Erro ao abrir menu.txt\n");
        return 1;
    }

    int qtd_itens;
    fscanf(menu, "%d", &qtd_itens);

    Item itens[qtd_itens];

    // Ler menu
    for (int i = 0; i < qtd_itens; i++) {
        fscanf(menu, "%s %f", itens[i].nome, &itens[i].preco);
        itens[i].quantidade = 0;
    }

    rewind(menu); // Se quiser reler, mas aqui não é necessário
    fclose(menu);

    // Exibir menu
    printf("\n===== MENU =====\n");
    for (int i = 0; i < qtd_itens; i++) {
        printf("%d - %s (R$ %.2f)\n", i + 1, itens[i].nome, itens[i].preco);
    }
    printf("================\n");

    // Fazer pedido
    int escolha, qtd;
    do {
        printf("Digite o número do item (0 para finalizar): ");
        scanf("%d", &escolha);

        if (escolha > 0 && escolha <= qtd_itens) {
            printf("Quantidade de %s: ", itens[escolha - 1].nome);
            scanf("%d", &qtd);
            itens[escolha - 1].quantidade += qtd;
        } else if (escolha != 0) {
            printf("Item inválido.\n");
        }
    } while (escolha != 0);

    // Gerar boleto
    FILE *boleto = fopen("boleto.txt", "w");
    if (boleto == NULL) {
        printf("Erro ao criar boleto.txt\n");
        return 1;
    }

    float total = 0;
    fprintf(boleto, "======= BOLETO =======\n");
    for (int i = 0; i < qtd_itens; i++) {
        if (itens[i].quantidade > 0) {
            float subtotal = itens[i].quantidade * itens[i].preco;
            fprintf(boleto, "%s x%d - R$ %.2f\n", itens[i].nome, itens[i].quantidade, subtotal);
            total += subtotal;
        }
    }
    fprintf(boleto, "-----------------------\n");
    fprintf(boleto, "TOTAL: R$ %.2f\n", total);
    fprintf(boleto, "=======================\n");

    fclose(boleto);

    printf("\nBoleto gerado em 'boleto.txt'.\n");

    return 0;
}
