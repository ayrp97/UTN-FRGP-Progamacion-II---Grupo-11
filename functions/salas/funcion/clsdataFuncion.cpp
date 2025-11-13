#include "clsDataFuncion.h"
#include <iostream>
using namespace std;

clsDataFuncion::clsDataFuncion() {
    idFuncion = "";
    idSala = "";
    idPelicula = "";

    fecha = clsFecha(1, 1, 2000);   // <-- clsFecha, no clsFechas

    horaInicio = 0;
    duracionTotal = 0;
    capacidadSala = 0;
    asientosDisponibles = 0;
    activa = true;
}

// =================== ID ===================
void clsDataFuncion::setIdFuncion(const string& id) { idFuncion = id; }
string clsDataFuncion::getIdFuncion() const { return idFuncion; }

// =================== IDs externos ===================
void clsDataFuncion::setIdSala(const string& id) { idSala = id; }
void clsDataFuncion::setIdPelicula(const string& id) { idPelicula = id; }

string clsDataFuncion::getIdSala() const { return idSala; }
string clsDataFuncion::getIdPelicula() const { return idPelicula; }

// =================== FECHA ===================
void clsDataFuncion::setFecha(const clsFecha& f) {
    fecha = f;
}

clsFecha clsDataFuncion::getFecha() const {
    return fecha;
}

int clsDataFuncion::getDia() const { return fecha.getDia(); }
int clsDataFuncion::getMes() const { return fecha.getMes(); }
int clsDataFuncion::getAnio() const { return fecha.getAnio(); }

// =================== HORARIOS ===================
void clsDataFuncion::setHoraInicio(int hora) {
    horaInicio = hora;
}

int clsDataFuncion::getHoraInicio() const {
    return horaInicio;
}

void clsDataFuncion::setDuracionPelicula(int min) {
    duracionTotal = min;
}

int clsDataFuncion::getDuracionPelicula() const {
    return duracionTotal;
}

int clsDataFuncion::getHoraFin() const {
    int h = horaInicio / 100;
    int m = horaInicio % 100;

    int totalMin = h * 60 + m + duracionTotal;

    int hFin = totalMin / 60;
    int mFin = totalMin % 60;

    return hFin * 100 + mFin;
}

// =================== SALA ===================
void clsDataFuncion::setCapacidadSala(int cap) {
    capacidadSala = cap;
    asientosDisponibles = cap;
}

int clsDataFuncion::getCapacidadSala() const { return capacidadSala; }

void clsDataFuncion::setAsientosDisponibles(int cant) {
    asientosDisponibles = cant;
}

int clsDataFuncion::getAsientosDisponibles() const {
    return asientosDisponibles;
}

// =================== ESTADO ===================
void clsDataFuncion::setActiva(bool estado) {
    activa = estado;
}

bool clsDataFuncion::estaActiva() const {
    return activa;
}