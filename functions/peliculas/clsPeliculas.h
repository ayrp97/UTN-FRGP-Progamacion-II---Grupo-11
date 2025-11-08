#pragma once

#include "clsDataPeliculas.h"
#include "../../utilities/classes/clsFechas.h"
#include <string>

class clsPelicula {
private:
    clsDataPeliculas* peliculas;  // arreglo dinámico
    int cantidad;                 // películas actualmente cargadas
    int capacidad;                // tamaño actual del arreglo

    std::string generarId();      // Genera ID automático AAAAMMXXXX
    void redimensionar();         // Duplica el tamaño del arreglo si se llena

public:
    clsPelicula();
    ~clsPelicula();

    void cargarNuevaPelicula();
    void modificarPelicula(const std::string& id);
    void darDeBaja(const std::string& id);
    void darDeAlta(const std::string& id);
    void mostrarPeliculas() const;
};
