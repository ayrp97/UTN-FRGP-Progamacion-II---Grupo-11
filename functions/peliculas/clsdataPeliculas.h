#pragma once
#include "../../utilities/classes/clsFechas.h"
#include <string>

class clsDataPeliculas {
private:
    char id[11];           // AAAA-MM-XXXX
    char nombre[50];
    int duracion;          // en minutos
    char genero[30];
    char clasificacion[4]; // ATP, +16, +18
    char director[50];
    clsFecha estreno;      // Fecha de estreno
    std::string idiomas;   // Español, Ingles subtitulado, Original subtitulado
    std::string formatos;  // 2D, 3D, 4D
    bool activa;

public:
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