#ifndef BOMBA_H
#define BOMBA_H
#include "Tierra.h"

typedef struct Bomba{
    int contador_turnos;
    void (*explotar)(int fila, int columna);
    Tierra* tierra_debajo;
} Bomba;

void TryExplotar(int fila, int columna);
void BorrarBomba(int fila, int columna);
void ExplosionPunto(int fila, int columna);
void ExplosionX(int fila, int columna);

#endif