#pragma once
#include <string>
#include "clsTarifa.h"
#include "../Candy/clsCandy.h"
#include "../../../mainHeader.h"

const std::string ARCHIVO_TARIFAS = "tarifas.dat";

class clsPrecios {
private:
    void inicializarTarifasDefault();

public:
    clsPrecios();

    void menuModificarPreciosEntradas();
    bool actualizarPrecioEntrada(const std::string& codigo, float nuevoPrecio);

    clsTarifa buscarPorDescripcion(const std::string& descripcionSala) const;
    clsTarifa buscarPorCodigo(const std::string& codigo) const;

    void mostrarListadoTarifas() const;
    void menuPrincipalPrecios();
};
