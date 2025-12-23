#pragma once
#include <string>
#include "clsdetalleVentas.h"
#include "../../utilities/classes/clsFechas.h"

class clsmaestroVenta {
private:
    char idVenta[10];  
    int dniCliente;
    char idFuncion[50];
    clsFecha fecha;
    int hora;
    clsdetalleVenta detalles[20]; 
    int cantidadDetalles;
    
    float importeTotal;    
    bool activa;

public:
    clsmaestroVenta();

    void setIdVenta(const std::string& id);
    void setDniCliente(int dni);
    void setFecha(const clsFecha& f);
    void setHora(int h);
    void setActiva(bool a);
    void setIdFuncion(const std::string& id);

    std::string getIdVenta() const;
    int getDniCliente() const;
    clsFecha getFecha() const;
    int getHora() const;
    float getImporteTotal() const;
    bool estaActiva() const;
    std::string getIdFuncion() const;

    bool agregarDetalle(const clsdetalleVenta& item);
    
    int getCantidadDetalles() const;
    
    clsdetalleVenta leerDetalle(int indice) const;
};

