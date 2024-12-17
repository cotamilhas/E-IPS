#include <stdio.h>
#include "data.h"

DataVisita dataCriar(int dia, int mes, int ano)
{
    DataVisita data;
    data.dia = dia;
    data.mes = mes;
    data.ano = ano;
    return data;
}