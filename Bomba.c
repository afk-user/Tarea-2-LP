#include <stdio.h>
#include <stdlib.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"

/* Recibe coordenadas. Reduce contador_turnos de la Bomba en la
coordenada en 1, si termina en 0 el contador, debe llamar la función explotar de la
Bomba. */
void TryExplotar(int fila, int columna){
    Bomba* bombHere = (Bomba*)tablero[fila][columna]; 
    bombHere->contador_turnos-=1;
    if(bombHere->contador_turnos==0){
        if(bombHere->explotar==ExplosionPunto){
            ExplosionPunto(fila,columna);
        }else{
            ExplosionX(fila,columna);
        }
        BorrarBomba(fila,columna);
        return;
    } else tablero[fila][columna] = (void*)bombHere;
}

/* Recibe coordenadas. Borra la Bomba en la coordenada de la memoria
Heap, pero antes de eso devuelve la Tierra al tablero. */
void BorrarBomba(int fila, int columna){
    DirtOrBomb[fila][columna] = 't';
    Bomba* bombNow = (Bomba*)tablero[fila][columna];
    tablero[fila][columna] = (void*)bombNow->tierra_debajo;
    free(bombNow);
    return;
}

/* Explota la bomba como un punto, es decir, solo afecta a la tierra debajo
de la Bomba. Disminuye la vida de esa Tierra en 3. Al momento de crear una bomba con
este tipo de explosión, su variable contador_turnos debe asignarse a 1. */
void ExplosionPunto(int fila, int columna){
    Bomba* bombHere = (Bomba*)tablero[fila][columna];
    bombHere->tierra_debajo->vida = 0;
    if(bombHere->tierra_debajo->es_tesoro==1) foundTreasures++;
    return;
}

/* Explota la bomba como una equis, afecta 5 celdas solamente (no se extiende
por el tablero). Disminuye la vida de las celdas de Tierra afectadas en 1. Al momento de
crear una bomba con este tipo de explosión, su variable contador_turnos debe asignarse a
3. */
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