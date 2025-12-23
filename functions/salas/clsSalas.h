#pragma once
#include <string>
#include "clsDataSalas.h"

class clsSala {
private:
    clsDataSalas* salas;   
    int cantidad;
    int capacidadMax;
public:
    clsSala();
    ~clsSala();

    std::string generarIdSala();

    void crearSala();
    void modificarSala(const std::string& idSala);
    void verCapacidad(const std::string& idSala) const;

    void asignarPelicula(const std::string& idSala, const std::string& idPelicula);
    void desasignarPelicula(const std::string& idSala);

    void mostrarSalas() const;

    int buscarSala(const std::string& idSala) const;
    int getCantidad() const;
    const clsDataSalas* getSalas() const;

    void vaciarSalas();
    void agregarSala(const clsDataSalas& sala);

};
