#include <iostream>
#include <fstream>
#include <iomanip>
#include "clsPrecios.h"
#include "../../../rlutil.h"

using namespace std;

// ========================================================
// CONSTRUCTOR: Asegura que existan tarifas base
// ========================================================
clsPrecios::clsPrecios() {
    ifstream archivo(ARCHIVO_TARIFAS);
    if (!archivo.good()) {
        archivo.close();
        inicializarTarifasDefault();
    } else {
        archivo.close();
    }
}

// ========================================================
// INICIALIZACIÓN AUTOMÁTICA (Mapeo Sala -> Código Ticket)
// ========================================================
void clsPrecios::inicializarTarifasDefault() {
    // Definimos los tipos que usaste en clsSalas.cpp
    // y les asignamos tus códigos de ticket personalizados.

    clsTarifa t;
    ofstream archivo(ARCHIVO_TARIFAS, ios::binary);

    // 1. BASIC 2D
    t.setCodigo("ENT2DBA");
    t.setDescripcion("BASIC 2D");
    t.setPrecio(4500);
    archivo.write(reinterpret_cast<const char*>(&t), sizeof(clsTarifa));

    // 2. BASIC 3D
    t.setCodigo("ENT3DBA");
    t.setDescripcion("BASIC 3D");
    t.setPrecio(5500);
    archivo.write(reinterpret_cast<const char*>(&t), sizeof(clsTarifa));

    // 3. PREMIUM 2D
    t.setCodigo("ENT2DPR");
    t.setDescripcion("PREMIUM 2D CONFORT");
    t.setPrecio(6500);
    archivo.write(reinterpret_cast<const char*>(&t), sizeof(clsTarifa));

    // 4. PREMIUM 3D
    t.setCodigo("ENT3DPR");
    t.setDescripcion("PREMIUM 3D CONFORT");
    t.setPrecio(7500);
    archivo.write(reinterpret_cast<const char*>(&t), sizeof(clsTarifa));

    // 5. 4D MOTION
    t.setCodigo("ENT4DMO");
    t.setDescripcion("PREMIUM 4D MOTION");
    t.setPrecio(9000);
    archivo.write(reinterpret_cast<const char*>(&t), sizeof(clsTarifa));

    archivo.close();
}

// ========================================================
// LISTAR TARIFAS
// ========================================================
void clsPrecios::mostrarListadoTarifas() const {
    rlutil::cls();
    ifstream archivo(ARCHIVO_TARIFAS, ios::binary);
    clsTarifa t;

    rlutil::setColor(rlutil::YELLOW);
    cout << left << setw(15) << "CODIGO"
         << left << setw(30) << "TIPO DE SALA"
         << left << setw(10) << "PRECIO" << endl;
    cout << string(55, '-') << endl;
    rlutil::setColor(rlutil::WHITE);

    while (archivo.read(reinterpret_cast<char*>(&t), sizeof(clsTarifa))) {
        cout << left << setw(15) << t.getCodigo()
             << left << setw(30) << t.getDescripcion()
             << "$ " << t.getPrecio() << endl;
    }
    archivo.close();
}

// ========================================================
// MODIFICAR PRECIO ENTRADA
// ========================================================
bool clsPrecios::actualizarPrecioEntrada(const string& codigo, float nuevoPrecio) {
    fstream archivo(ARCHIVO_TARIFAS, ios::binary | ios::in | ios::out);
    clsTarifa t;
    bool encontrado = false;

    while (archivo.read(reinterpret_cast<char*>(&t), sizeof(clsTarifa))) {
        if (t.getCodigo() == codigo) {
            t.setPrecio(nuevoPrecio);

            // Retroceder el cursor para sobreescribir
            archivo.seekp(archivo.tellg() - static_cast<streamoff>(sizeof(clsTarifa)));
            archivo.write(reinterpret_cast<const char*>(&t), sizeof(clsTarifa));
            encontrado = true;
            break;
        }
    }
    archivo.close();
    return encontrado;
}

void clsPrecios::menuModificarPreciosEntradas() {
    mostrarListadoTarifas();
    cout << "\nIngrese CODIGO de entrada a modificar: ";
    string cod;
    cin >> cod;

    float precio;
    cout << "Nuevo Precio: $";
    cin >> precio;

    if (actualizarPrecioEntrada(cod, precio)) {
        rlutil::setColor(rlutil::GREEN);
        cout << "Precio actualizado correctamente.\n";
    } else {
        rlutil::setColor(rlutil::RED);
        cout << "Codigo no encontrado.\n";
    }
    rlutil::anykey();
}

// ========================================================
// BUSQUEDA PARA VENTAS
// ========================================================
clsTarifa clsPrecios::buscarPorDescripcion(const std::string& descripcionSala) const {
    ifstream archivo(ARCHIVO_TARIFAS, ios::binary);
    clsTarifa t;
    while (archivo.read(reinterpret_cast<char*>(&t), sizeof(clsTarifa))) {
        // Comparamos strings. Ojo, deben ser exactos.
        if (t.getDescripcion() == descripcionSala) {
            archivo.close();
            return t;
        }
    }
    archivo.close();
    // Retornamos un objeto vacío/gratis si no encuentra (o manejar error)
    return clsTarifa();
}

// ========================================================
// MENU PRINCIPAL DE GESTION DE PRECIOS
// ========================================================
void clsPrecios::menuPrincipalPrecios() {
    int op = 0;
    while (true) {
        rlutil::cls();
        rlutil::setColor(rlutil::YELLOW);
        cout << "--- GESTION DE PRECIOS Y TARIFAS ---\n\n";
        rlutil::setColor(rlutil::WHITE);

        cout << "1. Modificar Precios de ENTRADAS (2D, 3D, etc)\n";
        cout << "2. Modificar Precios de CANDY (Gaseosas, Pochoclos)\n";
        cout << "0. Volver\n";

        cout << "\nSeleccione: ";
        cin >> op;

        switch (op) {
            case 1:
                menuModificarPreciosEntradas();
                break;
            case 2: {
                // AQUÍ USAMOS LA CLASE CANDY
                clsCandy gestorCandy;
                gestorCandy.modificarPrecio(); // Llamamos al menú del otro módulo
                break;
            }
            case 0:
                return;
            default:
                cout << "Opcion incorrecta.\n";
                rlutil::anykey();
        }
    }
}
