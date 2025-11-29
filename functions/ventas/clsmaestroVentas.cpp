#include "clsmaestroVentas.h"

clsmaestroVenta::clsmaestroVenta() {
    std::strcpy(idVenta, "VE00000"); // Inicializar vacío
    dniCliente = 0;
    fecha = clsFecha(); // Usa el constructor por defecto (hoy o 1/1/2000)
    hora = 0;
    
    cantidadDetalles = 0;
    importeTotal = 0.0f;
    activa = true;
    // El array 'detalles' se autoinicializa con sus constructores vacíos
}

// ================= SETTERS =================
void clsmaestroVenta::setIdVenta(const std::string& id) {
    std::strncpy(idVenta, id.c_str(), 9);
    idVenta[9] = '\0';
}
void clsmaestroVenta::setDniCliente(int dni) { dniCliente = dni; }
void clsmaestroVenta::setFecha(const clsFecha& f) { fecha = f; }
void clsmaestroVenta::setHora(int h) { hora = h; }
void clsmaestroVenta::setActiva(bool a) { activa = a; }

// ================= GETTERS =================
std::string clsmaestroVenta::getIdVenta() const {
    return std::string(idVenta);
}
int clsmaestroVenta::getDniCliente() const { return dniCliente; }
clsFecha clsmaestroVenta::getFecha() const { return fecha; }
int clsmaestroVenta::getHora() const { return hora; }
float clsmaestroVenta::getImporteTotal() const { return importeTotal; }
bool clsmaestroVenta::estaActiva() const { return activa; }

// ================= LOGICA DE DETALLES =================

bool clsmaestroVenta::agregarDetalle(const clsdetalleVenta& item) {
    if (cantidadDetalles >= 20) {
        return false; // El ticket está lleno (límite de array)
    }

    // 1. Guardamos el item en la siguiente posición libre
    detalles[cantidadDetalles] = item;
    
    // 2. Aumentamos el contador
    cantidadDetalles++;

    // 3. ACTUALIZAMOS EL TOTAL AUTOMÁTICAMENTE
    importeTotal += item.getSubTotal();

    return true;
}

int clsmaestroVenta::getCantidadDetalles() const {
    return cantidadDetalles;
}

clsdetalleVenta clsmaestroVenta::leerDetalle(int indice) const {
    if (indice >= 0 && indice < cantidadDetalles) {
        return detalles[indice];
    }
    // Si pide un indice invalido, devolvemos uno vacio
    return clsdetalleVenta();
}