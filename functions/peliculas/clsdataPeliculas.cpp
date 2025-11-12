#include "clsDataPeliculas.h"

// Constructor
clsDataPeliculas::clsDataPeliculas() {
    std::strcpy(id, "");
    std::strcpy(nombre, "");
    duracion = 0;
    std::strcpy(genero, "");
    std::strcpy(clasificacion, "");
    std::strcpy(director, "");
    std::strcpy(idiomas, "");
    std::strcpy(formatos, "");
    activa = false;
}

// ====================== GETTERS ======================
std::string clsDataPeliculas::getId() const { return std::string(id); }
std::string clsDataPeliculas::getNombre() const { return std::string(nombre); }
int clsDataPeliculas::getDuracion() const { return duracion; }
std::string clsDataPeliculas::getGenero() const { return std::string(genero); }
std::string clsDataPeliculas::getClasificacion() const { return std::string(clasificacion); }
std::string clsDataPeliculas::getDirector() const { return std::string(director); }
clsFecha clsDataPeliculas::getFechaEstreno() const { return estreno; }
std::string clsDataPeliculas::getIdiomas() const { return std::string(idiomas); }
std::string clsDataPeliculas::getFormatos() const { return std::string(formatos); }
bool clsDataPeliculas::estaActiva() const { return activa; }

// ====================== SETTERS ======================
void clsDataPeliculas::setId(const std::string& nuevoId) {
    std::strncpy(id, nuevoId.c_str(), sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';
}
void clsDataPeliculas::setNombre(const std::string& nuevoNombre) {
    std::strncpy(nombre, nuevoNombre.c_str(), sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';
}
void clsDataPeliculas::setDuracion(int nuevaDuracion) { duracion = nuevaDuracion; }
void clsDataPeliculas::setGenero(const std::string& nuevoGenero) {
    std::strncpy(genero, nuevoGenero.c_str(), sizeof(genero) - 1);
    genero[sizeof(genero) - 1] = '\0';
}
void clsDataPeliculas::setClasificacion(const std::string& nuevaClasificacion) {
    std::strncpy(clasificacion, nuevaClasificacion.c_str(), sizeof(clasificacion) - 1);
    clasificacion[sizeof(clasificacion) - 1] = '\0';
}
void clsDataPeliculas::setDirector(const std::string& nuevoDirector) {
    std::strncpy(director, nuevoDirector.c_str(), sizeof(director) - 1);
    director[sizeof(director) - 1] = '\0';
}
void clsDataPeliculas::setFechaEstreno(const clsFecha& nuevaFecha) { estreno = nuevaFecha; }
void clsDataPeliculas::setIdiomas(const std::string& nuevosIdiomas) {
    std::strncpy(idiomas, nuevosIdiomas.c_str(), sizeof(idiomas) - 1);
    idiomas[sizeof(idiomas) - 1] = '\0';
}
void clsDataPeliculas::setFormatos(const std::string& nuevosFormatos) {
    std::strncpy(formatos, nuevosFormatos.c_str(), sizeof(formatos) - 1);
    formatos[sizeof(formatos) - 1] = '\0';
}
void clsDataPeliculas::setActiva(bool estado) { activa = estado; }
