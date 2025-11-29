#pragma once
#include "clsArticulo.h"
#include <string>

const std::string ARCHIVO_CANDY = "candy.dat";
const std::string ARCHIVO_ID_CANDY = "contador_sku.txt";

class clsCandy {
private:
    std::string generarSKU(); // Método privado para crear SKU0001...

public:
    // ABM
    void agregarArticulo();   // Pide datos al usuario y guarda
    void modificarPrecio();   // Busca por SKU y cambia precio
    void modificarStock();    // Suma stock (reposición)
    void darDeBaja();
    
    // Método técnico para Ventas (descuenta stock)
    bool restarStock(const std::string& sku, int cantidad); 

    // Consultas
    void mostrarListado() const;
    int buscarArticulo(const std::string& sku) const; // Retorna posición
    clsArticulo leerArticulo(int pos) const;
    
    // Auxiliar para clsPrecios (Facade)
    bool actualizarPrecioDirecto(const std::string& sku, float nuevoPrecio);
};