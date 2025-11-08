#include <iostream>
#include <locale>
#include "../../rlutil.h"
#include "../../mainHeader.h"
#include "clsdataPeliculas.h"
#include "clsPeliculas.h"
#include "../../utilities/classes/clsFechas.h"
using namespace std;

void peliculas() {
    rlutil::hidecursor();
    rlutil::cls();
    fondoVentana();

    clsPelicula gestor; // <<--- Este es tu "manejador" principal

    int opcion = -1;
    string id;

    while (opcion != 0) {
        rlutil::cls();
        rlutil::setColor(rlutil::GREEN);
        rlutil::locate(10, 5); cout << "===== MENU DE PELICULAS =====";
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(10, 7); cout << "1. Agregar nueva pelicula";
        rlutil::locate(10, 8); cout << "2. Modificar pelicula";
        rlutil::locate(10, 9); cout << "3. Dar de baja";
        rlutil::locate(10,10); cout << "4. Dar de alta";
        rlutil::locate(10,11); cout << "5. Mostrar todas";
        rlutil::locate(10,12); cout << "0. Volver al menu principal";

        rlutil::locate(10,14); cout << "Opcion: ";
        cin >> opcion;
        cin.ignore(); // limpiar el buffer por seguridad
        rlutil::cls();

        switch (opcion) {
            case 1:
                gestor.cargarNuevaPelicula();
                break;

            case 2:
                cout << "Ingrese ID de la pelicula a modificar: ";
                getline(cin, id);
                gestor.modificarPelicula(id);
                break;

            case 3:
                cout << "Ingrese ID de la pelicula a dar de baja: ";
                getline(cin, id);
                gestor.darDeBaja(id);
                break;

            case 4:
                cout << "Ingrese ID de la pelicula a activar: ";
                getline(cin, id);
                gestor.darDeAlta(id);
                break;

            case 5:
                gestor.mostrarPeliculas();
                rlutil::anykey(); // espera que el usuario presione una tecla
                break;

            case 0:
                rlutil::cls();
                cout << "Volviendo al menu principal...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
                rlutil::anykey();
                break;
        }
    }
}








