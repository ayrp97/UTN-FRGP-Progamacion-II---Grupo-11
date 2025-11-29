#include <iostream>
#include <locale>
#include <windows.h>
#include "../../rlutil.h"
#include "../../mainHeader.h"
#include "clsSalas.h"
#include "function_persistenciaSalas.h"
#include "funcion/clsFunciones.h"
#include "../peliculas/clsPeliculas.h"

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
// SUBMENU: GESTION DE FUNCIONES
// ---------------------------------------------------------
void menuFunciones(clsFunciones& funciones, clsSala& gestorSalas, clsPelicula& gestorPeliculas) {
    int opcion = 0;
    bool salir = false;

    while (!salir) {
        rlutil::cls();
        fondoVentana();

        rlutil::setColor(rlutil::YELLOW);
        rlutil::locate(48, 10);
        cout << "GESTION DE FUNCIONES";

        rlutil::setColor(rlutil::WHITE);

        // Opciones del submenú
        mostrarItemSalas(" CREAR FUNCION UNICA         ", 44, 13, opcion == 0);
        mostrarItemSalas(" CREAR FUNCIONES POR DIA     ", 44, 14, opcion == 1);
        mostrarItemSalas(" CREAR FUNCIONES POR MES     ", 44, 15, opcion == 2);
        mostrarItemSalas(" MOSTRAR TODAS LAS FUNCIONES ", 44, 17, opcion == 3);
        mostrarItemSalas(" FUNCIONES POR SALA          ", 44, 18, opcion == 4);
        mostrarItemSalas(" FUNCIONES POR FECHA         ", 44, 19, opcion == 5);
        mostrarItemSalas(" DESACTIVAR FUNCION          ", 44, 20, opcion == 6);
        mostrarItemSalas(" VOLVER                      ", 44, 22, opcion == 7);

        // Pointer
        rlutil::locate(41, 13 + opcion + (opcion >= 3 ? 1 : 0) + (opcion == 7 ? 1 : 0));
        cout << (char)175;

        int key = rlutil::getkey();

        switch (key) {
            case 14: // Flecha ARRIBA
                PlaySound(TEXT("D:\\UTN FRGP\\PROG II\\Salas de Cine\\PROG2-TP1-G11\\sounds\\keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                opcion--;
                if (opcion < 0) opcion = 7;
                break;

            case 15: // Flecha ABAJO
                PlaySound(TEXT("D:\\UTN FRGP\\PROG II\\Salas de Cine\\PROG2-TP1-G11\\sounds\\keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                opcion++;
                if (opcion > 7) opcion = 0;
                break;

            case 1: { // ENTER
                PlaySound(TEXT("D:\\UTN FRGP\\PROG II\\Salas de Cine\\PROG2-TP1-G11\\sounds\\keySoundStrong.wav"),NULL,SND_FILENAME | SND_ASYNC );
                rlutil::cls();
                fondoVentana();

                switch (opcion) {
                    case 0: // CREAR FUNCION UNICA
                        funciones.crearFuncion(gestorSalas, gestorPeliculas);
                        funciones.guardarFunciones("funciones.dat");
                        rlutil::anykey();
                        break;

                    case 1: // CREAR FUNCIONES POR DIA
                        funciones.crearFuncionesPorDia(gestorSalas, gestorPeliculas);
                        funciones.guardarFunciones("funciones.dat");
                        rlutil::anykey();
                        break;

                    case 2: // CREAR FUNCIONES POR MES
                        funciones.crearFuncionesPorMes(gestorSalas, gestorPeliculas);
                        funciones.guardarFunciones("funciones.dat");
                        rlutil::anykey();
                        break;

                    case 3: // MOSTRAR TODAS LAS FUNCIONES
                        funciones.mostrarFunciones(gestorPeliculas);
                        rlutil::anykey();
                        break;

                    case 4: { // FUNCIONES POR SALA
                        string idSala;
                        cout << "Ingrese ID de la sala: ";
                        getline(cin, idSala);
                        funciones.mostrarFuncionesPorSala(idSala, gestorPeliculas);
                        rlutil::anykey();
                        break;
                    }

                    case 5: { // FUNCIONES POR FECHA
                        int d, m, a;
                        cout << "Ingrese dia: ";  cin >> d;
                        cout << "Ingrese mes: "; cin >> m;
                        cout << "Ingrese anio: "; cin >> a;
                        cin.ignore();
                        funciones.mostrarFuncionesPorFecha(d, m, a, gestorPeliculas);
                        rlutil::anykey();
                        break;
                    }

                    case 6: { // DESACTIVAR FUNCION
                        string id;
                        cout << "Ingrese ID de funcion a desactivar: ";
                        getline(cin, id);

                        int pos = funciones.buscarFuncion(id);
                        if (pos == -1) {
                            cout << "No se encontro la funcion con ese ID.\n";
                        } else {
                            funciones.desactivarFuncion(id);
                            funciones.guardarFunciones("funciones.dat");
                            cout << "Funcion desactivada correctamente.\n";
                        }
                        rlutil::anykey();
                        break;
                    }

                    case 7: // VOLVER
                        salir = true;
                        break;
                }

                break;
            }
        }
    }
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

    // Persistencia inicial
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
        rlutil::locate(51, 10); // CENTRO para "GESTION DE SALAS"
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
        mostrarItemSalas(" GESTIONAR FUNCIONES         ", 44, 19, opcion == 5);

        // ------------------- SALIR -----------------------
        mostrarItemSalas(" VOLVER AL MENU PRINCIPAL    ", 44, 21, opcion == 6);

        // ------------------- POINTER ----------------------
        rlutil::locate(41, 13 + opcion);
        cout << (char)175;

        // ------------------- Navegación y Ejecución -------------------
        switch (rlutil::getkey()) {
            case 14: // Flecha ARRIBA
                PlaySound(TEXT("D:\\UTN FRGP\\PROG II\\Salas de Cine\\PROG2-TP1-G11\\sounds\\keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                opcion--;
                if (opcion < 0) opcion = 6;
                break;

            case 15: // Flecha ABAJO
                PlaySound(TEXT("D:\\UTN FRGP\\PROG II\\Salas de Cine\\PROG2-TP1-G11\\sounds\\keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                opcion++;
                if (opcion > 6) opcion = 0;
                break;

            case 1: { // TECLA ENTER (Ejecutar)
                PlaySound(TEXT("D:\\UTN FRGP\\PROG II\\Salas de Cine\\PROG2-TP1-G11\\sounds\\keySoundStrong.wav"),NULL,SND_FILENAME | SND_ASYNC );
                rlutil::cls();

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
                        rlutil::anykey();
                        break;
                    }

                    case 3: {
                        string id;
                        cout << "Ingrese ID de la sala: ";
                        getline(cin, id);
                        gestorSalas.verCapacidad(id);
                        rlutil::anykey();
                        break;
                    }

                    case 4:
                        menuGuardarSalas(guardadoAutomatico, gestorSalas);
                        rlutil::anykey();
                        break;

                    case 5: // SUBMENÚ DE FUNCIONES
                        menuFunciones(funciones, gestorSalas, gestorPeliculas);
                        break;

                    case 6:
                        guardarSalas(gestorSalas);
                        funciones.guardarFunciones("funciones.dat");
                        salir = true;
                        menuGestor();
                        break;
                }

                rlutil::cls();
                break;
            }
        }
    }
}
