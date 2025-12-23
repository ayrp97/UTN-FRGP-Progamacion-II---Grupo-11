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

    void imprimirTicketEnPantalla(const clsmaestroVenta& venta, const clsPelicula& peliGestor);
    bool esFuncionFutura(const clsDataFuncion& f);

public:
    void realizarVenta(clsFunciones& gestorFunciones,
                       clsPelicula& gestorPeliculas,
                       clsSala& gestorSalas,
                       clsPrecios& gestorPrecios,
                       clsCandy& gestorCandy);

    void mostrarHistorialVentas();
};


