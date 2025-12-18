#pragma once
#include <string>
#include "clsPeliculas.h"

class clsPelicula;

const std::string ARCHIVO_PELICULAS = "peliculas.dat";

void guardarPeliculas(const clsPelicula& gestor);
void cargarPeliculas(clsPelicula& gestor);
void exportarPeliculasCSV(const clsPelicula& gestor, const std::string& nombreArchivo);
void borrarArchivoPeliculas();

void menuGuardarPeliculas(bool& guardadoAutomatico, clsPelicula& gestor);
