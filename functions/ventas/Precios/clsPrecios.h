#pragma once
#include <string>
#include "clsTarifa.h"
#include "../Candy/clsCandy.h" // CONEXIÓN CON CANDY
#include "../../../mainHeader.h"

const std::string ARCHIVO_TARIFAS = "tarifas.dat";

class clsPrecios {
private:
    // Si el archivo no existe, crea las tarifas base (2D, 3D, etc.)
    void inicializarTarifasDefault();

public:
    clsPrecios(); // El constructor verificará si existe el archivo

    // --- GESTIÓN DE ENTRADAS ---
    void menuModificarPreciosEntradas();
    bool actualizarPrecioEntrada(const std::string& codigo, float nuevoPrecio);

    // Método para Ventas: Le das "BASIC 2D" y te devuelve el objeto tarifa completo
    clsTarifa buscarPorDescripcion(const std::string& descripcionSala) const;
    clsTarifa buscarPorCodigo(const std::string& codigo) const;

    void mostrarListadoTarifas() const;

    // --- GESTIÓN CENTRALIZADA (Entradas + Candy) ---
    void menuPrincipalPrecios();
};
