#pragma once
#include <cstring>
#include <string>

class clsDataSalas {
private:
    
    char idSala[10];
    int capacidad;
    char tipoSala[30];
    bool activa;

public:
    clsDataSalas();

    std::string getIdSala() const;
    int getCapacidad() const;
    std::string getTipoSala() const;
    bool estaActiva() const;

    void setIdSala(const std::string& id);
    void setCapacidad(int cap);
    void setTipoSala(const std::string& tipo);
    void setActiva(bool estado);
};