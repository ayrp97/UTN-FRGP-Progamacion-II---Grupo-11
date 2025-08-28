#include <iostream>   // Fundamental para la entrada y salida estándar del programa. Permite trabajar con flujos de datos, como la consola.
#include <locale>     // Proporciona herramientas para manejar la localización y adaptar programas a diferentes configuraciones regionales.
#include "rlutil.h"   // Facilita la manipulación de la consola en aplicaciones de texto. Se usa principalmente para juegos roguelike y otras aplicaciones que requieren control sobre el cursor, colores y entrada de teclado.
#include <windows.h>  // Permite interactuar con el sistema operativo a nivel bajo, facilitando la creación de aplicaciones con interfaz gráfica, gestión de memoria, entrada/salida, multithreading y más.
#include <mmsystem.h> // Proporciona funciones para manejar multimedia, como reproducción de sonido, control de dispositivos de audio y temporizadores.
#include <string>     // Permite trabajar con cadenas de caracteres de manera más flexible y segura que los arreglos de caracteres
#include <cstdlib>    // Proporciona funciones estándar relacionadas con la gestión de memoria, generación de números aleatorios, conversión de tipos y control del programa
#include "mainHeader.h" // Importa las funciones del archivo
#include <stdlib.h>

using namespace std;

int main(){
    //Declaramos la variable de corte
    int corteTotal = 1;

    // BIENVENIDA DURANTE EL INICIO DEL PROGRAMA
    PlaySound(TEXT("Bienvenida.wav"),NULL,SND_FILENAME | SND_ASYNC ); //SND_LOOP

    // CAPA DE MENÚ PRINCIPAL
    while (corteTotal !=0){
        menuGestor();
        corteTotal = 0;
        rlutil::cls();
    }
  exit(0);
}
