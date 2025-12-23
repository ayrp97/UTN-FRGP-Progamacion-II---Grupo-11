#pragma once
#include <string>
#include <cstring>
#include "../../../utilities/classes/clsFechas.h"

class clsDataFuncion {
private:
    char idFuncion[50];
    char idSala[10];
    char idPelicula[10];
    clsFecha fecha;

    int horaInicio;
    int duracionTotal;
    int capacidadSala;
    int asientosDisponibles;
    bool activa;

public:
    clsDataFuncion();

    void setIdFuncion(const std::string& id);
    void setIdSala(const std::string& id);
    void setIdPelicula(const std::string& id);
    void setFecha(const clsFecha& f);
    void setHoraInicio(int hora);
    void setDuracionPelicula(int minutos);
    void setCapacidadSala(int cap);
    void setAsientosDisponibles(int cant);

    std::string getIdFuncion() const;
    std::string getIdSala() const;
    std::string getIdPelicula() const;
    clsFecha getFecha() const;
    int getDia() const;
    int getMes() const;
    int getAnio() const;
    int getHoraInicio() const;
    int getDuracionPelicula() const;
    int getHoraFin() const;
    int getCapacidadSala() const;
    int getAsientosDisponibles() const;

    void setActiva(bool estado);
    bool estaActiva() const;
};
