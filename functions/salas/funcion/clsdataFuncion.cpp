#include "clsDataFuncion.h"
#include <iostream>
#include <cstring> // Importante
using namespace std;

clsDataFuncion::clsDataFuncion() {
    // Inicializar los char arrays vacíos
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

// =================== ID Funcion ===================
void clsDataFuncion::setIdFuncion(const string& id) {
    strncpy(idFuncion, id.c_str(), sizeof(idFuncion) - 1);
    idFuncion[sizeof(idFuncion) - 1] = '\0'; // Asegurar el null terminator
}

string clsDataFuncion::getIdFuncion() const {
    return string(idFuncion);
}

// =================== IDs externos ===================
void clsDataFuncion::setIdSala(const string& id) {
    strncpy(idSala, id.c_str(), sizeof(idSala) - 1);
    idSala[sizeof(idSala) - 1] = '\0';
}

void clsDataFuncion::setIdPelicula(const string& id) {
    strncpy(idPelicula, id.c_str(), sizeof(idPelicula) - 1);
    idPelicula[sizeof(idPelicula) - 1] = '\0';
}

string clsDataFuncion::getIdSala() const { return string(idSala); }
string clsDataFuncion::getIdPelicula() const { return string(idPelicula); }

// ... EL RESTO DEL ARCHIVO SIGUE IGUAL ...
// (Copia el resto de los getters/setters de fecha, hora, capacidad que ya tenías, esos no cambian)
// =================== FECHA ===================
void clsDataFuncion::setFecha(const clsFecha& f) { fecha = f; }
clsFecha clsDataFuncion::getFecha() const { return fecha; }
int clsDataFuncion::getDia() const { return fecha.getDia(); }
int clsDataFuncion::getMes() const { return fecha.getMes(); }
int clsDataFuncion::getAnio() const { return fecha.getAnio(); }

// =================== HORARIOS ===================
void clsDataFuncion::setHoraInicio(int hora) { horaInicio = hora; }
int clsDataFuncion::getHoraInicio() const { return horaInicio; }
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

// =================== SALA ===================
void clsDataFuncion::setCapacidadSala(int cap) {
    capacidadSala = cap;
    asientosDisponibles = cap;
}
int clsDataFuncion::getCapacidadSala() const { return capacidadSala; }
void clsDataFuncion::setAsientosDisponibles(int cant) { asientosDisponibles = cant; }
int clsDataFuncion::getAsientosDisponibles() const { return asientosDisponibles; }

// =================== ESTADO ===================
void clsDataFuncion::setActiva(bool estado) { activa = estado; }
bool clsDataFuncion::estaActiva() const { return activa; }