#include <iostream>
#include <fstream>
#include <iomanip>
#include "function_persistenciaPeliculas.h"
#include "../../rlutil.h"
#include "../../mainHeader.h"
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

void mostrarItemGuardarPeliculas(const char* texto, int x, int y, bool seleccionado) {
    if (seleccionado) {
        rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::BLACK);
    } else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
    }

    rlutil::locate(x, y);
    cout << texto;

    rlutil::setBackgroundColor(rlutil::BLACK);
}

void menuGuardarPeliculas(bool& guardadoAutomatico, clsPelicula& gestor) {
    int opcion = 0;
    bool salir = false;

    while (!salir) {
        rlutil::cls();
        fondoVentana();

        rlutil::setColor(rlutil::YELLOW);
        rlutil::locate(46, 12);
        cout << "CONFIGURACION DE GUARDADO - PELICULAS";

        rlutil::setColor(rlutil::WHITE);

        // ----- Opciones -----
        mostrarItemGuardarPeliculas(
            guardadoAutomatico ? " DESACTIVAR GUARDADO AUTOMATICO " 
                               : " ACTIVAR GUARDADO AUTOMATICO   ",
            50, 20, opcion == 0
        );

        mostrarItemGuardarPeliculas(" GUARDAR CAMBIOS MANUALMENTE      ", 50, 21, opcion == 1);
        mostrarItemGuardarPeliculas(" EXPORTAR PELICULAS A CSV         ", 50, 22, opcion == 2);
        mostrarItemGuardarPeliculas(" BORRAR ARCHIVO DE PELICULAS      ", 50, 23, opcion == 3);
        mostrarItemGuardarPeliculas(" VOLVER                           ", 50, 25, opcion == 4);

        // Entrada por teclado
        int key = rlutil::getkey();

        switch (key) {

            case rlutil::KEY_UP:
                opcion--;
                if (opcion < 0) opcion = 4;
                break;

            case rlutil::KEY_DOWN:
                opcion++;
                if (opcion > 4) opcion = 0;
                break;

            case rlutil::KEY_ENTER:
                switch (opcion) {

                    case 0:
                        guardadoAutomatico = !guardadoAutomatico;
                        break;

                    case 1:
                        guardarPeliculas(gestor);
                        break;

                    case 2:
                        exportarPeliculasCSV(gestor, "peliculas.csv");
                        break;

                    case 3:
                        borrarArchivoPeliculas();
                        break;

                    case 4:
                        salir = true;
                        break;
                }
                break;
        }
    }
}