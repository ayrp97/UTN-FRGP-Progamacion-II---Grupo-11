#include <iostream>
#include <fstream>
#include <iomanip>
#include "function_persistenciaSalas.h"

using namespace std;

// ============================================================
// GUARDAR EN ARCHIVO BINARIO
// ============================================================
void guardarSalas(const clsSala& gestor) {
    ofstream archivo(ARCHIVO_SALAS, ios::binary | ios::trunc);
    if (!archivo) {
        cout << "Error al abrir el archivo de salas para guardar.\n";
        return;
    }

    int cantidad = gestor.getCantidad();
    const clsDataSalas* salas = gestor.getSalas();

    archivo.write(reinterpret_cast<const char*>(&cantidad), sizeof(int));

    for (int i = 0; i < cantidad; i++) {
        archivo.write(reinterpret_cast<const char*>(&salas[i]), sizeof(clsDataSalas));
    }

    archivo.close();
    cout << "Salas guardadas correctamente (" << cantidad << " registros).\n";
}

// ============================================================
// CARGAR DESDE ARCHIVO BINARIO (VERSIÓN CORRECTA)
// ============================================================
void cargarSalas(clsSala& gestor) {
    ifstream archivo(ARCHIVO_SALAS, ios::binary);
    if (!archivo) {
        cout << "No se encontró 'salas.dat'. Se creará uno nuevo.\n";
        return;
    }

    int cantidad = 0;
    archivo.read(reinterpret_cast<char*>(&cantidad), sizeof(int));

    if (!archivo || cantidad <= 0) {
        cout << "No hay salas registradas.\n";
        return;
    }

    // Limpiar gestor actual sin llamar a crearSala()
    gestor.vaciarSalas();

    // Cargar cada registro directamente al array
    for (int i = 0; i < cantidad; i++) {
        clsDataSalas temp;
        archivo.read(reinterpret_cast<char*>(&temp), sizeof(clsDataSalas));
        if (!archivo) break;

        gestor.agregarSala(temp);   // NO genera ID, NO pide input
    }

    archivo.close();
    cout << cantidad << " salas cargadas desde archivo.\n";
}

// ============================================================
// EXPORTAR A CSV
// ============================================================
void exportarSalasCSV(const clsSala& gestor, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cout << "Error al crear archivo CSV.\n";
        return;
    }

    archivo << "ID Sala,Capacidad,Activa\n";

    const clsDataSalas* salas = gestor.getSalas();
    for (int i = 0; i < gestor.getCantidad(); i++) {
        const clsDataSalas& s = salas[i];

        archivo << s.getIdSala() << ","
                << s.getCapacidad() << ","
                << (s.estaActiva() ? "1" : "0") << "\n";
    }

    archivo.close();
    cout << "Salas exportadas a '" << nombreArchivo << "'.\n";
}

// ============================================================
// BORRAR ARCHIVO
// ============================================================
void borrarArchivoSalas() {
    ofstream clear(ARCHIVO_SALAS, ios::binary | ios::trunc);
    cout << "Archivo de salas borrado.\n";
}

// ============================================================
// MENU DE CONFIGURACIÓN DE GUARDADO
// ============================================================
void menuGuardarSalas(bool& guardadoAutomatico, clsSala& gestor) {
    int opcion = -1;

    while (opcion != 0) {
        cout << "\n===== CONFIGURACION DE GUARDADO DE SALAS =====\n";
        cout << "1. " << (guardadoAutomatico ? "Desactivar" : "Activar") << " guardado automatico\n";
        cout << "2. Guardar cambios manualmente\n";
        cout << "3. Exportar salas a CSV\n";
        cout << "4. Borrar archivo de salas\n";
        cout << "0. Volver\n";
        cout << "Opcion: ";

        cin >> opcion;

        // Lectura segura para evitar fallos
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = -1;
        } else {
            cin.ignore(1000, '\n');
        }

        switch (opcion) {
            case 1:
                guardadoAutomatico = !guardadoAutomatico;
                cout << "Guardado automatico "
                     << (guardadoAutomatico ? "activado.\n" : "desactivado.\n");
                break;

            case 2:
                guardarSalas(gestor);
                break;

            case 3:
                exportarSalasCSV(gestor, "salas.csv");
                break;

            case 4:
                borrarArchivoSalas();
                break;

            case 0:
                cout << "Volviendo...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
                break;
        }
    }
}
