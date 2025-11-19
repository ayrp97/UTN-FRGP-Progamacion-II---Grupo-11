#include <iostream>
#include <fstream>
#include <iomanip>
#include "function_persistenciaSalas.h"
#include "../../rlutil.h"
#include "../../mainHeader.h"

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
void borrarArchivoSalas(clsSala& gestor) {
    ofstream clear(ARCHIVO_SALAS, ios::binary | ios::trunc);
    if (!clear.is_open()) {
        cout << "Error al abrir el archivo de salas para borrar.\n";
        return;
    }
    clear.close();

    // Vaciar también las salas en memoria
    gestor.vaciarSalas();  // este método lo definimos en clsSala

    cout << "Archivo de salas y datos en memoria borrados.\n";
}

// ============================================================
// MENU DE CONFIGURACIÓN DE GUARDADO
// ============================================================
void mostrarItemGuardar(const char* texto, int x, int y, bool seleccionado) {
    if (seleccionado) {
        rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::BLACK);
    } else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
    }

    rlutil::locate(x, y);
    cout << texto;

    rlutil::setBackgroundColor(rlutil::BLACK); // Reset
}

void menuGuardarSalas(bool& guardadoAutomatico, clsSala& gestor) {
    int opcion = 0; // Navegación con flechas
    bool salir = false;

    while (!salir) {

        rlutil::cls();
        fondoVentana(); // Tu función de fondo

        rlutil::setColor(rlutil::YELLOW);
        rlutil::locate(46, 12);
        cout << "CONFIGURACION DE GUARDADO";

        // Mostrar items del menú
        rlutil::setColor(rlutil::WHITE);

        mostrarItemGuardar(
            guardadoAutomatico ? " DESACTIVAR GUARDADO AUTOMATICO "
                               : " ACTIVAR GUARDADO AUTOMATICO   ",
            50, 20, opcion == 0
        );

        mostrarItemGuardar(" GUARDAR CAMBIOS MANUALMENTE      ", 50, 21, opcion == 1);
        mostrarItemGuardar(" EXPORTAR SALAS A CSV             ", 50, 22, opcion == 2);
        mostrarItemGuardar(" BORRAR ARCHIVO DE SALAS          ", 50, 23, opcion == 3);
        mostrarItemGuardar(" VOLVER                           ", 50, 25, opcion == 4);

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
                        guardarSalas(gestor);
                        break;

                    case 2:
                        exportarSalasCSV(gestor, "salas.csv");
                        break;

                    case 3:
                        borrarArchivoSalas(gestor);
                        break;

                    case 4:
                        salir = true;
                        break;
                }
                break;
        }
    }
}
