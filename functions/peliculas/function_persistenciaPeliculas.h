#pragma once
#include <string>
#include "clsPeliculas.h"

class clsPelicula;

// Ruta del archivo binario
const std::string ARCHIVO_PELICULAS = "peliculas.dat";

// Funciones principales de persistencia
void guardarPeliculas(const clsPelicula& gestor);
void cargarPeliculas(clsPelicula& gestor);
void exportarPeliculasCSV(const clsPelicula& gestor, const std::string& nombreArchivo);
void borrarArchivoPeliculas();

// Menú de configuración de guardado
void menuGuardarPeliculas(bool& guardadoAutomatico, clsPelicula& gestor);
