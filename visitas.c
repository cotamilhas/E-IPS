#include <stdio.h>
#include <string.h>
#include "visitas.h"
#include "embaixadores.h"

DadosVisitas listaVisitas[MAX_VISITAS];
int contadorVisitas = 0;

void adicionarVisita()
{
    if (contadorVisitas >= MAX_VISITAS)
    {
        printf("\nErro: Capacidade máxima de visitas atingida.\n");
        return;
    }

    DadosVisitas *novaVisita = &listaVisitas[contadorVisitas];
    novaVisita->idVisita = contadorVisitas + 1;
    novaVisita->estadoVisita = emPlaneamento;
    novaVisita->numEmbaixadores = 0;

    printf("\nAdicionar nova visita:\n");

    printf("Local: ");
    scanf(" %[^\n]", novaVisita->local);

    int dia, mes, ano;
    printf("Data da Visita (dd/mm/aaaa): ");
    while (scanf("%d/%d/%d", &dia, &mes, &ano) != 3)
    {
        printf("Entrada inválida. Insira novamente (dd/mm/aaaa): ");
        while (getchar() != '\n');
    }
    novaVisita->dataVisita = dataCriar(dia, mes, ano);

    printf("Quantos embaixadores para esta visita? (Max. %d): ", MAX_NUM_EMBAIXADORES);
    int numEmbaixadoresEscolhidos;
    while (scanf("%d", &numEmbaixadoresEscolhidos) != 1 || numEmbaixadoresEscolhidos < 0 || numEmbaixadoresEscolhidos > MAX_NUM_EMBAIXADORES)
    {
        printf("Entrada inválida. Insira um valor entre 0 e %d: ", MAX_NUM_EMBAIXADORES);
        while (getchar() != '\n');
    }

    for (int i = 0; i < numEmbaixadoresEscolhidos; i++)
    {
        char nif[9];
        int encontrado = 0;
        printf("NIF do Embaixador %d: ", i + 1);
        scanf("%8s", nif);

        for (int j = 0; j < contadorEmbaixadores; j++)
        {
            if (strcmp(listaEmbaixadores[j].nif, nif) == 0)
            {
                novaVisita->listaEmbaixadores[novaVisita->numEmbaixadores++] = listaEmbaixadores[j];
                encontrado = 1;
                break;
            }
        }

        if (!encontrado)
        {
            printf("Erro: Embaixador com NIF %s não encontrado. Tente novamente.\n", nif);
            i--;
        }
    }

    contadorVisitas++;
    printf("\nVisita adicionada com sucesso! ID: %d\n", novaVisita->idVisita);
}

void listarVisitas()
{
    if (contadorVisitas == 0)
    {
        printf("\nNão há visitas cadastradas.\n");
        return;
    }

    printf("\nLista de Visitas (por ordem decrescente de ID):\n");
    for (int i = contadorVisitas - 1; i >= 0; i--)
    {
        printf("\nID da Visita: %d\n", listaVisitas[i].idVisita);
        printf("Local: %s\n", listaVisitas[i].local);
        printf("Data: %02d/%02d/%04d\n", listaVisitas[i].dataVisita.dia, listaVisitas[i].dataVisita.mes, listaVisitas[i].dataVisita.ano);
        printf("Estado: ");
        switch (listaVisitas[i].estadoVisita)
        {
        case emPlaneamento:
            printf("Em Planeamento");
            break;
        case autorizado:
            printf("Autorizado");
            break;
        case cancelado:
            printf("Cancelado");
            break;
        case realizado:
            printf("Realizado");
            break;
        default:
            printf("ERRO");
            break;
        }
        printf("\nEmbaixadores associados (%d):\n", listaVisitas[i].numEmbaixadores);
        for (int j = 0; j < listaVisitas[i].numEmbaixadores; j++)
        {
            printf("  - %s (NIF: %s)\n", listaVisitas[i].listaEmbaixadores[j].nomeCompleto, listaVisitas[i].listaEmbaixadores[j].nif);
        }
    }
}

void consultarVisita()
{
    if (contadorVisitas == 0)
    {
        printf("\nNão há visitas cadastradas.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da visita que deseja consultar: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < contadorVisitas; i++)
    {
        if (listaVisitas[i].idVisita == idBusca)
        {
            printf("\nDetalhes da Visita:\n");
            printf("ID da Visita: %d\n", listaVisitas[i].idVisita);
            printf("Local: %s\n", listaVisitas[i].local);
            printf("Data: %02d/%02d/%04d\n", listaVisitas[i].dataVisita.dia, listaVisitas[i].dataVisita.mes, listaVisitas[i].dataVisita.ano);
            printf("Estado: ");
            switch (listaVisitas[i].estadoVisita)
            {
            case emPlaneamento:
                printf("Em Planeamento");
                break;
            case autorizado:
                printf("Autorizado");
                break;
            case cancelado:
                printf("Cancelado");
                break;
            case realizado:
                printf("Realizado");
                break;
            default:
                printf("ERRO");
                break;
            }
            printf("\nEmbaixadores associados (%d):\n", listaVisitas[i].numEmbaixadores);
            for (int j = 0; j < listaVisitas[i].numEmbaixadores; j++)
            {
                printf("  - %s (NIF: %s)\n", listaVisitas[i].listaEmbaixadores[j].nomeCompleto, listaVisitas[i].listaEmbaixadores[j].nif);
            }
            return;
        }
    }

    printf("\nVisita com ID %d não encontrada.\n", idBusca);
}

void autorizarVisita()
{
    if (contadorVisitas == 0)
    {
        printf("\nNão há visitas cadastradas.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da visita que deseja autorizar: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < contadorVisitas; i++)
    {
        if (listaVisitas[i].idVisita == idBusca)
        {
            listaVisitas[i].estadoVisita = autorizado;
            printf("\nVisita ID %d foi autorizada com sucesso.\n", idBusca);
            return;
        }
    }

    printf("\nVisita com ID %d não encontrada.\n", idBusca);
}
