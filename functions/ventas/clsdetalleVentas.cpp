#include "clsdetalleVentas.h"

clsdetalleVenta::clsdetalleVenta() {
    std::strcpy(codigo, "");
    std::strcpy(descripcion, "");
    cantidad = 0;
    precioUnitario = 0.0f;
}

void clsdetalleVenta::setCodigo(const std::string& c) {
    std::strncpy(codigo, c.c_str(), 14); codigo[14] = '\0';
}
void clsdetalleVenta::setDescripcion(const std::string& d) {
    std::strncpy(descripcion, d.c_str(), 39); descripcion[39] = '\0';
}
void clsdetalleVenta::setCantidad(int c) { cantidad = c; }
void clsdetalleVenta::setPrecioUnitario(float p) { precioUnitario = p; }

std::string clsdetalleVenta::getCodigo() const { return std::string(codigo); }
std::string clsdetalleVenta::getDescripcion() const { return std::string(descripcion); }
int clsdetalleVenta::getCantidad() const { return cantidad; }
float clsdetalleVenta::getPrecioUnitario() const { return precioUnitario; }

float clsdetalleVenta::getSubTotal() const { return cantidad * precioUnitario; }