#include <iostream>
#include <fstream>
#include <iomanip>
#include "function_persistenciaPeliculas.h"
#include "../../rlutil.h"
#include "../../mainHeader.h"
using namespace std;

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

void cargarPeliculas(clsPelicula& gestor) {
    ifstream archivo(ARCHIVO_PELICULAS, ios::binary);
    if (!archivo) {
        cout << "No se encontró el archivo de películas. Se creará uno nuevo.\n";
        return;
    }

    int cantidad = 0;
    archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(int));
    if (cantidad <= 0) return;

    gestor.vaciarPeliculas();
    for (int i = 0; i < cantidad; i++) {
        clsDataPeliculas temp;
        archivo.read(reinterpret_cast<char*>(&temp), sizeof(clsDataPeliculas));
        gestor.agregarPelicula(temp);
    }

    archivo.close();
}

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

void borrarArchivoPeliculas() {
    ofstream clear(ARCHIVO_PELICULAS, ios::binary | ios::trunc);
    cout << "Archivo de películas borrado.\n";
}

void menuGuardarPeliculas(bool& guardadoAutomatico, clsPelicula& gestor) {

    while (true) {
        rlutil::cls();
        fondoVentana();

        const char* textoAuto = guardadoAutomatico ? " DESACTIVAR GUARDADO AUTOMATICO "
                                                   : " ACTIVAR GUARDADO AUTOMATICO ";
        const char* opciones[] = {
            textoAuto,
            " GUARDAR CAMBIOS MANUALMENTE ",
            " EXPORTAR PELICULAS A CSV ",
            " BORRAR ARCHIVO DE PELICULAS ",
            " VOLVER "
        };

        int cantidad = 5;

        int op = menuInteractivo(opciones, cantidad, "CONFIGURACION DE GUARDADO", 50, 20);

        if (op == -1 || op == 4) return;

        switch (op) {
            case 0: 
                guardadoAutomatico = !guardadoAutomatico;
                break;

            case 1:
                rlutil::cls();
                fondoVentana();
                rlutil::locate(40, 12);
                guardarPeliculas(gestor);
                rlutil::anykey();
                break;

            case 2:
                rlutil::cls();
                fondoVentana();
                rlutil::locate(40, 12);
                exportarPeliculasCSV(gestor, "peliculas.csv");
                rlutil::anykey();
                break;

            case 3:
                rlutil::cls();
                fondoVentana();
                rlutil::locate(40, 12);
                borrarArchivoPeliculas();
                rlutil::anykey();
                break;
        }
    }
}
