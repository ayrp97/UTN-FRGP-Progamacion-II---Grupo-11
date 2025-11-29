#pragma once
#include <string>
#include <cstring>

class clsdetalleVenta {
private:
    char codigo[15];      // "SKU0001" o "ENT2DBA"
    char descripcion[40]; // "Pochoclos Grandes"
    int cantidad;         // 2
    float precioUnitario; // $5000

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