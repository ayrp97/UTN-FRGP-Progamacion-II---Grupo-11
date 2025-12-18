#pragma once
#include <string>
#include <cstring>

class clsdetalleVenta {
private:
    char codigo[15];
    char descripcion[40];
    int cantidad;
    float precioUnitario;

public:
    clsdetalleVenta();

    // Setters
    void setCodigo(const std::string& c);
    void setDescripcion(const std::string& d);
    void setCantidad(int c);
    void setPrecioUnitario(float p);

    // Getters
    std::string getCodigo() const;
    std::string getDescripcion() const;
    int getCantidad() const;
    float getPrecioUnitario() const;
    
    // Cálculo auxiliar
    float getSubTotal() const;
};