main: Bomba.c Tablero.C TreasureFinder.c Tierra.h Bomba.h Tablero.h
	gcc Bomba.c Tablero.c TreasureFinder.c -o output -Wall -g

valrun: output
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./output

compress: Bomba.c Tablero.C TreasureFinder.c Tierra.h Bomba.h Tablero.h readme.txt Makefile
	tar -czf Tarea2LP_202273560-0.tar.gz  Bomba.c Tablero.C TreasureFinder.c Tierra.h Bomba.h Tablero.h readme.txt Makefile