#pragma once

#include "clsDataPeliculas.h"
#include <vector>

class clsPelicula {
private:
    std::vector<clsDataPeliculas> peliculas;

    // Genera ID automático (AAAA-MM-XXXX)
    std::string generarId(); /* <-- implementación de ejemplo abajo */

public:
    void cargarNuevaPelicula();
    void modificarPelicula(const std::string& id);
    void darDeBaja(const std::string& id);
    void darDeAlta(const std::string& id);

    // Mostrar lista de películas
    void mostrarPeliculas() const;
};