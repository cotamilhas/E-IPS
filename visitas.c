#include <stdio.h>
#include <string.h>
#include <time.h>
#include "visitas.h"
#include "embaixadores.h"
#include "extras.h"

DadosVisitas listaVisitas[MAX_VISITAS];
int contadorVisitas = 0;

void adicionarVisita()
{
    if (contadorVisitas >= MAX_VISITAS)
    {
        printf("Erro: Capacidade máxima de visitas atingida.\n");
        return;
    }

    DadosVisitas *novaVisita = &listaVisitas[contadorVisitas];
    novaVisita->idVisita = contadorVisitas + 1;
    novaVisita->estadoVisita = emPlaneamento;
    novaVisita->numEmbaixadores = 0;

    printf("Adicionar nova visita\n");

    printf("Local: ");
    scanf(" %[^\n]", novaVisita->local);

    int dia, mes, ano;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("Data da Visita (dd/mm/aaaa): ");
    while (scanf("%d/%d/%d", &dia, &mes, &ano) != 3 || 
           (ano < tm.tm_year + 1900) || 
           (ano == tm.tm_year + 1900 && mes < tm.tm_mon + 1) || 
           (ano == tm.tm_year + 1900 && mes == tm.tm_mon + 1 && dia < tm.tm_mday))
    {
        printf("Entrada inválida. Insira uma data futura ou igual a hoje (dd/mm/aaaa): ");
        while (getchar() != '\n')
            ;
    }
    novaVisita->dataVisita = dataCriar(dia, mes, ano);

    printf("Quantos embaixadores para esta visita? (Max. %d): ", MAX_NUM_EMBAIXADORES);
    int numEmbaixadoresEscolhidos;
    while (scanf("%d", &numEmbaixadoresEscolhidos) != 1 || numEmbaixadoresEscolhidos < 0 || numEmbaixadoresEscolhidos > MAX_NUM_EMBAIXADORES)
    {
        printf("Entrada inválida. Insira um valor entre 0 e %d: ", MAX_NUM_EMBAIXADORES);
        while (getchar() != '\n')
            ;
    }

    if (contadorEmbaixadores == 0)
    {
        if (numEmbaixadoresEscolhidos > 0)
        {
            printf("Erro: Não há embaixadores registrados.\n");
            return;
        }
    }
    else if (numEmbaixadoresEscolhidos > contadorEmbaixadores)
    {
        printf("Erro: Você solicitou mais embaixadores do que estão registrados (%d disponíveis).\n", contadorEmbaixadores);
        return;
    }
    else
    {
        for (int i = 0; i < numEmbaixadoresEscolhidos; i++)
        {
            char nif[9];
            int encontrado = 0;
            printf("NIF do Embaixador %d: ", i + 1);
            scanf("%9s", nif);

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
    }

    contadorVisitas++;
    printf("\nVisita adicionada com sucesso! ID: %d\n", novaVisita->idVisita);
}

void listarVisitas()
{
    if (contadorVisitas == 0)
    {
        printf("Nenhuma visita encontrada.\n");
        return;
    }

    printf("\nLista de Visitas (por ordem decrescente de ID):\n");
    for (int i = contadorVisitas - 1; i >= 0; i--)
    {
        printf("ID: %d\n", listaVisitas[i].idVisita);
        printf("Local: %s\n", listaVisitas[i].local);
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
        printf("\nData: %02d/%02d/%04d\n", listaVisitas[i].dataVisita.dia, listaVisitas[i].dataVisita.mes, listaVisitas[i].dataVisita.ano);
        printf("Número de Embaixadores: %d\n", listaVisitas[i].numEmbaixadores);
        printf("NIFs dos Embaixadores: ");
        for (int j = 0; j < listaVisitas[i].numEmbaixadores; j++)
        {
            printf("%s", listaVisitas[i].listaEmbaixadores[j].nif);
            if (j < listaVisitas[i].numEmbaixadores - 1)
            {
                printf(";");
            }
        }
        printf("\n\n");
    }
}

void consultarVisita()
{
    if (contadorVisitas == 0)
    {
        printf("Não há visitas cadastradas.\n");
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
            printf("ID: %d\n", listaVisitas[i].idVisita);
            printf("Local: %s\n", listaVisitas[i].local);
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
            printf("\nData: %02d/%02d/%04d\n", listaVisitas[i].dataVisita.dia, listaVisitas[i].dataVisita.mes, listaVisitas[i].dataVisita.ano);
            printf("Número de Embaixadores: %d\n", listaVisitas[i].numEmbaixadores);
            printf("NIFs dos Embaixadores: ");
            for (int j = 0; j < listaVisitas[i].numEmbaixadores; j++)
            {
                printf("%s", listaVisitas[i].listaEmbaixadores[j].nif);
                if (j < listaVisitas[i].numEmbaixadores - 1)
                {
                    printf(";");
                }
            }
            printf("\n\n");
            return;
        }
    }

    printf("Visita com ID %d não encontrada.\n", idBusca);
}

