#include <stdio.h>
#include <string.h>
#include "embaixadores.h"

DadosEmbaixador listaEmbaixadores[MAX_EMBAIXADORES];
int contadorEmbaixadores = 0;

const char *nomesEscolas[] = {
    "ESTS",
    "ESTB",
    "ESE",
    "ESCE",
    "ESS"
};

void adicionarEmbaixador() {
    if (contadorEmbaixadores >= MAX_EMBAIXADORES) {
        printf("\nErro: Não é possível adicionar mais embaixadores. Capacidade máxima atingida.\n");
        return;
    }

    DadosEmbaixador *embaixador = &listaEmbaixadores[contadorEmbaixadores];

    printf("\nAdicionar novo embaixador:\n");

    printf("Número de Estudante: ");
    while (scanf("%d", &embaixador->numeroEstudante) != 1) {
        printf("Entrada inválida. Por favor, insira um número válido: ");
        while (getchar() != '\n');
    }

    printf("Escola (0: ESTS, 1: ESTB, 2: ESE, 3: ESCE, 4: ESS): ");
    while (scanf("%d", (int*)&embaixador->escola) != 1 || embaixador->escola < ESTS || embaixador->escola > ESS) {
        printf("Entrada inválida. Por favor, insira um valor entre 0 e 4: ");
        while (getchar() != '\n');
    }
    getchar();

    printf("Nome Completo: ");
    fgets(embaixador->nomeCompleto, sizeof(embaixador->nomeCompleto), stdin);
    embaixador->nomeCompleto[strcspn(embaixador->nomeCompleto, "\n")] = '\0';

    printf("NIF: ");
    scanf("%8s", embaixador->nif);

    contadorEmbaixadores++;
    printf("\nEmbaixador adicionado com sucesso!\n");
}

void listarEmbaixadores() {
    if (contadorEmbaixadores == 0) {
        printf("\nNão há embaixadores cadastrados.\n");
        return;
    }

    printf("\nLista de Embaixadores:\n");
    for (int i = 0; i < contadorEmbaixadores; i++) {
        printf("\nEmbaixador %d:\n", i + 1);
        printf("Número de Estudante: %d\n", listaEmbaixadores[i].numeroEstudante);
        printf("Escola: %s\n", nomesEscolas[listaEmbaixadores[i].escola]);
        printf("Nome Completo: %s\n", listaEmbaixadores[i].nomeCompleto);
        printf("NIF: %s\n", listaEmbaixadores[i].nif);
    }
}

void consultarEmbaixador() {
    if (contadorEmbaixadores == 0) {
        printf("\nNão há embaixadores cadastrados.\n");
        return;
    }

    int numeroBusca;
    printf("\nDigite o número de estudante do embaixador que deseja consultar: ");
    scanf("%d", &numeroBusca);

    for (int i = 0; i < contadorEmbaixadores; i++) {
        if (listaEmbaixadores[i].numeroEstudante == numeroBusca) {
            printf("\nEmbaixador encontrado:\n");
            printf("Número de Estudante: %d\n", listaEmbaixadores[i].numeroEstudante);
            printf("Escola: %s\n", nomesEscolas[listaEmbaixadores[i].escola]);
            printf("Nome Completo: %s\n", listaEmbaixadores[i].nomeCompleto);
            printf("NIF: %s\n", listaEmbaixadores[i].nif);
            return;
        }
    }

    printf("\nEmbaixador com número de estudante %d não encontrado.\n", numeroBusca);
}
