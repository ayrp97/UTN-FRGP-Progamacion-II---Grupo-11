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

void menuFunciones(clsFunciones& funciones, clsSala& gestorSalas, clsPelicula& gestorPeliculas) {
    while (true) {
        rlutil::cls();
        fondoVentana();

        const char* opciones[] = {
            " CREAR FUNCION UNICA ",
            " CREAR FUNCIONES POR DIA ",
            " CREAR FUNCIONES POR MES ",
            " MOSTRAR TODAS ",
            " FUNCIONES POR SALA ",
            " FUNCIONES POR FECHA ",
            " DESACTIVAR FUNCION ",
            " VOLVER "
        };

        int cantidad = 8;

        int op = menuInteractivo(opciones, cantidad, "SUB MODULO DE FUNCIONES", 50, 20);

        if (op == -1 || op == 7) return;

        rlutil::cls();

        switch (op) {
            case 0:
                funciones.crearFuncion(gestorSalas, gestorPeliculas);
                funciones.guardarFunciones("funciones.dat");
                rlutil::anykey();
                break;

            case 1:
                funciones.crearFuncionesPorDia(gestorSalas, gestorPeliculas);
                funciones.guardarFunciones("funciones.dat");
                rlutil::anykey();
                break;

            case 2:
                funciones.crearFuncionesPorMes(gestorSalas, gestorPeliculas);
                funciones.guardarFunciones("funciones.dat");
                rlutil::anykey();
                break;

            case 3:
                funciones.mostrarFunciones(gestorPeliculas);
                rlutil::anykey();
                break;

            case 4:
                {
                    fondoVentana();
                    rlutil::setColor(rlutil::YELLOW);
                    rlutil::locate(45, 10); cout << "BUSCAR FUNCIONES POR SALA";

                    rlutil::setColor(rlutil::WHITE);
                    rlutil::locate(40, 12); cout << "Ingrese ID de la sala: ";

                    rlutil::showcursor();
                    string idSala;
                    getline(cin, idSala);
                    rlutil::hidecursor();

                    rlutil::cls();
                    funciones.mostrarFuncionesPorSala(idSala, gestorPeliculas);
                    rlutil::anykey();
                }
                break;

            case 5:
                {
                    fondoVentana();
                    rlutil::setColor(rlutil::YELLOW);
                    rlutil::locate(45, 10); cout << "BUSCAR FUNCIONES POR FECHA";

                    int d, m, a;
                    rlutil::setColor(rlutil::WHITE);
                    rlutil::showcursor();

                    rlutil::locate(40, 12); cout << "Ingrese dia: "; cin >> d;
                    rlutil::locate(40, 13); cout << "Ingrese mes: "; cin >> m;
                    rlutil::locate(40, 14); cout << "Ingrese anio: "; cin >> a;
                    cin.ignore();
                    rlutil::hidecursor();

                    rlutil::cls();
                    funciones.mostrarFuncionesPorFecha(d, m, a, gestorPeliculas);
                    rlutil::anykey();
                }
                break;

            case 6:
                {
                    fondoVentana();
                    rlutil::setColor(rlutil::RED);
                    rlutil::locate(45, 10); cout << "DESACTIVAR FUNCION";

                    rlutil::setColor(rlutil::WHITE);
                    rlutil::locate(40, 12); cout << "Ingrese ID de funcion: ";

                    rlutil::showcursor();
                    string id;
                    getline(cin, id);
                    rlutil::hidecursor();

                    int pos = funciones.buscarFuncion(id);

                    rlutil::locate(40, 14);
                    if (pos == -1) {
                        rlutil::setColor(rlutil::RED);
                        cout << "No se encontro la funcion con ese ID.";
                    } else {
                        funciones.desactivarFuncion(id);
                        funciones.guardarFunciones("funciones.dat");
                        rlutil::setColor(rlutil::GREEN);
                        cout << "Funcion desactivada correctamente.";
                    }
                    rlutil::anykey();
                }
                break;
        }
    }
}

void salas() {
    configuracionesVisuales();

    clsSala gestorSalas;
    clsPelicula gestorPeliculas;
    clsFunciones funciones(2000);

    bool guardadoAutomatico = true;

    cargarSalas(gestorSalas);
    cargarPeliculas(gestorPeliculas);
    funciones.cargarFunciones("funciones.dat");

    while (true) {
        rlutil::cls();
        fondoVentana();

        const char* opciones[] = {
            " CREAR NUEVA SALA ",
            " MOSTRAR TODAS ",
            " MODIFICAR SALA ",
            " VER CAPACIDAD DE SALA ",
            " CONFIGURACION DE GUARDADO ",
            " GESTIONAR FUNCIONES ",
            " VOLVER "
        };

        int cantidad = 7;

        int op = menuInteractivo(opciones, cantidad, "MODULO DE SALAS", 50, 20);

        if (op == -1 || op == 6) {
            guardarSalas(gestorSalas);
            funciones.guardarFunciones("funciones.dat");
            break;
        }

        rlutil::cls();

        switch (op) {
            case 0:
                gestorSalas.crearSala();
                if (guardadoAutomatico) guardarSalas(gestorSalas);
                rlutil::anykey();
                break;

            case 1:
                gestorSalas.mostrarSalas();
                rlutil::anykey();
                break;

            case 2:
                {
                    fondoVentana();
                    rlutil::setColor(rlutil::YELLOW);
                    rlutil::locate(45, 10); cout << "MODIFICAR SALA";

                    rlutil::setColor(rlutil::WHITE);
                    rlutil::locate(40, 12); cout << "Ingrese ID de la sala: ";

                    rlutil::showcursor();
                    string id;
                    getline(cin, id);
                    rlutil::hidecursor();

                    if (!id.empty()) {
                        gestorSalas.modificarSala(id);
                        if (guardadoAutomatico) guardarSalas(gestorSalas);
                    }
                    rlutil::anykey();
                }
                break;

            case 3:
                {
                    fondoVentana();
                    rlutil::setColor(rlutil::YELLOW);
                    rlutil::locate(45, 10); cout << "CONSULTAR CAPACIDAD";

                    rlutil::setColor(rlutil::WHITE);
                    rlutil::locate(40, 12); cout << "Ingrese ID de la sala: ";

                    rlutil::showcursor();
                    string id;
                    getline(cin, id);
                    rlutil::hidecursor();

                    rlutil::cls();
                    gestorSalas.verCapacidad(id);
                    rlutil::anykey();
                }
                break;

            case 4:
                menuGuardarSalas(guardadoAutomatico, gestorSalas);
                break;

            case 5:
                menuFunciones(funciones, gestorSalas, gestorPeliculas);
                break;
        }
    }
}
