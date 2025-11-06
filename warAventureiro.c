#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ?? Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ?? Função para cadastrar os territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
	int i;
    for (i = 0; i < n; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %9s", mapa[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// ??? Função para exibir todos os territórios
void exibirMapa(Territorio* mapa, int n) {
    printf("\n=== ESTADO ATUAL DO MAPA ===\n");
    int i;
    for (i = 0; i < n; i++) {
        printf("%d. %-15s | Cor: %-10s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("==============================\n");
}

// ?? Função que simula um ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n?? Não é possível atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n?? O território atacante precisa de mais de 1 tropa para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n?? Rolagem dos dados:\n");
    printf("Atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Defensor  (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n?? O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf("\n??? O defensor resistiu! O atacante perde uma tropa.\n");
        atacante->tropas -= 1;
    }
}

// ?? Função para liberar memória alocada dinamicamente
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// ?? Função principal
int main() {
    srand(time(NULL)); // Garante aleatoriedade nos ataques

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    // Alocação dinâmica do vetor de territórios
    Territorio* mapa = (Territorio*)malloc(n * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);
    exibirMapa(mapa, n);

    int opcao;
    do {
        printf("\n--- MENU DE ATAQUE ---\n");
        printf("1. Realizar ataque\n");
        printf("2. Exibir mapa\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int iAtacante, iDefensor;

            printf("\nEscolha o território atacante (1 a %d): ", n);
            scanf("%d", &iAtacante);
            printf("Escolha o território defensor  (1 a %d): ", n);
            scanf("%d", &iDefensor);

            if (iAtacante < 1 || iAtacante > n || iDefensor < 1 || iDefensor > n) {
                printf("\n? Índice inválido!\n");
            } else if (iAtacante == iDefensor) {
                printf("\n?? Um território não pode atacar a si mesmo!\n");
            } else {
                atacar(&mapa[iAtacante - 1], &mapa[iDefensor - 1]);
            }
        } else if (opcao == 2) {
            exibirMapa(mapa, n);
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    printf("\n?? Memória liberada. Programa encerrado.\n");
    return 0;
}
