#pragma once
#include "embaixadores.h"
#include "data.h"

#define MAX_VISITAS 100
#define MAX_NUM_EMBAIXADORES 9

typedef enum
{
    emPlaneamento,
    autorizado,
    cancelado,
    realizado
} EstadoDaVisita;

typedef struct
{
    int idVisita;
    DadosEmbaixador listaEmbaixadores[MAX_NUM_EMBAIXADORES];
    int numEmbaixadores;
    EstadoDaVisita estadoVisita;
    char local[100];
    DataVisita dataVisita;
} DadosVisitas;

void adicionarVisita();
void listarVisitas();
void consultarVisita();
void autorizarVisita();
