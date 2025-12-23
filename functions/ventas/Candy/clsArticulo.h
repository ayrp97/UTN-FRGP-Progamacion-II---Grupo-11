#pragma once
#include <string>
#include <cstring>

class clsArticulo {
private:
    char sku[8];
    char nombre[30];
    float precio;
    int stock;
    bool activo;

public:
    clsArticulo();

    void setSKU(const std::string& s);
    void setNombre(const std::string& n);
    void setPrecio(float p);
    void setStock(int s);
    void setActivo(bool a);

    std::string getSKU() const;
    std::string getNombre() const;
    float getPrecio() const;
    int getStock() const;
    bool estaActivo() const;
};