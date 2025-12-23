#pragma once
#include "clsArticulo.h"
#include <string>

const std::string ARCHIVO_CANDY = "candy.dat";
const std::string ARCHIVO_ID_CANDY = "contador_sku.txt";

class clsCandy {
private:
    std::string generarSKU();
public:
    void agregarArticulo();
    void modificarPrecio();
    void modificarStock();
    bool darDeBajaLogica(const std::string& sku);
    void menuDarDeBaja();

    bool restarStock(const std::string& sku, int cantidad);

    void mostrarListado() const;
    int buscarArticulo(const std::string& sku) const;
    clsArticulo leerArticulo(int pos) const;

    bool actualizarPrecioDirecto(const std::string& sku, float nuevoPrecio);
};
