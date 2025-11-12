#include <iostream>
#include <fstream>
#include <iomanip>
#include "function_persistenciaPeliculas.h"
using namespace std;

// ============================================================
// GUARDAR EN ARCHIVO BINARIO
// ============================================================
void guardarPeliculas(const clsPelicula& gestor) {
    ofstream archivo(ARCHIVO_PELICULAS, ios::binary | ios::trunc);
    if (!archivo) {
        cout << "Error al abrir el archivo para guardar.\n";
        return;
    }

    int cantidad = gestor.getCantidad();
    const clsDataPeliculas* peliculas = gestor.getPeliculas();

    archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(int));
    for (int i = 0; i < cantidad; i++) {
        archivo.write(reinterpret_cast<const char*>(&peliculas[i]), sizeof(clsDataPeliculas));
    }

    archivo.close();
    cout << "Películas guardadas correctamente (" << cantidad << " registros).\n";
}

// ============================================================
// CARGAR DESDE ARCHIVO BINARIO
// ============================================================
void cargarPeliculas(clsPelicula& gestor) {
    ifstream archivo(ARCHIVO_PELICULAS, ios::binary);
    if (!archivo) {
        cout << "No se encontró el archivo de películas. Se creará uno nuevo.\n";
        return;
    }

    int cantidad = 0;
    archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(int));
    if (cantidad <= 0) return;

    gestor.vaciarPeliculas(); // Limpia las existentes

    for (int i = 0; i < cantidad; i++) {
        clsDataPeliculas temp;
        archivo.read(reinterpret_cast<char*>(&temp), sizeof(clsDataPeliculas));
        gestor.agregarPelicula(temp);
    }

    archivo.close();
    cout << cantidad << " películas cargadas desde archivo.\n";
}

// ============================================================
// EXPORTAR A CSV
// ============================================================
void exportarPeliculasCSV(const clsPelicula& gestor, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "Error al crear el archivo CSV.\n";
        return;
    }

    archivo << "ID,Nombre,Duracion,Genero,Clasificacion,Director,FechaEstreno,Idiomas,Formatos,Activa\n";

    const clsDataPeliculas* peliculas = gestor.getPeliculas();
    for (int i = 0; i < gestor.getCantidad(); i++) {
        const clsDataPeliculas& p = peliculas[i];
        archivo << p.getId() << ","
                << p.getNombre() << ","
                << p.getDuracion() << ","
                << p.getGenero() << ","
                << p.getClasificacion() << ","
                << p.getDirector() << ","
                << p.getFechaEstreno().toString() << ","
                << p.getIdiomas() << ","
                << p.getFormatos() << ","
                << (p.estaActiva() ? "1" : "0") << "\n";
    }

    archivo.close();
    cout << "Películas exportadas a '" << nombreArchivo << "'.\n";
}

// ============================================================
// BORRAR ARCHIVO BINARIO
// ============================================================
void borrarArchivoPeliculas() {
    ofstream clear(ARCHIVO_PELICULAS, ios::binary | ios::trunc);
    cout << "Archivo de películas borrado.\n";
}

// ============================================================
// MENU DE CONFIGURACION DE GUARDADO
// ============================================================
void menuGuardarPeliculas(bool& guardadoAutomatico, clsPelicula& gestor) {
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n===== CONFIGURACION DE GUARDADO =====\n";
        cout << "1. " << (guardadoAutomatico ? "Desactivar" : "Activar") << " guardado automatico\n";
        cout << "2. Guardar cambios manualmente\n";
        cout << "3. Exportar datos a CSV\n";
        cout << "4. Borrar todos los datos\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                guardadoAutomatico = !guardadoAutomatico;
                cout << "Guardado automatico " << (guardadoAutomatico ? "activado.\n" : "desactivado.\n");
                break;

            case 2:
                guardarPeliculas(gestor);
                break;

            case 3:
                exportarPeliculasCSV(gestor, "peliculas.csv");
                break;

            case 4:
                borrarArchivoPeliculas();
                break;

            case 0:
                cout << "Volviendo al menu anterior...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }
    }
}
