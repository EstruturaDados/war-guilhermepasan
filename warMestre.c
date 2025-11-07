#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* ---------- Funções auxiliares ---------- */
void padronizarMinusculo(char* str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower((unsigned char)str[i]);
}

void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n=== Cadastro do Território %d ===\n", i + 1);
        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %9s", mapa[i].cor);
        padronizarMinusculo(mapa[i].cor);
        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

void exibirMapa(Territorio* mapa, int n) {
    printf("\n=== MAPA ===\n");
    for (int i = 0; i < n; i++) {
        printf("%2d. %-15s | Cor: %-10s | Tropas: %2d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("================\n");
}

void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("? Não é possível atacar um território da mesma cor.\n");
        return;
    }
    if (atacante->tropas <= 1) {
        printf("? O atacante precisa ter mais de 1 tropa.\n");
        return;
    }

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;
    printf("\n?? Ataque: %s(%d) vs %s(%d)\n",
           atacante->nome, dadoA, defensor->nome, dadoD);

    if (dadoA > dadoD) {
        printf("? Vitória! %s conquista %s.\n", atacante->nome, defensor->nome);
        strcpy(defensor->cor, atacante->cor);
        int mov = atacante->tropas / 2;
        defensor->tropas = mov;
        atacante->tropas -= mov;
    } else {
        printf("??? Defesa venceu. Atacante perde 1 tropa.\n");
        atacante->tropas--;
    }
}

void atribuirMissao(char* destino, char* missoes[], int totalMissoes, const char* corJogador) {
    do {
        strcpy(destino, missoes[rand() % totalMissoes]);
        padronizarMinusculo(destino);
    } while (strstr(destino, corJogador) != NULL);
}

void exibirMissao(const char* missao) {
    printf("\n?? Sua missão: %s\n", missao);
}

int verificarMissao(char* missao, const char* corJogador, Territorio* mapa, int n) {
    if (strcmp(missao, "conquistar 3 territorios") == 0) {
        int cont = 0;
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, corJogador) == 0) cont++;
        return cont >= 3;
    }

    if (strcmp(missao, "controlar todos os territorios") == 0) {
        for (int i = 0; i < n; i++)
            if (strcmp(mapa[i].cor, corJogador) != 0) return 0;
        return 1;
    }

    return 0;
}

/* ---------- MAIN ---------- */
int main() {
    srand(time(NULL));

    int n;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);
    getchar();

    Territorio* mapa = calloc(n, sizeof(Territorio));
    if (!mapa) return 1;

    cadastrarTerritorios(mapa, n);
    exibirMapa(mapa, n);

    /* === Escolhe cor do jogador dentre as cadastradas === */
    char cores[10][10];
    int totalCores = 0;

    for (int i = 0; i < n; i++) {
        int jaExiste = 0;
        for (int j = 0; j < totalCores; j++)
            if (strcmp(cores[j], mapa[i].cor) == 0)
                jaExiste = 1;
        if (!jaExiste)
            strcpy(cores[totalCores++], mapa[i].cor);
    }

    if (totalCores == 0) {
        printf("Nenhuma cor cadastrada. Encerrando.\n");
        free(mapa);
        return 0;
    }

    const char* corJogador = cores[rand() % totalCores];
    printf("\n?? Sua cor será: %s\n", corJogador);

    /* === Missões === */
    char* missoes[] = {
        "conquistar 3 territorios",
        "controlar todos os territorios"
    };
    char missao[100];
    atribuirMissao(missao, missoes, 2, corJogador);
    exibirMissao(missao);

    /* === Loop principal === */
    int opcao, venceu = 0;
    do {
        printf("\n--- SEU TURNO (%s) ---\n", corJogador);
        printf("1. Atacar\n2. Ver mapa\n0. Sair\n> ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            exibirMapa(mapa, n);
            int ida, idd;
            printf("Atacante: "); scanf("%d", &ida);
            printf("Defensor: "); scanf("%d", &idd);
            if (ida < 1 || idd < 1 || ida > n || idd > n || ida == idd) {
                printf("Entrada inválida.\n");
                continue;
            }

            Territorio* at = &mapa[ida - 1];
            Territorio* de = &mapa[idd - 1];

            if (strcmp(at->cor, corJogador) != 0) {
                printf("Esse território não é seu!\n");
                continue;
            }

            atacar(at, de);

            if (verificarMissao(missao, corJogador, mapa, n)) {
                venceu = 1;
                printf("\n?? Você cumpriu sua missão!\n");
            }
        }
        else if (opcao == 2) exibirMapa(mapa, n);
        else if (opcao != 0) printf("Opção inválida.\n");

    } while (opcao != 0 && !venceu);

    if (venceu) printf("\n?? Parabéns, vitória!\n");
    else printf("\nJogo encerrado.\n");

    free(mapa);
    return 0;
}
