#include <stdio.h>   // Biblioteca padrão de entrada e saída
#include <string.h>  // Biblioteca usada para manipular strings

#define MAX_TERRITORIOS 5 // Constante da quantidade máxima de territórios

// Definição da estrutura (struct) que representa um território
struct Territorio {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército
    int tropas;     // Quantidade de tropas
};	

int main() {
    // Declaração de um vetor do tipo Territorio
    struct Territorio territorios[MAX_TERRITORIOS];
    int i; // Variável de índice

    // Loop para o cadastro dos 5 territórios
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("=== Cadastro do Território %d ===\n", i + 1);

        printf("Digite o nome do território: ");
        // Leitura do nome (permite espaços)
        fgets(territorios[i].nome, 30, stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o '\n'

        printf("Digite a cor do exército: ");
        fgets(territorios[i].cor, 10, stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // remove o '\n'

        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        getchar(); // limpa o '\n' deixado no buffer do teclado

        printf("\n");
    }

    // Exibição dos dados cadastrados
    printf("\n=== Estado Atual dos Territórios ===\n");
    for (i = 0; i < MAX_TERRITORIOS; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Número de Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
