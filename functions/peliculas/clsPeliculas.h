#pragma once
#include <iostream>
#include <string>
#include "clsdataPeliculas.h"
#include "../../utilities/classes/clsFechas.h"
#include "function_persistenciaPeliculas.h"

class clsPelicula {
private:
    clsDataPeliculas* peliculas;   // arreglo dinámico
    int cantidad;                  // cantidad actual de películas
    int capacidad;                 // tamaño máximo actual del arreglo
    bool guardadoAutomatico;       // 🔹 bandera de guardado automático

    void redimensionar();
    std::string generarId();

public:
    // Constructor y Destructor
    clsPelicula();
    ~clsPelicula();

    // Control del guardado automático
    void setGuardadoAutomatico(bool estado);
    bool getGuardadoAutomatico() const;

    // Métodos principales
    void cargarNuevaPelicula();
    void modificarPelicula(const std::string& id);
    void darDeBaja(const std::string& id);
    void darDeAlta(const std::string& id);
    void mostrarPeliculas() const;

    // Métodos auxiliares para persistencia
    int getCantidad() const;
    const clsDataPeliculas* getPeliculas() const;
    void agregarPelicula(const clsDataPeliculas& p);
    void vaciarPeliculas();
    int buscarPelicula(const std::string& id) const;
    int getDuracion(int index) const;
};
