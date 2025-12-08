#include <iostream>
#include <locale>
#include <string>
#include <windows.h>
#include "rlutil.h"
#include "mainHeader.h"
#include "utilities/classes/clsReportes.h"

using namespace std;

void menuGestor(){
    configuracionesVisuales();
    int corteMenu  = 1;    //Se declara y se asigna un valor a la variable de corte del Do While que contendra todo el menu del programa
    int  y = 0;            //Se declara y se asigna valor a la variable Y para ser usada en el switch para poder moverse verticalmente en el menu

    while (corteMenu !=0){
        rlutil::cls();
        fondoVentana();    //Funcion que configura el marco blanco de la consola
        dibujoMenu();      //Funcion que dibuja los pochoclos y el simbolo de cine

        const char* opciones[] = {
        " MODULO DE PELICULAS ",
        " MODULO DE SALAS ",
        " MODULO DE VENTAS ",
        " REPORTES E INFORMES ",
        " MODULO DE CREDITOS ",
        " SALIR DEL SISTEMA "
        };

        int cantidadOpciones = 6;

        int op = menuInteractivo(opciones, cantidadOpciones, "   CINEMA PARADISSO",50, 20);

        switch (op) {
        case 0: peliculas(); break;
        case 1: salas(); break;
        case 2: ventas(); break;
        case 3:
                {
                    clsReportes reporte;
                    reporte.menuPrincipalReportes();
                }
                break;
        case 4: creditos(); break;
        case 5:
            salir();
            corteMenu = 0;
            break;
        }

    }
}
