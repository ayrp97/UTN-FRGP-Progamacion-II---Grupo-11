#include "clsDataFuncion.h"
#include <iostream>
#include <cstring>
using namespace std;

clsDataFuncion::clsDataFuncion() {
    strcpy(idFuncion, "");
    strcpy(idSala, "");
    strcpy(idPelicula, "");

    fecha = clsFecha(1, 1, 2000);

    horaInicio = 0;
    duracionTotal = 0;
    capacidadSala = 0;
    asientosDisponibles = 0;
    activa = true;
}

void clsDataFuncion::setIdFuncion(const string& id) {
    strncpy(idFuncion, id.c_str(), sizeof(idFuncion) - 1);
    idFuncion[sizeof(idFuncion) - 1] = '\0'; // Asegurar el null terminator
}

string clsDataFuncion::getIdFuncion() const {
    return string(idFuncion);
}

void clsDataFuncion::setIdSala(const string& id) {
    strncpy(idSala, id.c_str(), sizeof(idSala) - 1);
    idSala[sizeof(idSala) - 1] = '\0';
}

void clsDataFuncion::setIdPelicula(const string& id) {
    strncpy(idPelicula, id.c_str(), sizeof(idPelicula) - 1);
    idPelicula[sizeof(idPelicula) - 1] = '\0';
}

void clsDataFuncion::setFecha(const clsFecha& f) { fecha = f; }

void clsDataFuncion::setHoraInicio(int hora) { horaInicio = hora; }

void clsDataFuncion::setCapacidadSala(int cap) {
    capacidadSala = cap;
    asientosDisponibles = cap;
}

void clsDataFuncion::setAsientosDisponibles(int cant) { asientosDisponibles = cant; }

void clsDataFuncion::setActiva(bool estado) { activa = estado; }

string clsDataFuncion::getIdSala() const { return string(idSala); }

string clsDataFuncion::getIdPelicula() const { return string(idPelicula); }

int clsDataFuncion::getDia() const { return fecha.getDia(); }

int clsDataFuncion::getMes() const { return fecha.getMes(); }

int clsDataFuncion::getAnio() const { return fecha.getAnio(); }

void clsDataFuncion::setDuracionPelicula(int min) { duracionTotal = min; }

int clsDataFuncion::getDuracionPelicula() const { return duracionTotal; }

int clsDataFuncion::getHoraFin() const {
    int h = horaInicio / 100;
    int m = horaInicio % 100;
    int totalMin = h * 60 + m + duracionTotal;
    int hFin = totalMin / 60;
    int mFin = totalMin % 60;
    return hFin * 100 + mFin;
}

int clsDataFuncion::getCapacidadSala() const { return capacidadSala; }

int clsDataFuncion::getAsientosDisponibles() const { return asientosDisponibles; }

clsFecha clsDataFuncion::getFecha() const { return fecha; }

int clsDataFuncion::getHoraInicio() const { return horaInicio; }

bool clsDataFuncion::estaActiva() const { return activa; }