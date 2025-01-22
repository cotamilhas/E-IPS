#include <stdio.h>
#include <stdlib.h>
#include "embaixadores.h"
#include "visitas.h"
#include "extras.h"

void mostrarMenu();
void limparConsola();
void limparBufferEntrada();

int main()
{
    int opcao;

    carregarDadosCSV();

    do
    {
        mostrarMenu();
        printf("\nEscolha uma opção: \033[31m");

        if (scanf("%d", &opcao) != 1)
        {
            printf("\033[0m");
            printf("Entrada inválida. Por favor, insira um número.\n");
            limparBufferEntrada();
            continue;
        }

        printf("\033[0m");

        switch (opcao)
        {
        case 1:
            limparConsola();
            listarVisitas();
            break;
        case 2:
            limparConsola();
            listarEmbaixadores();
            break;
        case 3:
            limparConsola();
            consultarVisita();
            break;
        case 4:
            limparConsola();
            consultarEmbaixador();
            break;
        case 5:
            limparConsola();
            adicionarVisita();
            break;
        case 6:
            limparConsola();
            adicionarEmbaixador();
            break;
        case 7:
            limparConsola();
            autorizarVisita();
            break;
        case 8:
            limparConsola();
            cancelarVisita();
            break;
        case 9:
            limparConsola();
            confirmarRealizacaoVisita();
            break;
        case 10:
            limparConsola();
            alterarInformacaoVisita();
            break;
        case 11:
            limparConsola();
            alterarInformacaoEmbaixador();
            break;
        case 12:
            limparConsola();
            eliminarVisita();
            break;
        case 13:
            limparConsola();
            eliminarEmbaixador();
            break;
        case 14:
            limparConsola();
            gravarDadosCSV();
            printf("Dados gravados com sucesso!\n");
            break;
        case 15:
            limparConsola();
            printf("Adeus...\n");
            break;
        default:
            limparConsola();
            printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 15);

    gravarDadosCSV();

    return 0;
}

void mostrarMenu()
{
    printf("\nEscolha uma opção:\n");
    printf("1. Listar visitas\n");
    printf("2. Listar embaixadores\n");
    printf("3. Consultar visita\n");
    printf("4. Consultar embaixador\n");
    printf("5. Adicionar visita\n");
    printf("6. Adicionar embaixador\n");
    printf("7. Autorizar visita\n");
    printf("8. Cancelar visita\n");
    printf("9. Confirmar realização da visita\n");
    printf("10. Alterar informação da visita\n");
    printf("11. Alterar informação do embaixador\n");
    printf("12. Eliminar visita\n");
    printf("13. Eliminar embaixador\n");
    printf("14. Gravar Dados\n");
    printf("15. Sair\n");
}