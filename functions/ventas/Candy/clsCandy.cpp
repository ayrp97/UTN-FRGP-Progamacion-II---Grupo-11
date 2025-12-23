#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "clsCandy.h"
#include "../../../rlutil.h"

using namespace std;

string clsCandy::generarSKU() {
    int contador = 1;
    ifstream in(ARCHIVO_ID_CANDY);
    if (in.is_open()) {
        in >> contador;
        in.close();
    }

    ostringstream oss;
    oss << "SKU" << setw(4) << setfill('0') << contador;

    ofstream out(ARCHIVO_ID_CANDY);
    out << contador + 1;
    out.close();

    return oss.str();
}

int clsCandy::buscarArticulo(const string& sku) const {
    clsArticulo art;
    ifstream archivo(ARCHIVO_CANDY, ios::binary);
    int pos = 0;

    while (archivo.read(reinterpret_cast<char*>(&art), sizeof(clsArticulo))) {
        if (art.estaActivo() && art.getSKU() == sku) {
            archivo.close();
            return pos;
        }
        pos++;
    }
    return -1;
}

clsArticulo clsCandy::leerArticulo(int pos) const {
    clsArticulo art;
    ifstream archivo(ARCHIVO_CANDY, ios::binary);
    archivo.seekg(pos * sizeof(clsArticulo), ios::beg);
    archivo.read(reinterpret_cast<char*>(&art), sizeof(clsArticulo));
    return art;
}

void clsCandy::agregarArticulo() {
    rlutil::cls();
    rlutil::setColor(rlutil::YELLOW);
    cout << "--- AGREGAR NUEVO ARTICULO AL CANDY ---\n\n";
    rlutil::setColor(rlutil::WHITE);

    clsArticulo nuevo;
    string temp;
    float precio;
    int stock;

    string sku = generarSKU();
    nuevo.setSKU(sku);
    cout << "SKU Generado: " << sku << endl;

    cout << "Nombre/Descripcion: ";
    cin.ignore();
    getline(cin, temp);
    nuevo.setNombre(temp);

    cout << "Precio Unitario: $";
    cin >> precio;
    nuevo.setPrecio(precio);

    cout << "Stock Inicial: ";
    cin >> stock;
    nuevo.setStock(stock);

    nuevo.setActivo(true);

    ofstream archivo(ARCHIVO_CANDY, ios::binary | ios::app);
    archivo.write(reinterpret_cast<const char*>(&nuevo), sizeof(clsArticulo));
    archivo.close();

    rlutil::setColor(rlutil::GREEN);
    cout << "\nArticulo guardado exitosamente!\n";
    rlutil::anykey();
}

void clsCandy::mostrarListado() const {
    rlutil::cls();
    ifstream archivo(ARCHIVO_CANDY, ios::binary);
    if (!archivo) {
        cout << "No hay articulos cargados.\n";
        return;
    }

    clsArticulo art;
    rlutil::setColor(rlutil::YELLOW);
    cout << left << setw(10) << "SKU"
         << left << setw(30) << "DESCRIPCION"
         << left << setw(10) << "PRECIO"
         << left << setw(10) << "STOCK" << endl;
    cout << string(60, '-') << endl;
    rlutil::setColor(rlutil::WHITE);

    while (archivo.read(reinterpret_cast<char*>(&art), sizeof(clsArticulo))) {
        if (art.estaActivo()) {
            cout << left << setw(10) << art.getSKU()
                 << left << setw(30) << art.getNombre()
                 << left << setw(2) << "$" << setw(8) << art.getPrecio()
                 << left << setw(10) << art.getStock() << endl;
        }
    }
    archivo.close();
}

void clsCandy::modificarPrecio() {
    mostrarListado();
    cout << "\nIngrese SKU a modificar: ";
    string sku;
    cin >> sku;
    int pos = buscarArticulo(sku);
    if (pos == -1) {
        cout << "Articulo no encontrado.\n";
        rlutil::anykey();
        return;
    }

    clsArticulo art = leerArticulo(pos);
    cout << "Precio actual: $" << art.getPrecio() << endl;

    float nuevoPrecio;
    cout << "Nuevo precio: $";
    cin >> nuevoPrecio;
    art.setPrecio(nuevoPrecio);

    fstream archivo(ARCHIVO_CANDY, ios::binary | ios::in | ios::out);
    archivo.seekp(pos * sizeof(clsArticulo), ios::beg);
    archivo.write(reinterpret_cast<const char*>(&art), sizeof(clsArticulo));
    archivo.close();

    cout << "Precio actualizado.\n";
    rlutil::anykey();
}

