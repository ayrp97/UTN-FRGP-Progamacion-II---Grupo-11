#pragma once
#include "clsmaestroVentas.h"
#include "../peliculas/clsPeliculas.h"
#include "../salas/clsSalas.h"
#include "../salas/funcion/clsFunciones.h"
#include "Candy/clsCandy.h"
#include "Precios/clsPrecios.h"
#include <string>

const std::string ARCHIVO_VENTAS = "ventas.dat";
const std::string ARCHIVO_ID_VENTAS = "contador_ventas.txt";

class clsVentas {
private:
    std::string generarIdVenta();

    // Función visual para simular la impresión
    void imprimirTicketEnPantalla(const clsmaestroVenta& venta, const clsPelicula& peliGestor);

    // Validación de horario (lo que hablamos antes)
    bool esFuncionFutura(const clsDataFuncion& f);

public:
    // EL MÉTODO PRINCIPAL
    // Recibe referencias a TODOS los gestores porque necesita leer y modificar sus datos
    void realizarVenta(clsFunciones& gestorFunciones,
                       clsPelicula& gestorPeliculas,
                       clsSala& gestorSalas,
                       clsPrecios& gestorPrecios,
                       clsCandy& gestorCandy);

    void mostrarHistorialVentas();
};
