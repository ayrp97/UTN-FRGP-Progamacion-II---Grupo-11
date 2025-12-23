#pragma once
#include <iostream>
#include <string>
#include "clsdataPeliculas.h"
#include "../../utilities/classes/clsFechas.h"
#include "function_persistenciaPeliculas.h"

class clsPelicula {
private:
    clsDataPeliculas* peliculas;
    int cantidad;
    int capacidad;
    bool guardadoAutomatico;

    void redimensionar();
    std::string generarId();

public:
    clsPelicula();
    ~clsPelicula();

    void setGuardadoAutomatico(bool estado);
    bool getGuardadoAutomatico() const;

    void cargarNuevaPelicula();
    void modificarPelicula(const std::string& id);
    void darDeBaja(const std::string& id);
    void darDeAlta(const std::string& id);
    void mostrarPeliculas() const;

    int getCantidad() const;
    const clsDataPeliculas* getPeliculas() const;
    void agregarPelicula(const clsDataPeliculas& p);
    void vaciarPeliculas();
    int buscarPelicula(const std::string& id) const;
    int getDuracion(int index) const;
};