void autorizarVisita()
{
    if (contadorVisitas == 0)
    {   
        printf("Não há visitas cadastradas.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da visita que deseja autorizar: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < contadorVisitas; i++)
    {
        if (listaVisitas[i].idVisita == idBusca)
        {  
            if (listaVisitas[i].numEmbaixadores < 2)
            {
                printf("Erro: A visita necessita de pelo menos 2 embaixadores para ser autorizada.\n");
                return;
            }
            
            listaVisitas[i].estadoVisita = autorizado;
            printf("\nVisita ID %d foi autorizada com sucesso.\n", idBusca);
            return;
        }
    }

    printf("Visita com ID %d não encontrada.\n", idBusca);
}

void cancelarVisita() {
    if (contadorVisitas == 0) {
        printf("Não há visitas cadastradas.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da visita que deseja cancelar: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < contadorVisitas; i++) {
        if (listaVisitas[i].idVisita == idBusca) {
            if (listaVisitas[i].estadoVisita == realizado) {
                printf("Erro: Não é possível cancelar uma visita já realizada.\n");
            } else {
                listaVisitas[i].estadoVisita = cancelado;
                printf("\nVisita ID %d foi cancelada com sucesso.\n", idBusca);
            }
            return;
        }
    }

    printf("Visita com ID %d não encontrada.\n", idBusca);
}

void confirmarRealizacaoVisita() {
    if (contadorVisitas == 0) {
        printf("Não há visitas cadastradas.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da visita que deseja confirmar como realizada: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < contadorVisitas; i++) {
        if (listaVisitas[i].idVisita == idBusca) {
            if (listaVisitas[i].estadoVisita == autorizado) {
                listaVisitas[i].estadoVisita = realizado;
                printf("\nVisita ID %d foi marcada como realizada.\n", idBusca);
            } else if (listaVisitas[i].estadoVisita == realizado) {
                printf("Erro: A visita já está marcada como realizada.\n");
            } else {
                printf("Erro: Apenas visitas autorizadas podem ser marcadas como realizadas.\n");
            }
            return;
        }
    }

    printf("Visita com ID %d não encontrada.\n", idBusca);
}

void alterarInformacaoVisita() {
    if (contadorVisitas == 0) {
        printf("Não há visitas cadastradas.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da visita que deseja alterar: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < contadorVisitas; i++) {
        if (listaVisitas[i].idVisita == idBusca) {
            printf("\nAltere os dados da visita (deixe em branco para não alterar):\n");

            printf("Local atual: %s\nNovo local: ", listaVisitas[i].local);
            char novoLocal[100];
            scanf(" %[^\n]", novoLocal);
            if (strlen(novoLocal) > 0) {
                strcpy(listaVisitas[i].local, novoLocal);
            }

            printf("Data atual: %02d/%02d/%04d\nNova data (dd/mm/aaaa): ",
                   listaVisitas[i].dataVisita.dia, listaVisitas[i].dataVisita.mes, listaVisitas[i].dataVisita.ano);
            int dia, mes, ano;
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);

            if (scanf("%d/%d/%d", &dia, &mes, &ano) == 3) {
                while ((ano < tm.tm_year + 1900) || 
                       (ano == tm.tm_year + 1900 && mes < tm.tm_mon + 1) || 
                       (ano == tm.tm_year + 1900 && mes == tm.tm_mon + 1 && dia < tm.tm_mday)) {
                    printf("Entrada inválida. Insira uma data futura ou igual a hoje (dd/mm/aaaa): ");
                    while (getchar() != '\n')
                        ;
                    scanf("%d/%d/%d", &dia, &mes, &ano);
                }
                listaVisitas[i].dataVisita = dataCriar(dia, mes, ano);
            }

            printf("\nInformações da visita atualizadas com sucesso.\n");
            return;
        }
    }

    printf("Visita com ID %d não encontrada.\n", idBusca);
}

void eliminarVisita() {
    if (contadorVisitas == 0) {
        printf("Não há visitas cadastradas.\n");
        return;
    }

    int idBusca;
    printf("\nDigite o ID da visita que deseja eliminar: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < contadorVisitas; i++) {
        if (listaVisitas[i].idVisita == idBusca) {
            if (listaVisitas[i].estadoVisita == realizado) {
                printf("Erro: Não é possível eliminar uma visita já realizada.\n");
            } else {
                for (int j = i; j < contadorVisitas - 1; j++) {
                    listaVisitas[j] = listaVisitas[j + 1];
                }
                contadorVisitas--;
                printf("\nVisita ID %d foi eliminada com sucesso.\n", idBusca);
            }
            return;
        }
    }

    printf("Visita com ID %d não encontrada.\n", idBusca);
}

