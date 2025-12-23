#include <iostream>
#include <locale>
<<<<<<< HEAD
#include "rlutil.h"
#include "mainHeader.h"
using namespace std;

void ventas(){

    rlutil::hidecursor(); // Herramienta que oculta el cursosor
    rlutil::cls();        // Herramienta que limpia la terminal

    int corteVentas = 1;

    while (corteVentas !=0) {
        fondoVentana();



        rlutil::setColor(rlutil::GREEN);
        rlutil::locate(41,29);  cout << " <ESC> ";
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(48,29);  cout <<" Para volver al menu principal  ";

        switch(rlutil::getkey()){
            case 0:
                PlaySound(TEXT("keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                corteVentas = 0;
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

=======
#include <windows.h>
#include <string>
#include <sstream>
#include "../../rlutil.h"
#include "../../mainHeader.h"
#include "clsVentas.h"
#include "Precios/clsPrecios.h"
#include "Candy/clsCandy.h"
#include "../peliculas/clsPeliculas.h"
#include "../salas/clsSalas.h"
#include "../salas/funcion/clsFunciones.h"
#include "../peliculas/function_persistenciaPeliculas.h"
#include "../salas/function_persistenciaSalas.h"

using namespace std;

void ventas() {
    configuracionesVisuales();

    clsVentas gestorVentas;       // Modulo Principal
    clsPrecios gestorPrecios;     // Tarifas y Precios
    clsCandy gestorCandy;         // Stock de comida
    clsPelicula gestorPeliculas;
    clsSala gestorSalas;

    cargarPeliculas(gestorPeliculas);
    cargarSalas(gestorSalas);
    clsFunciones gestorFunciones(2000);
    gestorFunciones.cargarFunciones("funciones.dat");

    while (true) {
        rlutil::cls();
        fondoVentana();

        const char* opciones[] = {
            " NUEVA VENTA ",
            " HISTORIAL DE VENTAS ",
            " GESTION DE PRECIOS Y STOCK ",
            " GESTION DE CANDY ",
            " VOLVER "
        };

        int cantidad = 5;
        int op = menuInteractivo(opciones, cantidad, "MODULO DE VENTAS", 50, 20);



        if (op == -1 || op == 4) return;

        rlutil::cls();

        switch (op) {
            case 0:
                gestorVentas.realizarVenta(gestorFunciones, gestorPeliculas, gestorSalas, gestorPrecios, gestorCandy);
                break;

            case 1:
                gestorVentas.mostrarHistorialVentas();
                break;

            case 2:
                gestorPrecios.menuPrincipalPrecios();
                break;

            case 3:
                {
                    while(true) {
                        rlutil::cls();
                        fondoVentana();

                        const char* opcionesCandy[] = {
                            " AGREGAR NUEVO ARTICULO       ",
                            " VER LISTADO COMPLETO         ",
                            " CARGAR STOCK MANUALMENTE     ",
                            " ELIMINAR ARTICULO (BAJA)     ",
                            " VOLVER                       "
                        };

                        int opCandy = menuInteractivo(opcionesCandy, 5, "GESTION RAPIDA DE CANDY", 50, 20);

                        if (opCandy == -1 || opCandy == 4) break;

                        rlutil::cls();

                        switch(opCandy) {
                            case 0: gestorCandy.agregarArticulo(); break;
                            case 1: gestorCandy.mostrarListado(); rlutil::anykey(); break;
                            case 2: gestorCandy.modificarStock(); break;
                            case 3: gestorCandy.menuDarDeBaja(); break;
                        }
                    }
                }
                break;
        }
    }
>>>>>>> develop
}


