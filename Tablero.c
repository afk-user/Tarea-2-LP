#include <stdio.h>
#include <stdlib.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"

void*** tablero;
char** DirtOrBomb;
int dimension, allTreasures, foundTreasures;

/* Recibe el tamaño del tablero n, generando una matriz void n x n
inicializado con Tierra en cada una de sus celdas. Cada Tierra se le asigna al azar vida
entre los valores {1, 2, 3} (equiprobable) además del parámetro es_tesoro (5% de
probabilidad de ser un tesoro). */
void IniciarTablero(int n){
    tablero = (void***)malloc(n*sizeof(void**));
    DirtOrBomb = (char**)malloc(n*sizeof(char*));
    for(int i=0;i<n;i++){
        tablero[i] = (void**)malloc(n*sizeof(void*));
        DirtOrBomb[i] = (char*)malloc(n*sizeof(char));
        for(int j=0;j<n;j++){
            Tierra *dirtNow = (Tierra*)malloc(sizeof(Tierra));
            dirtNow->vida = (rand()%3+1);
            if((rand()%100)<5) dirtNow->es_tesoro = 1;
            else dirtNow->es_tesoro = 0;
            tablero[i][j] = (void*)dirtNow;
            DirtOrBomb[i][j] = 't';
        }
    }
    return;
}

/* Recibe el tablero del juego. Recorre la matriz de izquierda a derecha y de
arriba abajo intentando explotar cada una de las bombas en el tablero con TryExplotar. */
void PasarTurno(){
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(DirtOrBomb[i][j]=='b') TryExplotar(i,j);
        }
    }
    return;
}

/* Recibe una Bomba y coordenadas. Coloca una Bomba en el tablero, en la
celda especificada por el parámetro coordenadas. */
void ColocarBomba(Bomba* b, int fila, int columna){
    DirtOrBomb[fila][columna] = 'b';
    Bomba* bomb = malloc(sizeof(Bomba));
    *bomb = *b;
    bomb->tierra_debajo = (Tierra*)tablero[fila][columna];
    tablero[fila][columna] = (void*)bomb;
    return;
}

/* Muestra el tablero representando la Tierra con su vida, Bomba con o
(letra “o” minúscula) y un tesoro descubierto con *. (Tierra = {“3”, “2”, “1”, “0”},
Bomba = “o”, Mostrar tesoro de Tierra = “*”. Notar que si una Tierra llega a vida = 0 y
no es un tesoro, simplemente se enseñará como “0”) */
void MostrarTablero(){
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(DirtOrBomb[i][j] == 't'){
                Tierra *dirtNow = (Tierra*) tablero[i][j];
                if(dirtNow->vida == 0 && dirtNow->es_tesoro == 1) printf("*");
                else printf("%d",dirtNow->vida);
            } else if(DirtOrBomb[i][j] == 'b'){
                printf("o");
            }
            if(j<dimension-1) printf(" | ");
        }
        printf("\n");
    }
    return;
}

/* Muestra por pantalla cada una de las bombas en el tablero de la
siguiente forma:
****
Turnos para explotar: el valor
Coordenada: x y
Forma Explosión: nombre de la función explotar (ExplosionPunto o
ExplosionX)
Vida de Tierra Debajo: el valor.
****
- Es importante notar que las coordenadas x e y van desde 1 hasta el tamaño del tablero. */
void MostrarBombas(){
    Bomba* bombNow;
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(DirtOrBomb[i][j]=='b'){
                bombNow = (Bomba*)tablero[i][j];
                printf("Turnos para explotar: %d\nCoordenada: %d %d\nForma Explosión: ExplosionX\nVida de Tierra Debajo: %d\n\n",bombNow->contador_turnos,i+1,j+1,bombNow->tierra_debajo->vida);
            }
        }
    }
    return;
}

/* Muestra todos los tesoros en el tablero (ocultos y revelados). Esta función
está pensada para facilitar el testeo. Los espacios en donde hay tesoros se marcan con * en vez de un número. */
void VerTesoros(){
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(DirtOrBomb[i][j] == 't'){
                Tierra *dirtNow = (Tierra*) tablero[i][j];
                if(dirtNow->es_tesoro == 1) printf("*");
                else printf("%d",dirtNow->vida);
            } else if(DirtOrBomb[i][j] == 'b'){
                Bomba *bombNow = (Bomba*) tablero[i][j];
                if(bombNow->tierra_debajo->es_tesoro==1) printf("*");
                else printf("%d",bombNow->tierra_debajo->vida);
            }
            if(j<dimension-1) printf(" | ");
        }
        printf("\n");
    }
    printf("\n");
    return;
}

/* Borra el tablero de la memoria Heap. */
void BorrarTablero(){
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(DirtOrBomb[i][j]=='b') BorrarBomba(i,j);
            free(tablero[i][j]);
        }
        free(tablero[i]);
        free(DirtOrBomb[i]);
    }
    free(tablero);
    free(DirtOrBomb);
    return;
}

int TreasureCheck(){
    int flag = 0;
    for(int i = 0;i<dimension;i++){
        for(int j = 0;j<dimension;j++){
            if(DirtOrBomb[i][j] == 't'){
                Tierra* dirtNow = (Tierra*)tablero[i][j];
                if(dirtNow->es_tesoro==1){
                    flag = 1;
                    allTreasures++;
                }
            }
        }
    }
    return flag;
}