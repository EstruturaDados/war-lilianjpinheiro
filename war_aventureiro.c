#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Constantes ---
#define MAX_TERRITORIOS 5

// --- Estrutura ---
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// --- Limpar buffer ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Mostrar mapa ---
void mostrarMapa(struct Territorio *territorios, int total) {
    printf("\n===========================================\n");
    printf("        MAPA DO MUNDO - ATUAL\n");
    printf("===========================================\n");

    for (int i = 0; i < total; i++) {
        printf("[%d] %s | Exército: %s | Tropas: %d\n",
               i + 1,
               territorios[i].nome,
               territorios[i].cor,
               territorios[i].tropas);
    }
    printf("\n");
}

// --- Função de ataque ---
void simularAtaque(struct Territorio *atacante, struct Territorio *defensor) {
    if (atacante->tropas <= 1) {
        printf("\n⚠️ Território atacante precisa de mais de 1 tropa!\n");
        return;
    }

    printf("\n⚔️ ATAQUE INICIADO: %s -> %s\n", atacante->nome, defensor->nome);

    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("🎲 Dado Ataque: %d\n", dadoAtaque);
    printf("🎲 Dado Defesa: %d\n", dadoDefesa);

    if (dadoAtaque > dadoDefesa) {
        defensor->tropas--;
        atacante->tropas++;
        printf("✅ Ataque venceu! Defensor transfere 1 tropa.\n");
    } else if (dadoDefesa > dadoAtaque) {
        atacante->tropas--;
        defensor->tropas++;
        printf("❌ Defesa venceu! Atacante transfere1 tropa.\n");
    } else {
        printf("🤝 Empate! Nada acontece.\n");
    }

    // Verifica conquista
    if (defensor->tropas <= 0) {
        printf("\n🏴 Território conquistado!\n");

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = 1;
        atacante->tropas--;

        printf("Agora %s pertence ao exército %s\n",
               defensor->nome, defensor->cor);
    }
}

// --- MAIN ---
int main() {

    srand(time(NULL)); // inicializa random

    // 🔥 ALOCAÇÃO DINÂMICA
    struct Territorio *territorios =
        (struct Territorio *) calloc(MAX_TERRITORIOS, sizeof(struct Territorio));

    if (territorios == NULL) {
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    int totalTerritorios = 0;

    // --- Cadastro ---
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("===========================================\n");
        printf("         CADASTRO DE TERRITÓRIOS\n");
        printf("===========================================\n");

        printf("Território %d\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0';

        printf("Tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada();

        totalTerritorios++;
        printf("\n");
    }

    // --- LOOP DE JOGO ---
    int opcao;

    do {
        printf("\n========= MENU =========\n");
        printf("1 - Mostrar mapa\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("========================\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {

            case 1:
                mostrarMapa(territorios, totalTerritorios);
                break;

            case 2: {
                int atk, def;

                mostrarMapa(territorios, totalTerritorios);

                printf("Escolha território ATACANTE (1 a %d): ", totalTerritorios);
                scanf("%d", &atk);

                printf("Escolha território DEFENSOR (1 a %d): ", totalTerritorios);
                scanf("%d", &def);
                limparBufferEntrada();

                if (atk < 1 || atk > totalTerritorios ||
                    def < 1 || def > totalTerritorios ||
                    atk == def) {

                    printf("⚠️ Escolha inválida!\n");
                } else {
                    simularAtaque(&territorios[atk - 1],
                                  &territorios[def - 1]);
                }

                break;
            }

            case 0:
                printf("Saindo do jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    // 🔥 LIBERA MEMÓRIA
    free(territorios);

    return 0;
}