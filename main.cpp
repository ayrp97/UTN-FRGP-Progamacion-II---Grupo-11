<<<<<<< HEAD
#include <iostream>   // Fundamental para la entrada y salida estándar del programa. Permite trabajar con flujos de datos, como la consola.
#include <locale>     // Proporciona herramientas para manejar la localización y adaptar programas a diferentes configuraciones regionales.
#include "utilities/rlutil.h"   // Facilita la manipulación de la consola en aplicaciones de texto. Se usa principalmente para juegos roguelike y otras aplicaciones que requieren control sobre el cursor, colores y entrada de teclado.
#include <windows.h>  // Permite interactuar con el sistema operativo a nivel bajo, facilitando la creación de aplicaciones con interfaz gráfica, gestión de memoria, entrada/salida, multithreading y más.
#include <mmsystem.h> // Proporciona funciones para manejar multimedia, como reproducción de sonido, control de dispositivos de audio y temporizadores.
#include <string>     // Permite trabajar con cadenas de caracteres de manera más flexible y segura que los arreglos de caracteres
#include <cstdlib>    // Proporciona funciones estándar relacionadas con la gestión de memoria, generación de números aleatorios, conversión de tipos y control del programa
=======
#include <iostream>   // Fundamental para la entrada y salida estï¿½ndar del programa. Permite trabajar con flujos de datos, como la consola.
#include <locale>     // Proporciona herramientas para manejar la localizaciï¿½n y adaptar programas a diferentes configuraciones regionales.
#include "utilities/rlutil.h"   // Facilita la manipulaciï¿½n de la consola en aplicaciones de texto. Se usa principalmente para juegos roguelike y otras aplicaciones que requieren control sobre el cursor, colores y entrada de teclado.
#include <windows.h>  // Permite interactuar con el sistema operativo a nivel bajo, facilitando la creaciï¿½n de aplicaciones con interfaz grï¿½fica, gestiï¿½n de memoria, entrada/salida, multithreading y mï¿½s.
#include <mmsystem.h> // Proporciona funciones para manejar multimedia, como reproducciï¿½n de sonido, control de dispositivos de audio y temporizadores.
#include <string>     // Permite trabajar con cadenas de caracteres de manera mï¿½s flexible y segura que los arreglos de caracteres
#include <cstdlib>    // Proporciona funciones estï¿½ndar relacionadas con la gestiï¿½n de memoria, generaciï¿½n de nï¿½meros aleatorios, conversiï¿½n de tipos y control del programa
>>>>>>> develop
#include "mainHeader.h" // Importa las funciones del archivo
#include <stdlib.h>

using namespace std;

int main(){
    //Declaramos la variable de corte
    int corteTotal = 1;

    // BIENVENIDA DURANTE EL INICIO DEL PROGRAMA
<<<<<<< HEAD
    PlaySound(TEXT("sounds/Bienvenida.wav"),NULL,SND_FILENAME | SND_ASYNC ); //SND_LOOP

    // CAPA DE MENÚ PRINCIPAL
=======
  PlaySound(TEXT("D:\\UTN FRGP\\PROG II\\Salas de Cine\\PROG2-TP1-G11\\sounds\\Bienvenida.wav"),NULL,SND_FILENAME | SND_ASYNC ); //SND_LOOP

    // CAPA DE MENï¿½ PRINCIPAL
>>>>>>> develop
    while (corteTotal !=0){
        menuGestor();
        corteTotal = 0;
        rlutil::cls();
    }
  exit(0);
}
