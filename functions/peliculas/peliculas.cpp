#include <iostream>
<<<<<<< HEAD
#include <locale>
#include "rlutil.h"
#include "mainHeader.h"
using namespace std;

void peliculas(){

    rlutil::hidecursor(); // Herramienta que oculta el cursosor
    rlutil::cls();        // Herramienta que limpia la terminal
    fondoVentana();
    rlutil::setColor(rlutil::GREEN);
    rlutil::locate(41,29);  cout << " <ESC> ";
    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(48,29);  cout <<" Para volver al menu principal  ";

    int cortePeliculas = 1;

    while (cortePeliculas !=0) {
        switch(rlutil::getkey()){
            case 0:
                PlaySound(TEXT("keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                cortePeliculas = 0;
                rlutil::cls();
                break;

            default:
                rlutil::cls();
                rlutil::setColor(rlutil::RED);
                rlutil::locate(7,4);  cout << "=========================================";
                rlutil::locate(7,5);  cout << "|";
                rlutil::locate(47,5); cout << "|";
                rlutil::locate(7,6);  cout << "=========================================";
                rlutil::setColor(rlutil::WHITE);
                rlutil::locate(8,5);  cout << "  Utilice las teclas correspondientes!";
                break;
            }

     }
}








=======
#include <string>
#include <windows.h>
#include "clsPeliculas.h"
#include "clsdataPeliculas.h"
#include "function_persistenciaPeliculas.h"
#include "../../rlutil.h"
#include "../../mainHeader.h"
#include "../../utilities/classes/clsFechas.h"

using namespace std;

void peliculas() {
    configuracionesVisuales();
    clsPelicula gestor;
    bool guardadoAutomatico = true;
    cargarPeliculas(gestor);

    while (true) {
        rlutil::cls();
        fondoVentana();

        const char* opciones[] = {
            " AGREGAR NUEVA PELICULA ",
            " MODIFICAR PELICULA ",
            " DAR DE BAJA ",
            " DAR DE ALTA ",
            " MOSTRAR TODAS ",
            " CONFIGURACION GUARDADO ",
            " VOLVER "
        };

        int cantidadOpciones = 7;

        int op = menuInteractivo(opciones, cantidadOpciones, " MODULO DE PELICULAS", 50, 20);

        if (op == -1 || op == 6) {
            break;
        }

        rlutil::cls();

        switch (op) {
            case 0:
                gestor.cargarNuevaPelicula();
                break;

            case 1:
                {
                    fondoVentana();
                    rlutil::setColor(rlutil::YELLOW);
                    rlutil::locate(45, 10); cout << "MODIFICAR PELICULA";

                    rlutil::setColor(rlutil::WHITE);
                    rlutil::locate(40, 12); cout << "Ingrese ID de la pelicula: ";

                    rlutil::showcursor();
                    string id;
                    getline(cin, id);
                    rlutil::hidecursor();

                    if (!id.empty()) gestor.modificarPelicula(id);
                }
                break;

            case 2:
                {
                    fondoVentana();
                    rlutil::setColor(rlutil::RED); // Rojo para indicar peligro/baja
                    rlutil::locate(45, 10); cout << "DAR DE BAJA PELICULA";

                    rlutil::setColor(rlutil::WHITE);
                    rlutil::locate(40, 12); cout << "Ingrese ID de la pelicula: ";

                    rlutil::showcursor();
                    string id;
                    getline(cin, id);
                    rlutil::hidecursor();

                    if (!id.empty()) gestor.darDeBaja(id);
                }
                break;

            case 3:
                {
                    fondoVentana();
                    rlutil::setColor(rlutil::GREEN); // Verde para alta
                    rlutil::locate(45, 10); cout << "REACTIVAR PELICULA";

                    rlutil::setColor(rlutil::WHITE);
                    rlutil::locate(40, 12); cout << "Ingrese ID de la pelicula: ";

                    rlutil::showcursor();
                    string id;
                    getline(cin, id);
                    rlutil::hidecursor();

                    if (!id.empty()) gestor.darDeAlta(id);
                }
                break;

            case 4:
                gestor.mostrarPeliculas();
                rlutil::anykey();
                break;

            case 5:
                menuGuardarPeliculas(guardadoAutomatico, gestor);
                break;
        }
    }
}
>>>>>>> develop
