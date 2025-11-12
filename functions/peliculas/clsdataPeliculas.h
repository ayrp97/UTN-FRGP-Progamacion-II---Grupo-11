#pragma once
#include "../../utilities/classes/clsFechas.h"
#include <cstring>   // para strcpy y strncpy
#include <string>

class clsDataPeliculas {
private:
    char id[10];
    char nombre[50];
    int duracion;
    char genero[30];
    char clasificacion[5];
    char director[50];
    clsFecha estreno;
    char idiomas[50];
    char formatos[50];
    bool activa;

public:
    // Constructor
    clsDataPeliculas();

    // Getters
    std::string getId() const;
    std::string getNombre() const;
    int getDuracion() const;
    std::string getGenero() const;
    std::string getClasificacion() const;
    std::string getDirector() const;
    clsFecha getFechaEstreno() const;
    std::string getIdiomas() const;
    std::string getFormatos() const;
    bool estaActiva() const;

    // Setters
    void setId(const std::string& nuevoId);
    void setNombre(const std::string& nuevoNombre);
    void setDuracion(int nuevaDuracion);
    void setGenero(const std::string& nuevoGenero);
    void setClasificacion(const std::string& nuevaClasificacion);
    void setDirector(const std::string& nuevoDirector);
    void setFechaEstreno(const clsFecha& nuevaFecha);
    void setIdiomas(const std::string& nuevosIdiomas);
    void setFormatos(const std::string& nuevosFormatos);
    void setActiva(bool estado);
};
