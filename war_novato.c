//===========================================================================
// DESAFIO NÍVEL NOVATO: CADASTRO DE TERRITÓRIOS DO JOGO WAR
//Solicitacao do cadastro dos territórios 
//Armazenando informações como nome, cor do exército e quantidade de tropas. 
//===========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcspn()

// --- Constantes Globais ---
#define MAX_TERRITORIOS 5

// --- Definição da Estrutura (struct) ---
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

//---Função para limpar o buffer de entrada---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer (prevenção de problemas com fgets)
}

// --- Cadastro dos Territórios ---
int main() {
    struct Territorio territorios[MAX_TERRITORIOS]; // Array para armazenar os territórios
    int totalTerritorios = 0; // Contador de territórios cadastrados

    // --- Cadastrando os Territórios ---
    for (int i = 0; i < MAX_TERRITORIOS; i++) {
        printf("===========================================\n");
        printf("         CADASTRO DE TERRITÓRIOS - WAR\n");
        printf("===========================================\n\n");

        printf("Cadastrando Território %d:\n", i + 1);
        
        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // Remove o \n do final da string
        
        printf("Digite a cor do exército (ex. Azul, verde): ");
        fgets(territorios[i].cor, sizeof(territorios[i].cor), stdin);
        territorios[i].cor[strcspn(territorios[i].cor, "\n")] = '\0'; // Remove o \n do final da string
        
        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].tropas);
        limparBufferEntrada(); // Limpa o buffer de entrada
        
        totalTerritorios++; // Incrementa o contador de territórios
        printf("\n");

       }

    // --- Listagem dos Territórios Cadastrados ---
    //Informacoes que serao impressas

    printf("===========================================\n");
    printf("    MAPA DO MUNDO - ESTADO ATUAL\n");
    printf("===========================================\n");
    for (int i = 0; i < totalTerritorios; i++) {
        printf("TERRITORIO %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Dominado por: Exército %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------\n");
    }

    return 0;
}
