#include "clsDataSalas.h"

// ------------------------------------------------------
// CONSTRUCTOR
// ------------------------------------------------------
clsDataSalas::clsDataSalas() {
    std::strcpy(idSala, "");
    capacidad = 0;
    activa = true;       // Por defecto activa
}

// ------------------------------------------------------
// GETTERS
// ------------------------------------------------------
std::string clsDataSalas::getIdSala() const {
    return std::string(idSala);
}

int clsDataSalas::getCapacidad() const {
    return capacidad;
}

bool clsDataSalas::estaActiva() const {
    return activa;
}

// ------------------------------------------------------
// SETTERS
// ------------------------------------------------------
void clsDataSalas::setIdSala(const std::string& id) {
    std::strncpy(idSala, id.c_str(), sizeof(idSala) - 1);
    idSala[sizeof(idSala) - 1] = '\0';
}

void clsDataSalas::setCapacidad(int cap) {
    capacidad = cap;
}

void clsDataSalas::setActiva(bool estado) {
    activa = estado;
}




