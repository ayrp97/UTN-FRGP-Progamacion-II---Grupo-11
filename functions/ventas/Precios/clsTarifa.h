#pragma once
#include <string>
#include <cstring>

class clsTarifa {
private:
    char codigo[10];        // Ej: "ENT2DBA"
    char descripcion[40];   // Ej: "BASIC 2D" (Debe coincidir con clsSalas)
    float precio;           // $5000

public:
    clsTarifa() {
        std::strcpy(codigo, "");
        std::strcpy(descripcion, "");
        precio = 0.0f;
    }

    void setCodigo(const std::string& c) {
        std::strncpy(codigo, c.c_str(), 9); codigo[9] = '\0';
    }
    void setDescripcion(const std::string& d) {
        std::strncpy(descripcion, d.c_str(), 39); descripcion[39] = '\0';
    }
    void setPrecio(float p) { precio = p; }

    std::string getCodigo() const { return std::string(codigo); }
    std::string getDescripcion() const { return std::string(descripcion); }
    float getPrecio() const { return precio; }
};