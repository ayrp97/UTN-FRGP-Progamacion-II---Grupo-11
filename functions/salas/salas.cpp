
#include <iostream>
#include <locale>
#include "../../rlutil.h"
#include "../../mainHeader.h"
using namespace std;

void mostrarTituloSalas() {
    rlutil::setColor(rlutil::LIGHTCYAN);
    rlutil::locate(10, 2);
    cout << "============================================";
    rlutil::locate(10, 3);
    cout << "          GESTION DE SALAS DE CINE           ";
    rlutil::locate(10, 4);
    cout << "============================================";
    rlutil::setColor(rlutil::WHITE);
}

void mostrarMenuSalas() {
    rlutil::locate(14, 7);  cout << "1. Crear nueva sala";
    rlutil::locate(14, 8);  cout << "2. Mostrar todas las salas";
    rlutil::locate(14, 9);  cout << "3. Modificar sala existente";
    rlutil::locate(14, 10); cout << "4. Eliminar sala";
    rlutil::locate(14, 11); cout << "0. Volver al menu principal";
}

void salas() {
    rlutil::hidecursor();
    rlutil::cls();

    /* clsSalas gestorSalas; // Controlador principal de salas

    int opcion = -1;
    while (opcion != 0) {
        fondoVentana();
        mostrarTituloSalas();
        mostrarMenuSalas();

        rlutil::setColor(rlutil::GREEN);
        rlutil::locate(14, 13);
        cout << "Seleccione una opcion: ";
        rlutil::setColor(rlutil::WHITE);
        cin >> opcion;

        PlaySound(TEXT("../../sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
        rlutil::cls();

        switch (opcion) {
        case 1: {
            fondoVentana();
            mostrarTituloSalas();
            gestorSalas.crearSala();
            rlutil::anykey();
            break;
        }
        case 2: {
            fondoVentana();
            mostrarTituloSalas();
            gestorSalas.mostrarSalas();
            rlutil::anykey();
            break;
        }
        case 3: {
            fondoVentana();
            mostrarTituloSalas();
            gestorSalas.modificarSala();
            rlutil::anykey();
            break;
        }
        case 4: {
            fondoVentana();
            mostrarTituloSalas();
            gestorSalas.eliminarSala();
            rlutil::anykey();
            break;
        }
        case 0:
            PlaySound(TEXT("../../sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
            rlutil::cls();
            break;

        default:
            rlutil::cls();
            rlutil::setColor(rlutil::RED);
            rlutil::locate(10, 6); cout << "===========================================";
            rlutil::locate(10, 7); cout << "|     OPCION INVALIDA, INTENTE NUEVAMENTE  |";
            rlutil::locate(10, 8); cout << "===========================================";
            rlutil::setColor(rlutil::WHITE);
            rlutil::anykey();
            break;
        }

        rlutil::cls();
    }
        */
}




