#include "clsArticulo.h"

clsArticulo::clsArticulo() {
    std::strcpy(sku, "");
    std::strcpy(nombre, "");
    precio = 0.0f;
    stock = 0;
    activo = true;
}

void clsArticulo::setSKU(const std::string& s) {
    std::strncpy(sku, s.c_str(), sizeof(sku) - 1);
    sku[sizeof(sku) - 1] = '\0';
}
void clsArticulo::setNombre(const std::string& n) {
    std::strncpy(nombre, n.c_str(), sizeof(nombre) - 1);
    nombre[sizeof(nombre) - 1] = '\0';
}
void clsArticulo::setPrecio(float p) { precio = p; }
void clsArticulo::setStock(int s) { stock = s; }
void clsArticulo::setActivo(bool a) { activo = a; }

// Getters
std::string clsArticulo::getSKU() const { return std::string(sku); }
std::string clsArticulo::getNombre() const { return std::string(nombre); }
float clsArticulo::getPrecio() const { return precio; }
int clsArticulo::getStock() const { return stock; }
bool clsArticulo::estaActivo() const { return activo; }