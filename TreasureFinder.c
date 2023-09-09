#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Tierra.h"
#include "Bomba.h"
#include "Tablero.h"

int input, row, column, turn_counter = 0, end_game = 0, end_turn = 0, surrender = 0;
char exit_input1,exit_input2;

int main(int argc, char const *argv[]){
    allTreasures = 0, foundTreasures = 0; // fueron declaradas en Tablero.c
    printf("¡Bienvenido a Treasure Finder!\nIndique el tamaño del tablero a jugar:\n1.7x7  2.10x10  3.12x12\nSu input: ");
    scanf("%d",&input);
    printf("Empezando juego... ");
    switch (input){
    case 1: dimension = 7;
        break;
    case 2: dimension = 10;
        break;
    case 3: dimension = 12;
        break;
    }
    srand(time(NULL));

    IniciarTablero(dimension);
    while (TreasureCheck() == 0){
        BorrarTablero();
        IniciarTablero(dimension);       
    }
    printf("¡listo!\n\n");
    Bomba* bomb = malloc(sizeof(Bomba));
    while (end_game == 0){
        turn_counter++;
        end_turn = 0;
        printf("Tablero - Turno %d:\n",turn_counter);
        MostrarTablero();
        printf("\n");
        while (end_turn == 0){
            if(foundTreasures==allTreasures){
                end_game = 1;
                break;
            }
            printf("Seleccione una acción:\n1.Colocar Bomba  2.Mostrar Bombas  3.Mostrar Tesoros  4.Pasar Turno  5.Rendirse\nEscoja una opción: ");
            scanf("%d",&input);
            printf("\n");

            switch (input){
            case 1:
                printf("Indique coordenadas de la bomba\nFila: ");
                scanf("%d",&row);
                printf("Columna: ");
                scanf("%d",&column);
                printf("Indique forma en que explota la bomba\n1.Punto  2.X\nSu input: ");
                scanf("%d",&input);
                printf("\n");

                if(input==1){
                    bomb->contador_turnos = 1;
                    bomb->explotar = ExplosionPunto;
                } else if(input==2){
                    bomb->contador_turnos = 3;
                    bomb->explotar = ExplosionX;
                }

                ColocarBomba(bomb,(int)row-1,(int)column-1);
                PasarTurno();
                end_turn = 1;
                break;

            case 2: MostrarBombas();
                break;

            case 3: VerTesoros();
                break;

            case 4: PasarTurno();
                end_turn = 1;
                break;

            case 5:
                end_turn = 1, end_game = 1, surrender = 1;
                break;
            }
        }
    }
    printf("Juego Terminado\n");
    if (surrender==1){
        printf("Mejor suerte para la próxima...\n");
    }
    else printf("¡Felicidades, Ganaste el juego!\n");
    printf("Presione la tecla Enter para salir...\n");
    
    scanf("%c",&exit_input1);
    while ((exit_input2 = getchar()) != '\n' && exit_input2 != EOF);

    BorrarTablero();
    free(bomb);
    return 0;
}