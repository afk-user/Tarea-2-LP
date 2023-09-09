Nombre: Javier Matamala
Rol: 202273560-0

Compilado con gcc 11.4, desde WSL Ubuntu 22.04

Adiciones al código base:
- Se añadieron las variables allTreasures y foundTreasures a Tablero.c
    - allTreasures es un contador global para saber la cantidad total de tesoros en el tablero.
    - foundTreasures es un contador global que incrementa cada vez que la explisión de una bomba revela un tesoro en el tablero.

- Se añadieron 9 variables a TreasureFinder.c
    - input, row y column son las variables que guardan datos que se reciben desde la terminal, siendo input el número de una acción y row y column la fila y columna en la que se pondrá una bomba.
    - turn_counter es un contador que crece con cada turno que pasa, y se usa para el display del turno que va sobre el tablero.
    - end_turn y end_game son flags para determinar cuando se termina un turno y cuando se termina el juego, respectivamente.
    - surrender es un flag para dar un texto distinto cuando se termina el juego en caso de rendirse.
    - exit_input1 y exit_input2 son tipo carácter para poder permitir "usar" cualquier tecla. Son necesarias dos flags para salir del juego dado que exit_input1 captura el "\n" del input anterior, y exit_input2 captura la acción de presionar Enter para poder salir del programa.
    (Nótese que escribir algo en la terminal antes de salir del juego no afecta en nada, dado que hay que presionar Enter para mandar lo escrito por la terminal, entonces es más simple solo presionar Enter para salir.)

Instrucciones de uso:
- Extraer todos los archivos que se encuentran en el .tar.gz que se entrega en un directorio vacío.
- En el directorio recién creado, abrir una terminal que sea capaz de ejecutar gcc, make y valgrind.
- Con la terminal ya abierta, hay 4 opciones elegibles a ejecutar:
    - make main: Compila los archivos Bomba.c Bomba.h Tablero.c Tablero.h Tierra.h y TreasureFinder.c, y devuelve un ejecutable de terminal llamado main (sin extensión).
    - make run: Ejecuta el archivo main, y si este no existe entonces lo compila.
    - make valrun: Ejecuta el archivo main con la aplicación valgrind para detectar advertencias y fugas de memoria, y si este no existe entonces lo compila. (Usado para el testeo del programa.)
    - make compress: Crea un .tar.gz cuyo contenido son los seis archivos de compilación del programa, además del Makefile y este readme.
- Para compilar y abrir el ejecutable escriba make run en la terminal.

Dentro del juego:
El flujo del juego es el siguiente:
- El programa le va a pedir que seleccione un tamaño para el tablero, y lo va a selecionar escribiendo 1, 2 o 3 en la terminal.
- Luego de eso, se le mostrará una vez por turno el tablero sobre el cual estará jugando.
- En dicho tablero se le mostrarán las siguientes cosas:
    - La vida de una celda de tierra, indicada con números del 3 al 0.
    - Las bombas puestas, indicadas con una o minúscula.
    - Los tesoros descubiertos, indicados por un *.
- Después de mostrar el tablero, se le mostrarán las siguientes opciones:
    - Colocar bomba
    - Mostrar bombas
    - Mostrar tesoros
    - Pasar turno
    - Rendirse
- Colocar Bomba abre un diálogo en el cual le pide una fila, una columna y un tipo de bomba. Además, hace que termine el turno tras poner la bomba.
- La fila y la columna se usarán para saber donde poner la bomba en el tablero, y el tipo de bomba determina como y cuando va a explotar.
- Estos son los tipos de bombas:
    - ExplosionPunto: Afecta una sola celda y le quita toda la vida, y explota en un turno.
    - ExplosionX: Afecta una cruz y le quita un punto de vida a cada tierra, y explota en tres turnos.
- Mostrar tesoros, Pasar turno y Rendirse son opciones que se añadieron para facilitar el desarrollo del programa:
    - Mostrar tesoros muestra las ubicaciones de todos los tesoros en el tablero, pero no muestra bombas.
    - Pasar turno salta un turno, más que nada usado para saber como explotan las bombas X.
    - Rendirse es cuando ya no sabe donde más pueden haber tesoros, entonces decide terminar el juego.
- El juego termina una vez que se encuentran todos los tesoros del tablero, o el jugador se rinde.