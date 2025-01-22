#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "embaixadores.h"
#include "visitas.h"
#include "extras.h"

DadosEmbaixador listaEmbaixadores[MAX_EMBAIXADORES];
int contadorEmbaixadores = 0;

const char *nomesEscolas[] = {
    "ESTS",
    "ESTB",
    "ESE",
    "ESCE",
    "ESS"};

void adicionarEmbaixador()
{
    if (contadorEmbaixadores >= MAX_EMBAIXADORES)
    {
        printf("Erro: Não é possível adicionar mais embaixadores. Capacidade máxima atingida.\n");
        return;
    }

    DadosEmbaixador embaixadorTemp;

    // Pedir o número de estudante e verificar se já existe
    printf("Número de Estudante: ");
    while (scanf("%d", &embaixadorTemp.numeroEstudante) != 1)
    {

        printf("Entrada inválida. Por favor, insira um número válido: ");
        while (getchar() != '\n')
            ;
    }

    for (int i = 0; i < contadorEmbaixadores; i++)
    {
        if (listaEmbaixadores[i].numeroEstudante == embaixadorTemp.numeroEstudante)
        {
            printf("Erro: Já existe um embaixador com o número de estudante %d.\n", embaixadorTemp.numeroEstudante);
            return;
        }
    }

    // Pedir o NIF e verificar se já existe e se tem exatamente 9 dígitos
    printf("\nNIF (9 dígitos): ");
    while (1)
    {
        scanf("%9s", embaixadorTemp.nif);

        // Verificar se o NIF tem exatamente 9 dígitos
        if (strlen(embaixadorTemp.nif) != 9 || strspn(embaixadorTemp.nif, "0123456789") != 9)
        {
            printf("Erro: O NIF deve ter exatamente 9 dígitos numéricos. Por favor, tente novamente: ");
        }
        else
        {
            break;
        }
    }

    for (int i = 0; i < contadorEmbaixadores; i++)
    {
        if (strcmp(listaEmbaixadores[i].nif, embaixadorTemp.nif) == 0)
        {
            printf("Erro: Já existe um embaixador com o NIF %s.\n", embaixadorTemp.nif);
            return;
        }
    }

    // Pedir a escola
    printf("\nEscola (0: ESTS, 1: ESTB, 2: ESE, 3: ESCE, 4: ESS): ");
    while (scanf("%d", (int *)&embaixadorTemp.escola) != 1 || embaixadorTemp.escola < ESTS || embaixadorTemp.escola > ESS)
    {

        printf("Entrada inválida. Por favor, insira um valor entre 0 e 4.");
        printf("\nEscola (0: ESTS, 1: ESTB, 2: ESE, 3: ESCE, 4: ESS): ");
        while (getchar() != '\n')
            ;
    }
    getchar();

    // Pedir o nome completo
    printf("\nNome Completo: ");
    fgets(embaixadorTemp.nomeCompleto, sizeof(embaixadorTemp.nomeCompleto), stdin);
    embaixadorTemp.nomeCompleto[strcspn(embaixadorTemp.nomeCompleto, "\n")] = '\0';

    // Adicionar o embaixador à lista
    listaEmbaixadores[contadorEmbaixadores] = embaixadorTemp;
    contadorEmbaixadores++;

    mudarCores(2);
    printf("\nEmbaixador adicionado com sucesso!\n");
    mudarCores(0);
}

void listarEmbaixadores()
{
    if (contadorEmbaixadores == 0)
    {
        printf("Não há embaixadores cadastrados.\n");
        return;
    }

    printf("Lista de Embaixadores:\n");
    for (int i = 0; i < contadorEmbaixadores; i++)
    {
        printf("\nEmbaixador %d:\n", i + 1);
        printf("Número de Estudante: %d\n", listaEmbaixadores[i].numeroEstudante);
        printf("Escola: %s\n", nomesEscolas[listaEmbaixadores[i].escola]);
        printf("Nome Completo: %s\n", listaEmbaixadores[i].nomeCompleto);
        printf("NIF: %s\n", listaEmbaixadores[i].nif);
    }

    return;
}

