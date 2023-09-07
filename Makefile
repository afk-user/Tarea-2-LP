main: Bomba.c Bomba.h Tablero.c Tablero.h Tierra.h TreasureFinder.c
	gcc Bomba.c Tablero.c TreasureFinder.c -o main -Wall -g

run: main
	./main
	
valrun: main
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

compress: Bomba.c Bomba.h Tablero.c Tablero.h Tierra.h TreasureFinder.c readme.txt Makefile
	tar -czf Tarea2LP_202273560-0.tar.gz Bomba.c Bomba.h Tablero.c Tablero.h Tierra.h TreasureFinder.c readme.txt Makefile