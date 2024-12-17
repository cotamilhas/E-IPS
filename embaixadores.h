#pragma once

#define MAX_EMBAIXADORES 100

typedef enum {
    ESTS,  // Escola Superior de Tecnologia de Setúbal
    ESTB,  // Escola Superior de Tecnologia do Barreiro
    ESE,   // Escola Superior de Educação
    ESCE,  // Escola Superior de Ciências Empresariais
    ESS    // Escola Superior de Saúde
} Escola;

typedef struct {
    int numeroEstudante;
    Escola escola;
    char nomeCompleto[100];
    char nif[9];
} DadosEmbaixador;

extern int contadorEmbaixadores;
extern DadosEmbaixador listaEmbaixadores[MAX_EMBAIXADORES];

void listarEmbaixadores();
void adicionarEmbaixador();
void consultarEmbaixador();
