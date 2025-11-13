#pragma once
#include <string>
#include "clsDataSalas.h"

class clsSala {
private:
    clsDataSalas* salas;   // Array dinámico de salas
    int cantidad;          // Cantidad actual de salas cargadas
    int capacidadMax;      // Máximo 15 salas por cine

public:
    // Constructor y Destructor
    clsSala();
    ~clsSala();

    // Generador automático de ID: SA0001, SA0002...
    std::string generarIdSala();

    // Métodos principales
    void crearSala();                         // Crea una sala nueva y asigna capacidad según tipo
    void modificarSala(const std::string& idSala);
    void verCapacidad(const std::string& idSala) const;

    // Asignación / desasignación de películas (próximamente conectado con clsDataFuncion)
    void asignarPelicula(const std::string& idSala, const std::string& idPelicula);
    void desasignarPelicula(const std::string& idSala);

    // Mostrar todas las salas cargadas
    void mostrarSalas() const;

    // Métodos auxiliares
    int buscarSala(const std::string& idSala) const;
    int getCantidad() const;
    const clsDataSalas* getSalas() const;

    //Correcion de bug

    void vaciarSalas();
    void agregarSala(const clsDataSalas& sala);

};
