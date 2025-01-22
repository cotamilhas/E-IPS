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
    char nifEmbaixadores[10];
} DadosVisitas;

extern DadosVisitas listaVisitas[MAX_VISITAS];
extern int contadorVisitas;

void adicionarVisita();
void listarVisitas();
void consultarVisita();
void autorizarVisita();
void cancelarVisita();
void confirmarRealizacaoVisita();
void alterarInformacaoVisita();
void eliminarVisita();