void consultarEmbaixador()
{
    if (contadorEmbaixadores == 0)
    {
        printf("Não há embaixadores cadastrados.\n");
        return;
    }

    int numeroBusca;
    printf("Digite o número de estudante do embaixador que deseja consultar: ");
    scanf("%d", &numeroBusca);

    for (int i = 0; i < contadorEmbaixadores; i++)
    {
        if (listaEmbaixadores[i].numeroEstudante == numeroBusca)
        {
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

void alterarInformacaoEmbaixador()
{
    if (contadorEmbaixadores == 0)
    {
        printf("Não há embaixadores cadastrados.\n");
        return;
    }

    int numeroBusca;
    printf("Digite o número de estudante do embaixador que deseja alterar: ");
    scanf("%d", &numeroBusca);

    for (int i = 0; i < contadorEmbaixadores; i++)
    {
        if (listaEmbaixadores[i].numeroEstudante == numeroBusca)
        {
            // Verificar se o embaixador está associado a visitas
            for (int j = 0; j < contadorVisitas; j++)
            {
                for (int k = 0; k < listaVisitas[j].numEmbaixadores; k++)
                {
                    if (strcmp(listaVisitas[j].listaEmbaixadores[k].nif, listaEmbaixadores[i].nif) == 0)
                    {
                        printf("Erro: Não é possível alterar este embaixador. Ele está associado a uma visita.\n");
                        return;
                    }
                }
            }

            printf("\nAlterar informações do embaixador (deixe em branco para não alterar):\n");

            // Alterar o NIF
            printf("NIF atual: %s\nNovo NIF (9 dígitos): ", listaEmbaixadores[i].nif);
            char novoNif[10];
            scanf("%s", novoNif);

            if (strlen(novoNif) == 9 && strspn(novoNif, "0123456789") == 9)
            {
                strcpy(listaEmbaixadores[i].nif, novoNif);
            }
            else
            {
                printf("NIF inválido. Mantendo o anterior.\n");
            }

            // Alterar a escola
            printf("Escola atual: %s\nNova Escola (0: ESTS, 1: ESTB, 2: ESE, 3: ESCE, 4: ESS): ",
                   nomesEscolas[listaEmbaixadores[i].escola]);
            int novaEscola;
            if (scanf("%d", &novaEscola) == 1 && novaEscola >= ESTS && novaEscola <= ESS)
            {
                listaEmbaixadores[i].escola = novaEscola;
            }
            else
            {
                printf("Escola inválida. Mantendo a anterior.\n");
            }

            // Alterar o nome completo
            printf("Nome atual: %s\nNovo Nome: ", listaEmbaixadores[i].nomeCompleto);
            getchar(); // Limpar o buffer
            fgets(listaEmbaixadores[i].nomeCompleto, sizeof(listaEmbaixadores[i].nomeCompleto), stdin);
            listaEmbaixadores[i].nomeCompleto[strcspn(listaEmbaixadores[i].nomeCompleto, "\n")] = '\0';

            printf("\nInformações do embaixador atualizadas com sucesso!\n");
            return;
        }
    }

    printf("\nEmbaixador com número de estudante %d não encontrado.\n", numeroBusca);
}

void eliminarEmbaixador()
{
    if (contadorEmbaixadores == 0)
    {
        printf("Não há embaixadores cadastrados.\n");
        return;
    }

    int numeroBusca;
    printf("Digite o número de estudante do embaixador que deseja eliminar: ");
    scanf("%d", &numeroBusca);

    for (int i = 0; i < contadorEmbaixadores; i++)
    {
        if (listaEmbaixadores[i].numeroEstudante == numeroBusca)
        {
            // Verificar se o embaixador está associado a visitas autorizadas
            for (int j = 0; j < contadorVisitas; j++)
            {
                char *nifEmbaixador = listaEmbaixadores[i].nif;
                for (int k = 0; k < listaVisitas[j].numEmbaixadores; k++)
                {
                    char *nifEmbaixadoresVisita = strdup(listaVisitas[j].listaEmbaixadores[k].nif);
                    char *token = strtok(nifEmbaixadoresVisita, ";");

                    while (token != NULL)
                    {
                        if (strcmp(token, nifEmbaixador) == 0 && listaVisitas[j].estadoVisita == autorizado)
                        {
                            printf("Erro: Não é possível eliminar este embaixador. Ele está associado a uma visita autorizada.\n");
                            free(nifEmbaixadoresVisita);
                            return;
                        }
                        token = strtok(NULL, ";");
                    }
                    free(nifEmbaixadoresVisita);
                }
            }

            // Remover o embaixador
            for (int j = i; j < contadorEmbaixadores - 1; j++)
            {
                listaEmbaixadores[j] = listaEmbaixadores[j + 1];
            }
            contadorEmbaixadores--;
            printf("\nEmbaixador com número de estudante %d eliminado com sucesso.\n", numeroBusca);
            return;
        }
    }

    printf("\nEmbaixador com número de estudante %d não encontrado.\n", numeroBusca);
}
