#include <iostream>   // Fundamental para la entrada y salida est�ndar del programa. Permite trabajar con flujos de datos, como la consola.
#include <locale>     // Proporciona herramientas para manejar la localizaci�n y adaptar programas a diferentes configuraciones regionales.
#include "utilities/rlutil.h"   // Facilita la manipulaci�n de la consola en aplicaciones de texto. Se usa principalmente para juegos roguelike y otras aplicaciones que requieren control sobre el cursor, colores y entrada de teclado.
#include <windows.h>  // Permite interactuar con el sistema operativo a nivel bajo, facilitando la creaci�n de aplicaciones con interfaz gr�fica, gesti�n de memoria, entrada/salida, multithreading y m�s.
#include <mmsystem.h> // Proporciona funciones para manejar multimedia, como reproducci�n de sonido, control de dispositivos de audio y temporizadores.
#include <string>     // Permite trabajar con cadenas de caracteres de manera m�s flexible y segura que los arreglos de caracteres
#include <cstdlib>    // Proporciona funciones est�ndar relacionadas con la gesti�n de memoria, generaci�n de n�meros aleatorios, conversi�n de tipos y control del programa
#include "mainHeader.h" // Importa las funciones del archivo
#include <stdlib.h>

using namespace std;

int main(){
    //Declaramos la variable de corte
    int corteTotal = 1;

    // BIENVENIDA DURANTE EL INICIO DEL PROGRAMA
  PlaySound(TEXT("../../sounds/Bienvenida.wav"),NULL,SND_FILENAME | SND_ASYNC ); //SND_LOOP

    // CAPA DE MEN� PRINCIPAL
    while (corteTotal !=0){
        menuGestor();
        corteTotal = 0;
        rlutil::cls();
    }
  exit(0);
}
