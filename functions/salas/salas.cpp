#include <iostream>
#include <locale>
#include "../../rlutil.h"
#include "../../mainHeader.h"
#include "clsSalas.h"
#include "function_persistenciaSalas.h"
#include "funcion/clsFunciones.h"
#include "../peliculas/clsPeliculas.h"
#include <windows.h>

using namespace std;

// ---------------------------------------------------------
// Función para mostrar ítems con diseño tipo películas.cpp
// ---------------------------------------------------------
void mostrarItemSalas(const char* text, int posx, int posy, bool selected) {
    if (selected) rlutil::setBackgroundColor(rlutil::BLUE);
    else rlutil::setBackgroundColor(rlutil::BLACK);

    rlutil::locate(posx, posy);
    cout << text << endl;

    rlutil::setBackgroundColor(rlutil::BLACK);
}

// ---------------------------------------------------------
// MENÚ SALAS ESTILO PELÍCULAS
// ---------------------------------------------------------

void salas() {

    rlutil::hidecursor();
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);

    clsSala gestorSalas;
    clsPelicula gestorPeliculas;
    clsFunciones funciones(2000);

    bool guardadoAutomatico = true;

    // Persistencia
    cargarSalas(gestorSalas);
    cargarPeliculas(gestorPeliculas);
    funciones.cargarFunciones("funciones.dat");

    int opcion = 0;
    bool salir = false;

        while (!salir) {


            rlutil::cls();
            fondoVentana();

            // ---------------- TÍTULO CENTRADO ----------------
            rlutil::setColor(rlutil::YELLOW);
            rlutil::locate(51, 10); // CENTRO EXACTO para un texto de 17 chars
            cout << "GESTION DE SALAS";

            rlutil::setColor(rlutil::WHITE);

            // ---------------- MENÚ PRINCIPAL CENTRADO ----------------
            // X = 44, Y desde 13 hacia abajo

            mostrarItemSalas(" CREAR NUEVA SALA            ", 44, 13, opcion == 0);
            mostrarItemSalas(" MOSTRAR TODAS               ", 44, 14, opcion == 1);
            mostrarItemSalas(" MODIFICAR SALA              ", 44, 15, opcion == 2);
            mostrarItemSalas(" VER CAPACIDAD DE SALA       ", 44, 16, opcion == 3);
            mostrarItemSalas(" CONFIGURACION DE GUARDADO   ", 44, 17, opcion == 4);

            // ------------------- FUNCIONES -------------------
            mostrarItemSalas(" GENERAR FUNCION UNICA       ", 44, 19, opcion == 5);
            mostrarItemSalas(" GENERAR FUNCIONES POR DIA   ", 44, 20, opcion == 6);
            mostrarItemSalas(" GENERAR FUNCIONES POR MES   ", 44, 21, opcion == 7);

            // ------------------- SALIR -----------------------
            mostrarItemSalas(" VOLVER AL MENU PRINCIPAL    ", 44, 23, opcion == 8);

            // ------------------- POINTER ----------------------
            // La fórmula de ubicación es correcta para manejar los saltos de línea en Y=18 y Y=22
            rlutil::locate(41, 13 + opcion + (opcion >= 5 ? 1 : 0) + (opcion == 8 ? 1 : 0));
            cout << (char)175;

            // ------------------- Navegación y Ejecución -------------------
            switch (rlutil::getkey()) {
                case 14: // Flecha ARRIBA
                    PlaySound(TEXT("../../sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    opcion--;
                    if (opcion < 0) opcion = 0;
                    break;

                case 15: // Flecha ABAJO
                    PlaySound(TEXT("../../sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    opcion++;
                    if (opcion > 8) opcion = 8;
                    break;

                case 1: // TECLA ENTER (Ejecutar)
                    PlaySound(TEXT("../../sounds/keySoundStrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    rlutil::cls();

                    // ---------------------------------------------------
                    // Selección de opciones (Se ejecuta SOLAMENTE al presionar Enter)
                    // ---------------------------------------------------
                    switch (opcion) {

                        case 0:
                            gestorSalas.crearSala();
                            if (guardadoAutomatico) guardarSalas(gestorSalas);
                            rlutil::anykey();
                            break;

                        case 1:
                            gestorSalas.mostrarSalas();
                            rlutil::anykey();
                            break;

                        case 2: {
                            string id;
                            cout << "Ingrese ID de la sala a modificar: ";
                            getline(cin, id);
                            gestorSalas.modificarSala(id);
                            if (guardadoAutomatico) guardarSalas(gestorSalas);
                            }
                            rlutil::anykey();
                            break;

                        case 3: {
                            string id;
                            cout << "Ingrese ID de la sala: ";
                            getline(cin, id);
                            gestorSalas.verCapacidad(id);
                            }
                            rlutil::anykey();
                            break;

                        case 4:
                            menuGuardarSalas(guardadoAutomatico, gestorSalas);
                            rlutil::anykey();
                            break;

                        // ---------- FUNCIONES ----------
                        case 5:
                            funciones.crearFuncion(gestorSalas, gestorPeliculas);
                            funciones.guardarFunciones("funciones.dat");
                            rlutil::anykey();
                            break;

                        case 6:
                            funciones.crearFuncionesPorDia(gestorSalas, gestorPeliculas);
                            funciones.guardarFunciones("funciones.dat");
                            rlutil::anykey();
                            break;

                        case 7:
                            funciones.crearFuncionesPorMes(gestorSalas, gestorPeliculas);
                            funciones.guardarFunciones("funciones.dat");
                            rlutil::anykey();
                            break;

                        case 8:
                            guardarSalas(gestorSalas);
                            funciones.guardarFunciones("funciones.dat");
                            salir = true;
                            menuGestor();
                            break;
                    }

                    rlutil::cls(); // Limpiar después de la ejecución de una opción
                    break;         // Salir del switch principal (el de rlutil::getkey())
            }
        }
}
