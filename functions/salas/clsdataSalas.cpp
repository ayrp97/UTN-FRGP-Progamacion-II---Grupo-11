#include "clsDataSalas.h"

clsDataSalas::clsDataSalas() {
    std::strcpy(idSala, "");
    capacidad = 0;
    activa = true;       // Por defecto activa
}

std::string clsDataSalas::getIdSala() const {
    return std::string(idSala);
}

int clsDataSalas::getCapacidad() const {
    return capacidad;
}

bool clsDataSalas::estaActiva() const {
    return activa;
}

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

std::string clsDataSalas::getTipoSala() const {
    return std::string(tipoSala);
}

void clsDataSalas::setTipoSala(const std::string& tipo) {
    std::strncpy(tipoSala, tipo.c_str(), 29);
    tipoSala[29] = '\0';
}


