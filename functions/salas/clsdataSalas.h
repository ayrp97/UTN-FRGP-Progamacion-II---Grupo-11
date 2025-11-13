#pragma once
#include <cstring>
#include <string>

class clsDataSalas {
private:
    char idSala[10];     // Ej.: "SALA01", "SALA12"
    int capacidad;       // Cantidad de butacas
    bool activa;         // true = activa, false = inactiva

public:
    // Constructor
    clsDataSalas();

    // Getters
    std::string getIdSala() const;
    int getCapacidad() const;
    bool estaActiva() const;

    // Setters
    void setIdSala(const std::string& id);
    void setCapacidad(int cap);
    void setActiva(bool estado);
};