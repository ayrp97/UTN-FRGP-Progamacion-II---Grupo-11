#include <iostream>
#include <string>
#include "../../rlutil.h"
#include <windows.h>
#include "../../mainHeader.h"
#include "clsdataPeliculas.h"
#include "clsPeliculas.h"
#include "../../utilities/classes/clsFechas.h"
#include "function_persistenciaPeliculas.h"

using namespace std;

void mostrarItemPeliculas(const char* text, int posx, int posy, bool selected) {
    if (selected) {
        rlutil::setBackgroundColor(rlutil::BLUE);
    } else {
        rlutil::setBackgroundColor(rlutil::BLACK);
    }
    rlutil::locate(posx, posy);
    cout << text << endl;
    rlutil::setBackgroundColor(rlutil::BLACK);
}

void peliculas() {
    rlutil::hidecursor();
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);

    clsPelicula gestor;
    bool guardadoAutomatico = true;
    cargarPeliculas(gestor);

    int opcion = 0; // índice seleccionado
    bool salir = false;

    while (!salir) {
        fondoVentana();
        rlutil::setColor(rlutil::YELLOW);
        rlutil::locate(46, 17);
        cout << "GESTION DE PELICULAS";

        rlutil::setColor(rlutil::WHITE);
        mostrarItemPeliculas(" AGREGAR NUEVA PELICULA ", 50, 20, opcion == 0);
        mostrarItemPeliculas(" MODIFICAR PELICULA     ", 50, 21, opcion == 1);
        mostrarItemPeliculas(" DAR DE BAJA            ", 50, 22, opcion == 2);
        mostrarItemPeliculas(" DAR DE ALTA            ", 50, 23, opcion == 3);
        mostrarItemPeliculas(" MOSTRAR TODAS          ", 50, 24, opcion == 4);
        mostrarItemPeliculas(" CONFIGURACION GUARDADO ", 50, 25, opcion == 5);
        mostrarItemPeliculas(" VOLVER AL MENU         ", 50, 26, opcion == 6);

        rlutil::locate(47, 20 + opcion);
        cout << (char)175; // puntero >>

        switch (rlutil::getkey()) {
            case 14: // Flecha arriba
                rlutil::locate(47, 20 + opcion);
                cout << " ";
                opcion--;
                PlaySound(TEXT("D:\\UTN FRGP\\PROG II\\Salas de Cine\\PROG2-TP1-G11\\sounds\\keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                if (opcion < 0) opcion = 0;
                break;

            case 15: // Flecha abajo
                rlutil::locate(47, 20 + opcion);
                cout << " ";
                opcion++;
                PlaySound(TEXT("D:\\UTN FRGP\\PROG II\\Salas de Cine\\PROG2-TP1-G11\\sounds\\keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                if (opcion > 6) opcion = 6;
                break;

            case 1: // Enter
                PlaySound(TEXT("D:\\UTN FRGP\\PROG II\\Salas de Cine\\PROG2-TP1-G11\\sounds\\keySoundStrong.wav"),NULL,SND_FILENAME | SND_ASYNC );
                rlutil::cls();
                switch (opcion) {
                    case 0:
                        gestor.cargarNuevaPelicula();
                        rlutil::cls();
                        break;
                    case 1: {
                        string id;
                        cout << "Ingrese ID de la pelicula a modificar: ";
                        getline(cin, id);
                        gestor.modificarPelicula(id);
                        rlutil::cls();
                        break;
                    }
                    case 2: {
                        string id;
                        cout << "Ingrese ID de la pelicula a dar de baja: ";
                        getline(cin, id);
                        gestor.darDeBaja(id);
                        rlutil::cls();
                        break;
                    }
                    case 3: {
                        string id;
                        cout << "Ingrese ID de la pelicula a activar: ";
                        getline(cin, id);
                        gestor.darDeAlta(id);
                        rlutil::cls();
                        break;
                    }
                    case 4:
                        gestor.mostrarPeliculas();
                        rlutil::anykey();
                        rlutil::cls();
                        break;
                    case 5:
                        menuGuardarPeliculas(guardadoAutomatico, gestor);
                        rlutil::cls();
                        break;
                    case 6:
                        salir = true;
                        rlutil::cls();
                        break;
                }
                break;
        }
    }
}