bool clsCandy::actualizarPrecioDirecto(const string& sku, float nuevoPrecio) {
    int pos = buscarArticulo(sku);
    if (pos == -1) return false;

    clsArticulo art = leerArticulo(pos);
    art.setPrecio(nuevoPrecio);

    fstream archivo(ARCHIVO_CANDY, ios::binary | ios::in | ios::out);
    archivo.seekp(pos * sizeof(clsArticulo), ios::beg);
    archivo.write(reinterpret_cast<const char*>(&art), sizeof(clsArticulo));
    return true;
}

bool clsCandy::restarStock(const string& sku, int cantidad) {
    int pos = buscarArticulo(sku);
    if (pos == -1) return false;

    clsArticulo art = leerArticulo(pos);

    if (art.getStock() < cantidad) return false;

    art.setStock(art.getStock() - cantidad);

    fstream archivo(ARCHIVO_CANDY, ios::binary | ios::in | ios::out);
    archivo.seekp(pos * sizeof(clsArticulo), ios::beg);
    archivo.write(reinterpret_cast<const char*>(&art), sizeof(clsArticulo));
    return true;
}

void clsCandy::modificarStock() {
    rlutil::cls();
    mostrarListado();
    cout << "\nIngrese SKU para reponer stock: ";
    string sku;
    cin >> sku;

    int pos = buscarArticulo(sku);
    if (pos == -1) {
        cout << "Articulo no encontrado.\n";
        rlutil::anykey();
        return;
    }

    clsArticulo art = leerArticulo(pos);
    cout << "Articulo: " << art.getNombre() << endl;
    cout << "Stock actual: " << art.getStock() << endl;

    int cantidad;
    cout << "Cantidad a agregar: ";
    cin >> cantidad;

    if (cantidad <= 0) {
        cout << "La cantidad debe ser positiva.\n";
        rlutil::anykey();
        return;
    }

    art.setStock(art.getStock() + cantidad);

    fstream archivo(ARCHIVO_CANDY, ios::binary | ios::in | ios::out);
    archivo.seekp(pos * sizeof(clsArticulo), ios::beg);
    archivo.write(reinterpret_cast<const char*>(&art), sizeof(clsArticulo));
    archivo.close();

    rlutil::setColor(rlutil::GREEN);
    cout << "Stock actualizado. Nuevo total: " << art.getStock() << endl;
    rlutil::anykey();
}

bool clsCandy::darDeBajaLogica(const string& sku) {

    int pos = buscarArticulo(sku);
    if (pos == -1) return false;

    clsArticulo art = leerArticulo(pos);
    
    art.setActivo(false);

    fstream archivo(ARCHIVO_CANDY, ios::binary | ios::in | ios::out);

    archivo.seekp(pos * sizeof(clsArticulo), ios::beg);
    archivo.write(reinterpret_cast<const char*>(&art), sizeof(clsArticulo));
    archivo.close();

    return true;
}

void clsCandy::menuDarDeBaja() {
    rlutil::cls();
    
    mostrarListado(); 
    
    rlutil::setColor(rlutil::RED);
    cout << "\n--- DAR DE BAJA ARTICULO ---\n";
    rlutil::setColor(rlutil::WHITE);

    string sku;
    cout << "Ingrese el SKU del articulo a eliminar: ";
    cin >> sku;

    cout << "Esta seguro que desea eliminar " << sku << "? (S/N): ";
    char confirmacion;
    cin >> confirmacion;

    if (confirmacion == 's' || confirmacion == 'S') {
        if (darDeBajaLogica(sku)) {
            rlutil::setColor(rlutil::GREEN);
            cout << "\nArticulo dado de baja exitosamente.\n";
        } else {
            rlutil::setColor(rlutil::RED);
            cout << "\nError: No se encontro el articulo con ese SKU.\n";
        }
    } else {
        rlutil::setColor(rlutil::YELLOW);
        cout << "\nOperacion cancelada.\n";
    }
    
    rlutil::anykey();
}