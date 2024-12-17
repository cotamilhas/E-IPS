#include <stdio.h>
#include <stdlib.h>
#include "embaixadores.h"
#include "visitas.h"

void mostrarMenu();
void limparConsola();
void test();

int main()
{
    int opcao;

    do
    {
        mostrarMenu();
        printf("\nEscolha uma opção: \033[31m");
        scanf("%d", &opcao);
        printf("\033[0m");

        limparConsola();

        switch (opcao)
        {
        case 1:
            listarVisitas();
            break;
        case 2:
            listarEmbaixadores();
            break;
        case 3:
            consultarVisita();
            break;
        case 4:
            consultarEmbaixador();
            break;
        case 5:
            adicionarVisita();
            break;
        case 6:
            adicionarEmbaixador();
            break;
        case 7:
            autorizarVisita();
            break;
        case 15:
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 15);

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
    printf("15. Sair\n");
}

void test(){

}

void limparConsola()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
