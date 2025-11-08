#include "clsdataPeliculas.h"
#include "../../utilities/classes/clsFechas.h"
#include <cstring>

// Constructor por defecto
clsDataPeliculas::clsDataPeliculas() {
    std::strcpy(id, "");
    std::strcpy(nombre, "");
    duracion = 0;
    std::strcpy(genero, "");
    std::strcpy(clasificacion, "");
    std::strcpy(director, "");
    idiomas = "";
    formatos = "";
    activa = false;
}




// Getters
std::string clsDataPeliculas::getId() const { 
    return std::string(id); 
}
std::string clsDataPeliculas::getNombre() const { 
    return std::string(nombre); 
}
int clsDataPeliculas::getDuracion() const { 
    return duracion; 
}
std::string clsDataPeliculas::getGenero() const { 
    return std::string(genero); 
}
std::string clsDataPeliculas::getClasificacion() const { 
    return std::string(clasificacion); 
}
std::string clsDataPeliculas::getDirector() const { 
    return std::string(director); 
}
clsFecha clsDataPeliculas::getFechaEstreno() const {
    return estreno;
}
std::string clsDataPeliculas::getIdiomas() const { 
    return idiomas; 
}
std::string clsDataPeliculas::getFormatos() const { 
    return formatos; 
}
bool clsDataPeliculas::estaActiva() const { 
    return activa; 
}




// Setters
void clsDataPeliculas::setId(const std::string& nuevoId) { 
    std::strncpy(id, nuevoId.c_str(), 10); id[10] = '\0'; 
}
void clsDataPeliculas::setNombre(const std::string& nuevoNombre) { 
    std::strncpy(nombre, nuevoNombre.c_str(), 49); nombre[49] = '\0'; 
}
void clsDataPeliculas::setDuracion(int nuevaDuracion) { 
    duracion = nuevaDuracion; 
}
void clsDataPeliculas::setGenero(const std::string& nuevoGenero) { 
    std::strncpy(genero, nuevoGenero.c_str(), 29); genero[29] = '\0'; 
}
void clsDataPeliculas::setClasificacion(const std::string& nuevaClasificacion) { 
    std::strncpy(clasificacion, nuevaClasificacion.c_str(), 3); clasificacion[3] = '\0';
 }
void clsDataPeliculas::setDirector(const std::string& nuevoDirector) { 
    std::strncpy(director, nuevoDirector.c_str(), 49); director[49] = '\0'; 
}
void clsDataPeliculas::setFechaEstreno(const clsFecha& nuevaFecha) {
    estreno = nuevaFecha;
}
void clsDataPeliculas::setIdiomas(const std::string& nuevosIdiomas) { 
    idiomas = nuevosIdiomas; 
}
void clsDataPeliculas::setFormatos(const std::string& nuevosFormatos) { 
    formatos = nuevosFormatos; 
}
void clsDataPeliculas::setActiva(bool estado) { 
    activa = estado; 
}
