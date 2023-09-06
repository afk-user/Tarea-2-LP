#ifndef TABLERO_H
#define TABLERO_H

extern void*** tablero;
extern int dimension, allTreasures, foundTreasures; // 7 en 7x7, 10 en 10x10, 12 en 12x12
extern char** DirtOrBomb;

void IniciarTablero(int n);
void PasarTurno();
void ColocarBomba(Bomba* b, int fila, int columna);
void MostrarTablero();
void MostrarBombas();
void VerTesoros();
void BorrarTablero();
int TreasureCheck();
#endif