#include <stdio.h>
#include <stdlib.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"

void*** tablero;
char** DirtOrBomb;
int dimension, allTreasures, foundTreasures;

/*****
* void IniciarTablero
******
* Recibe el tamaño de un tablero y genera una matriz cuadrada void* de largo n, inicializando structs Tierra en sus celdas.
******
* Input:
* int n : Descripción Parámetro
*****/
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

/*****
* void PasarTurno
******
* Recibe el tablero del juego. Recorre la matriz de izquierda a derecha y de arriba abajo intentando explotar cada una de las bombas en el tablero con TryExplotar.
******
* No tiene inputs, el tablero es una variable global.
*****/
void PasarTurno(){
    for(int i=0;i<dimension;i++){
        for(int j=0;j<dimension;j++){
            if(DirtOrBomb[i][j]=='b') TryExplotar(i,j);
        }
    }
    return;
}

/*****
* void ColocarBomba
******
* Recibe una Bomba y coordenadas. Coloca una Bomba en el tablero, en la celda especificada por el parámetro coordenadas.
******
* Input:
* Bomba* b : puntero al struct de la bomba a plantar.
* int fila : número que va del 0 a dimension-1, indica en que fila se plantará la bomba.
* int columna : número que va del 0 a dimension-1, indica en que columna se plantará la bomba.
*****/
void ColocarBomba(Bomba* b, int fila, int columna){
    DirtOrBomb[fila][columna] = 'b';
    Bomba* bomb = malloc(sizeof(Bomba));
    *bomb = *b;
    bomb->tierra_debajo = (Tierra*)tablero[fila][columna];
    tablero[fila][columna] = (void*)bomb;
    return;
}

/*****
* void MostrarTablero
******
* Muestra el tablero representando la Tierra con su vida, Bomba con o (letra “o” minúscula) y un tesoro descubierto con *.
******
* No tiene inputs, el tablero es una variable global.
*****/
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

/*****
* void MostrarBombas
******
* Muestra por pantalla las descripciones de las bombas que se encuentran en el tablero al momento de llamar la función.
******
* No tiene inputs, el tablero es una variable global.
*****/
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

/*****
* void VerTesoros
******
* Muestra todos los tesoros en el tablero (ocultos y revelados). No muestra Bombas. Los espacios en donde hay tesoros se marcan con * en vez de un número.
******
* No tiene inputs, el tablero es una variable global.
*****/
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

/*****
* void BorrarTablero
******
* Borra el tablero de la memoria Heap. En caso de haber bombas puestas también las elimina.
******
* No tiene inputs, el tablero es una variable global.
*****/
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

/*****
* int TreasureCheck
******
* Recorre el tablero generado en busca de tesoros, y los suma a allTreasures para llevar la cuenta de los tesoros.
******
* No hay inputs. Tablero, dimensión y allTreasures son variables globales.
******
* Returns:
* int, retorna la cantidad de tesoros encontrados en el tablero.
*****/
int TreasureCheck(){
    for(int i = 0;i<dimension;i++){
        for(int j = 0;j<dimension;j++){
            if(DirtOrBomb[i][j] == 't'){
                Tierra* dirtNow = (Tierra*)tablero[i][j];
                if(dirtNow->es_tesoro==1){
                    allTreasures++;
                }
            }
        }
    }
    return allTreasures;
}