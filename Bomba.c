#include <stdio.h>
#include <stdlib.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"

/*****
* void TryExplotar
******
* Recibe coordenadas. Reduce contador_turnos de la Bomba en la coordenada en 1, si termina en 0 el contador, debe llamar la función explotar de la Bomba.
******
* Input:
* int fila : número que va del 0 a dimension-1, indica fila de la bomba que se intenta explotar.
* int columna : número que va del 0 a dimension-1, indica columna de la bomba que se intenta explotar.
*****/
void TryExplotar(int fila, int columna){
    Bomba* bombHere = (Bomba*)tablero[fila][columna];
    bombHere->contador_turnos-=1;
    if(bombHere->contador_turnos==0){
        bombHere->explotar(fila,columna);
        BorrarBomba(fila,columna);
        return;
    } else tablero[fila][columna] = (void*)bombHere;
    return;
}

/*****
* void BorrarBomba
******
* Borra la Bomba en la coordenada de la memoria Heap, y devuelve la Tierra al tablero.
******
* Input:
* int fila : número que va del 0 a dimensión-1, indica fila de la bomba a borrar.
* int columna : número que va del 0 a dimensión-1, indica columna de la bomba a borrar.
*****/
void BorrarBomba(int fila, int columna){
    DirtOrBomb[fila][columna] = 't';
    Bomba* bombNow = (Bomba*)tablero[fila][columna];
    tablero[fila][columna] = (void*)bombNow->tierra_debajo;
    free(bombNow);
    return;
}

/*****
* void ExplosionPunto
******
* Hace explotar la bomba en la casilla en la que se encuentra, disminuyendo en 3 puntos la vida de la tierra debajo.
******
* Input:
* int fila : número que va del 0 a dimension-1, indica fila de la bomba a detonar.
* int columna : número que va del 0 a dimension-1, indica columna de la bomba a detonar.
*****/
void ExplosionPunto(int fila, int columna){
    Bomba* bombHere = (Bomba*)tablero[fila][columna];
    bombHere->tierra_debajo->vida -= 3;
    if(bombHere->tierra_debajo->vida<0) bombHere->tierra_debajo->vida=0;
    if(bombHere->tierra_debajo->es_tesoro==1) foundTreasures++;
    return;
}

/*  */
/*****
* void ExplosionX
******
* Explota la bomba como una equis, afectando las celdas diagonales a esta en un radio de 1 celda. Disminuye la vida de las celdas de Tierra afectadas en 1.
******
* Input:
* int fila : número que va del 0 a dimension-1, indica fila de la bomba a detonar.
* int columna : número que va del 0 a dimension-1, indica columna de la bomba a detonar.
*****/
void ExplosionX(int fila, int columna){
    int disrow=0, discolumn=0;
    if(((Bomba*)tablero[fila][columna])->tierra_debajo->vida!=0)
        ((Bomba*)tablero[fila][columna])->tierra_debajo->vida -= 1;
    for(int i = -1; i<=1;i+=2){
        for(int j = -1; j<=1;j+=2){
            disrow=fila+i;
            discolumn=columna+j;

            if(disrow < 0)
                disrow+=dimension;
            else if(dimension-1 < disrow)
                disrow-=dimension;
            
            if(discolumn < 0)
                discolumn+=dimension;
            else if(dimension-1 < discolumn)
                discolumn-=dimension;
            
            if(DirtOrBomb[disrow][discolumn]=='t'){
                Tierra* dirt = (Tierra*)tablero[disrow][discolumn];
                if(dirt->vida!=0){
                    dirt->vida -= 1;
                    tablero[disrow][discolumn] = (void*)dirt;
                    if(dirt->es_tesoro==1 && dirt->vida == 0) foundTreasures++;
                }
            } else if(DirtOrBomb[disrow][discolumn]=='b'){
                Bomba* bomb = (Bomba*)tablero[disrow][discolumn];
                if(bomb->tierra_debajo->vida!=0){
                    bomb->tierra_debajo->vida -= 1;
                    tablero[disrow][discolumn] = (void*)bomb;
                    if(bomb->tierra_debajo->es_tesoro==1 && bomb->tierra_debajo->vida == 0) foundTreasures++;
                }
            }
        }
    }
    return;
}