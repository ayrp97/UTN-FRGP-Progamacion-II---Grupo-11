#pragma once
#include <string>
#include "clsDataFuncion.h"
#include "../../salas/clsSalas.h"
#include "../../peliculas/clsPeliculas.h"

class clsFunciones {
private:
    clsDataFuncion* funciones;
    int capacidadMax;
    int cantidad;

    int redondear10(int minutos) const;
    std::string generarIdFuncion(const std::string& idPelicula,
                                 const std::string& idSala,
                                 int horaInicio,
                                 int dia, int mes, int anio) const;

    bool verificarSolapamiento(const std::string& idSala,
                               int dia, int mes, int anio,
                               int horaInicio, int horaFin) const;

public:
    clsFunciones(int maxFunciones = 2000);
    ~clsFunciones();

    void crearFuncion(clsSala& salas, clsPelicula& peliculas);
    void crearFuncionesPorDia(clsSala& salas, clsPelicula& peliculas);
    void crearFuncionesPorMes(clsSala& salas, clsPelicula& peliculas);

    void mostrarFunciones(const clsPelicula& gestorPeliculas) const;
    void mostrarFuncionesPorSala(const std::string& idSala, const clsPelicula& gestorPeliculas) const;
    void mostrarFuncionesPorFecha(int dia, int mes, int anio, const clsPelicula& gestorPeliculas) const;

    int buscarFuncion(const std::string& id) const;
    void desactivarFuncion(const std::string& id);

    bool guardarFunciones(const char* nombreArchivo) const;
    bool cargarFunciones(const char* nombreArchivo);

    int getCantidad() const;
    const clsDataFuncion* getFunciones() const;

    bool restarCapacidad(const std::string& idFuncion, int cantidad);
};
