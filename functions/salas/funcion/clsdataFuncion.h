#pragma once
#include <string>
#include <cstring> // Necesario para strcpy, strncpy
#include "../../../utilities/classes/clsFechas.h"

class clsDataFuncion {
private:
    char idFuncion[50];  // Cambiado de string a char[]
    char idSala[10];     // Cambiado de string a char[]
    char idPelicula[10]; // Cambiado de string a char[]

    clsFecha fecha;

    int horaInicio;
    int duracionTotal;
    int capacidadSala;
    int asientosDisponibles;
    bool activa;

public:
    clsDataFuncion();

    // IDs
    void setIdFuncion(const std::string& id);
    std::string getIdFuncion() const;

    void setIdSala(const std::string& id);
    void setIdPelicula(const std::string& id);

    std::string getIdSala() const;
    std::string getIdPelicula() const;

    // Fecha
    void setFecha(const clsFecha& f);
    clsFecha getFecha() const;

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // Horarios
    void setHoraInicio(int hora);
    int getHoraInicio() const;

    void setDuracionPelicula(int minutos);
    int getDuracionPelicula() const;

    int getHoraFin() const;

    // Sala / Asientos
    void setCapacidadSala(int cap);
    int getCapacidadSala() const;

    void setAsientosDisponibles(int cant);
    int getAsientosDisponibles() const;

    // Estado
    void setActiva(bool estado);
    bool estaActiva() const;
};