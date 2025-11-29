#pragma once
#include <string>
#include <cstring>

class clsArticulo {
private:
    char sku[8];            // SKU0001 (7 chars + \0)
    char nombre[30];        // "Pochoclo Grande"
    float precio;           // $
    int stock;              // Cantidad disponible
    bool activo;            // Eliminado lógico

public:
    clsArticulo();

    // Setters
    void setSKU(const std::string& s);
    void setNombre(const std::string& n);
    void setPrecio(float p);
    void setStock(int s);
    void setActivo(bool a);

    // Getters
    std::string getSKU() const;
    std::string getNombre() const;
    float getPrecio() const;
    int getStock() const;
    bool estaActivo() const;
};