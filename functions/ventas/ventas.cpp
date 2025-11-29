#include <iostream>
#include <locale>
#include <windows.h>
#include "../../rlutil.h"
#include "../../mainHeader.h"

// INCLUDES DE TODAS LAS DEPENDENCIAS
#include "clsVentas.h"
#include "Precios/clsPrecios.h"
#include "Candy/clsCandy.h"
#include "../peliculas/clsPeliculas.h"
#include "../salas/clsSalas.h"
#include "../salas/funcion/clsFunciones.h"

// INCLUDES DE PERSISTENCIA (Para cargar los datos al inicio)
#include "../peliculas/function_persistenciaPeliculas.h"
#include "../salas/function_persistenciaSalas.h"

using namespace std;

// --------------------------------------------------------------------
// HELPER VISUAL (Copia exacta del estilo usado en Salas y Peliculas)
// --------------------------------------------------------------------
void mostrarItemVentas(const char* text, int posx, int posy, bool selected) {
    if (selected) {
        rlutil::setBackgroundColor(rlutil::BLUE);
        rlutil::locate(posx - 2, posy); // Un pequeño margen visual
        cout << " " << text << " " << endl;
    } else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::locate(posx - 2, posy);
        cout << " " << text << " " << endl;
    }
    rlutil::setBackgroundColor(rlutil::BLACK);
}

// --------------------------------------------------------------------
// MENU PRINCIPAL DE VENTAS
// --------------------------------------------------------------------
void ventas() {
    rlutil::hidecursor();
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);

    // ========================================================
    // 1. INSTANCIACIÓN DE GESTORES
    // ========================================================
    // Necesitamos levantar TODO el sistema para poder vender

    clsVentas gestorVentas;       // El orquestador
    clsPrecios gestorPrecios;     // Tarifas y Precios
    clsCandy gestorCandy;         // Stock de comida

    // Gestores de datos principales (requieren carga de disco)
    clsPelicula gestorPeliculas;
    cargarPeliculas(gestorPeliculas);

    clsSala gestorSalas;
    cargarSalas(gestorSalas);

    clsFunciones gestorFunciones(2000); // 2000 funciones max
    gestorFunciones.cargarFunciones("funciones.dat");

    // ========================================================
    // 2. BUCLE DEL MENÚ
    // ========================================================
    int opcion = 0;
    bool salir = false;

    while (!salir) {
        fondoVentana(); // Tu marco estándar

        // Título del Módulo
        rlutil::setColor(rlutil::YELLOW);
        rlutil::locate(48, 10);
        cout << "MODULO DE VENTAS Y CAJA";

        rlutil::setColor(rlutil::WHITE);

        // --- OPCIONES DEL MENÚ ---
        // Coordenadas ajustadas para que quede centrado
        mostrarItemVentas(" NUEVA VENTA (TICKET)       ", 45, 14, opcion == 0);
        mostrarItemVentas(" HISTORIAL DE VENTAS        ", 45, 15, opcion == 1);
        mostrarItemVentas(" GESTION DE PRECIOS Y STOCK ", 45, 16, opcion == 2);
        mostrarItemVentas(" GESTION DE CANDY (ABM)     ", 45, 17, opcion == 3);
        mostrarItemVentas(" VOLVER AL MENU PRINCIPAL   ", 45, 19, opcion == 4);

        // --- PUNTERO VISUAL (Flecha) ---
        rlutil::locate(41, 14 + opcion + (opcion == 4 ? 1 : 0));
        cout << (char)175;

        // --- NAVEGACIÓN ---
        int key = rlutil::getkey();

        switch (key) {
            case 14: // ARRIBA
                PlaySound(TEXT("sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                opcion--;
                if (opcion < 0) opcion = 4;
                break;

            case 15: // ABAJO
                PlaySound(TEXT("sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                opcion++;
                if (opcion > 4) opcion = 0;
                break;

            case 1: // ENTER
                PlaySound(TEXT("sounds/keySoundStrong.wav"), NULL, SND_FILENAME | SND_ASYNC);

                // Limpiamos pantalla para entrar a la sub-sección
                rlutil::cls();

                switch (opcion) {
                    case 0: // REALIZAR VENTA
                        // Aquí ocurre la magia: Pasamos TODOS los gestores al método
                        gestorVentas.realizarVenta(gestorFunciones, gestorPeliculas, gestorSalas, gestorPrecios, gestorCandy);
                        break;

                    case 1: // HISTORIAL
                        gestorVentas.mostrarHistorialVentas();
                        break;

                    case 2: // PRECIOS (Entradas y acceso a precios de Candy)
                        gestorPrecios.menuPrincipalPrecios();
                        break;

                    case 3: // ABM CANDY (Agregar productos, stock manual)
                        {
                            bool volverCandy = false;
                            while(!volverCandy){
                                rlutil::cls();
                                cout << "--- GESTION RAPIDA DE CANDY ---\n";
                                cout << "1. Agregar Nuevo Articulo\n";
                                cout << "2. Ver Listado Completo\n";
                                cout << "3. Cargar Stock Manualmente\n";
                                cout << "0. Volver\n";
                                int opc; cin >> opc;
                                switch(opc){
                                    case 1: gestorCandy.agregarArticulo(); break;
                                    case 2: gestorCandy.mostrarListado(); rlutil::anykey(); break;
                                    case 3: gestorCandy.modificarStock(); break;
                                    case 0: volverCandy = true; break;
                                }
                            }
                        }
                        break;

                    case 4: // SALIR
                        salir = true;
                        // Opcional: Volver a menú principal llamando a menuGestor()
                        // o simplemente break para que el main lo maneje.
                        break;
                }

                // Al volver de cualquier opción, limpiamos y redibujamos
                rlutil::cls();
                break;
        }
    }
}


