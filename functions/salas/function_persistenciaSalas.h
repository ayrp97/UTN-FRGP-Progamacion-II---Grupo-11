#pragma once
#include <string>
#include "clsSalas.h"

const std::string ARCHIVO_SALAS = "salas.dat";

// Guardado / Carga
void guardarSalas(const clsSala& gestor);
void cargarSalas(clsSala& gestor);

// Exportación
void exportarSalasCSV(const clsSala& gestor, const std::string& nombreArchivo);

// Borrado
void borrarArchivoSalas(clsSala& gestor);

// Menú de configuración
void menuGuardarSalas(bool& guardadoAutomatico, clsSala& gestor);
