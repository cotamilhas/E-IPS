#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "visitas.h"
#include "embaixadores.h"
#include "extras.h"

void mudarCores(int cor)
{
    switch (cor) {
        case 0: printf("\033[0m"); break; // branco
        case 1: printf("\033[31m"); break; // vermelho
        case 2: printf("\033[32m"); break; // verde
        case 3: printf("\033[33m"); break; // amarelo
        case 4: printf("\033[34m"); break; // azul
    }
}

void limparConsola()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void limparBufferEntrada()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Lê e descarta caracteres até nova linha ou EOF
}

void gravarDadosCSV() {
    FILE *ficheiroVisitas = fopen("visitas.csv", "w");
    FILE *ficheiroEmbaixadores = fopen("embaixadores.csv", "w");

    if (ficheiroVisitas == NULL || ficheiroEmbaixadores == NULL) {
        printf("Erro ao abrir os ficheiros para gravação.\n");
        return;
    }

    // gravar cabeçalhos e dados das visitas
    fprintf(ficheiroVisitas, "ID,Local,Estado,Data,NumEmbaixadores,NIFEmbaixadores\n");
    for (int i = 0; i < contadorVisitas; i++) {
        fprintf(ficheiroVisitas, "%d,%s,%d,%02d/%02d/%04d,%d,",
                listaVisitas[i].idVisita,
                listaVisitas[i].local,
                listaVisitas[i].estadoVisita,
                listaVisitas[i].dataVisita.dia,
                listaVisitas[i].dataVisita.mes,
                listaVisitas[i].dataVisita.ano,
                listaVisitas[i].numEmbaixadores);

        // gravar os NIFs dos embaixadores associados à visita
        for (int j = 0; j < listaVisitas[i].numEmbaixadores; j++) {
            fprintf(ficheiroVisitas, "%s", listaVisitas[i].listaEmbaixadores[j].nif);
            if (j < listaVisitas[i].numEmbaixadores - 1) {
                fprintf(ficheiroVisitas, ";");
            }
        }
        fprintf(ficheiroVisitas, "\n");
    }
    fclose(ficheiroVisitas);

    // gravar embaixadores
    fprintf(ficheiroEmbaixadores, "Numero,Nome,Escola,NIF\n");
    for (int i = 0; i < contadorEmbaixadores; i++) {
        fprintf(ficheiroEmbaixadores, "%d,%s,%s,%s\n",
                listaEmbaixadores[i].numeroEstudante,
                listaEmbaixadores[i].nomeCompleto,
                nomesEscolas[listaEmbaixadores[i].escola],
                listaEmbaixadores[i].nif);
    }
    fclose(ficheiroEmbaixadores);

    printf("Dados gravados com sucesso nos ficheiros CSV.\n");
}

void carregarDadosCSV() {
    FILE *ficheiroVisitas = fopen("visitas.csv", "r");
    FILE *ficheiroEmbaixadores = fopen("embaixadores.csv", "r");

    if (ficheiroVisitas == NULL || ficheiroEmbaixadores == NULL) {
        printf("Erro ao abrir os ficheiros para leitura. Verifique se os ficheiros existem.\n");
        return;
    }

    // limpar as listas existentes
    contadorVisitas = 0;
    contadorEmbaixadores = 0;

    // carregar visitas
    char linha[1024];
    fgets(linha, sizeof(linha), ficheiroVisitas); // ignorar cabeçalho
    while (fgets(linha, sizeof(linha), ficheiroVisitas)) {
        DadosVisitas visitaTemp;
        char nifs[256];
        sscanf(linha, "%d,%[^,],%d,%d/%d/%d,%d,%[^\n]",
               &visitaTemp.idVisita,
               visitaTemp.local,
               (int*)&visitaTemp.estadoVisita,
               &visitaTemp.dataVisita.dia,
               &visitaTemp.dataVisita.mes,
               &visitaTemp.dataVisita.ano,
               &visitaTemp.numEmbaixadores,
               nifs);

        // processar NIFs dos embaixadores
        char *nif = strtok(nifs, ";");
        int j = 0;
        while (nif != NULL && j < 9) {
            strcpy(visitaTemp.listaEmbaixadores[j++].nif, nif);
            nif = strtok(NULL, ";");
        }

        listaVisitas[contadorVisitas++] = visitaTemp;
    }
    fclose(ficheiroVisitas);

    // carregar embaixadores
    fgets(linha, sizeof(linha), ficheiroEmbaixadores); // ignorar cabeçalho
    while (fgets(linha, sizeof(linha), ficheiroEmbaixadores)) {
        DadosEmbaixador embaixadorTemp;
        char escolaTemp[10];
        sscanf(linha, "%d,%[^,],%[^,],%s",
               &embaixadorTemp.numeroEstudante,
               embaixadorTemp.nomeCompleto,
               escolaTemp,
               embaixadorTemp.nif);

        // Converter escola para enum
        for (int i = 0; i < 5; i++) {
            if (strcmp(nomesEscolas[i], escolaTemp) == 0) {
                embaixadorTemp.escola = i;
                break;
            }
        }
        listaEmbaixadores[contadorEmbaixadores++] = embaixadorTemp;
    }
    fclose(ficheiroEmbaixadores);

    printf("Dados carregados com sucesso dos ficheiros CSV.\n");
}
