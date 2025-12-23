#pragma once
#include <string>
#include "clsSalas.h"

const std::string ARCHIVO_SALAS = "salas.dat";

void guardarSalas(const clsSala& gestor);

void cargarSalas(clsSala& gestor);

void exportarSalasCSV(const clsSala& gestor, const std::string& nombreArchivo);

void borrarArchivoSalas(clsSala& gestor);

void menuGuardarSalas(bool& guardadoAutomatico, clsSala& gestor);
