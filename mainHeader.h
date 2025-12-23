#ifndef MAINHEADER_H_INCLUDED
#define MAINHEADER_H_INCLUDED
#include <string>
// GUARDS (DEBEN ESTAR PARA QUE EL PROCESO DE COMPILACI�N SEA EXITOSO)
// AQUI SE DECLARAN LAS FUNCIONES

// CAPAS PRINCIPALES

void menuGestor();
void peliculas();
void salas();
void ventas();
void creditos();
void salir();
void corteTotal();

// FONDO
void fondoVentana();
void dibujoMenu();
void mostrarItem(const char* text, int x, int y, bool selected);
int menuInteractivo(const char* opciones[], int cantidad, const char* titulo, int x, int yBase);
void configuracionesVisuales();
#endif //MAINHEADER_H_INCLUDED
