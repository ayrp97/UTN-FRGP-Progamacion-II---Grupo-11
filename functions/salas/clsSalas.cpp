#include <iostream>
#include <fstream>
#include <iomanip>
#include "clsSalas.h"

// ----------------------------------------------------------
// CONSTRUCTOR
// ----------------------------------------------------------
clsSala::clsSala() {
    capacidadMax = 15;
    cantidad = 0;
    salas = new clsDataSalas[capacidadMax];
}

// ----------------------------------------------------------
// DESTRUCTOR
// ----------------------------------------------------------
clsSala::~clsSala() {
    delete[] salas;
}

// ----------------------------------------------------------
// BUSCAR SALA POR ID
// ----------------------------------------------------------
int clsSala::buscarSala(const std::string& idSala) const {
    for (int i = 0; i < cantidad; i++) {
        if (salas[i].getIdSala() == idSala) return i;
    }
    return -1;
}

// ----------------------------------------------------------
// GENERADOR DE ID: SA0001, SA0002, SA0003...
// ----------------------------------------------------------
std::string clsSala::generarIdSala() {
    const std::string archivo = "contador_salas.txt";
    int contador = 1;

    std::ifstream in(archivo);
    if (in.is_open()) {
        in >> contador;
        in.close();
    }

    std::ostringstream oss;
    oss << "SA" << std::setw(5) << std::setfill('0') << contador;

    std::ofstream out(archivo);
    out << contador + 1;
    out.close();

    return oss.str();
}

// ----------------------------------------------------------
// ASIGNAR CAPACIDAD SEGÚN TIPO
// ----------------------------------------------------------
int obtenerCapacidadPorTipo(const std::string& tipo) {
    if (tipo == "BASIC 2D") return 120;
    if (tipo == "BASIC 3D") return 120;
    if (tipo == "PREMIUM 2D CONFORT") return 100;
    if (tipo == "PREMIUM 3D CONFORT") return 100;
    if (tipo == "PREMIUM 4D MOTION") return 80;
    return 0;
}

// ----------------------------------------------------------
// CREAR SALA
// ----------------------------------------------------------
void clsSala::crearSala() {
    if (cantidad >= capacidadMax) {
        std::cout << "No se pueden crear más salas (máximo 15).\n";
        return;
    }

    clsDataSalas nueva;

    std::string id = generarIdSala();
    nueva.setIdSala(id);

    std::cout << "ID generado: " << id << "\n";

    std::string tipo;
    std::cout << "Ingrese tipo de sala:\n";
    std::cout << "1) BASIC 2D\n2) BASIC 3D\n3) PREMIUM 2D CONFORT\n4) PREMIUM 3D CONFORT\n5) PREMIUM 4D MOTION\n";
    std::cout << "Opcion: ";

    int op;
    std::cin >> op;
    std::cin.ignore();

    switch (op) {
        case 1: tipo = "BASIC 2D"; break;
        case 2: tipo = "BASIC 3D"; break;
        case 3: tipo = "PREMIUM 2D CONFORT"; break;
        case 4: tipo = "PREMIUM 3D CONFORT"; break;
        case 5: tipo = "PREMIUM 4D MOTION"; break;
        default:
            std::cout << "Tipo inválido.\n";
            return;
    }

    int capacidad = obtenerCapacidadPorTipo(tipo);
    nueva.setCapacidad(capacidad);

    nueva.setActiva(true);

    salas[cantidad++] = nueva;

    std::cout << "Sala creada correctamente.\n";
}

// ----------------------------------------------------------
// MODIFICAR SALA (solo estado por ahora)
// ----------------------------------------------------------
void clsSala::modificarSala(const std::string& idSala) {
    int pos = buscarSala(idSala);
    if (pos == -1) {
        std::cout << "ID no encontrado.\n";
        return;
    }

    std::cout << "Modificar sala " << idSala << "\n";
    std::cout << "1) Activar\n2) Desactivar\n";
    int op; std::cin >> op; std::cin.ignore();

    if (op == 1) salas[pos].setActiva(true);
    else if (op == 2) salas[pos].setActiva(false);

    std::cout << "Modificación realizada.\n";
}

// ----------------------------------------------------------
// MOSTRAR CAPACIDAD
// ----------------------------------------------------------
void clsSala::verCapacidad(const std::string& idSala) const {
    int pos = buscarSala(idSala);
    if (pos == -1) {
        std::cout << "ID no encontrado.\n";
        return;
    }

    std::cout << "Capacidad de la sala " << idSala << ": "
              << salas[pos].getCapacidad() << " asientos.\n";
}

// ----------------------------------------------------------
// ASIGNAR / DESASIGNAR PELICULA (placeholder)
// ----------------------------------------------------------
void clsSala::asignarPelicula(const std::string& idSala, const std::string& idPelicula) {
    std::cout << "(Pendiente, depende de clsDataFuncion y peliculas.dat)\n";
}

void clsSala::desasignarPelicula(const std::string& idSala) {
    std::cout << "(Pendiente, depende de clsDataFuncion)\n";
}

// ----------------------------------------------------------
// MOSTRAR SALAS
// ----------------------------------------------------------
void clsSala::mostrarSalas() const {
    for (int i = 0; i < cantidad; i++) {
        std::cout << salas[i].getIdSala()
                  << " - Capacidad: " << salas[i].getCapacidad()
                  << " - Estado: " << (salas[i].estaActiva() ? "Activa" : "Inactiva")
                  << "\n";
    }
}

// ----------------------------------------------------------
int clsSala::getCantidad() const { return cantidad; }
const clsDataSalas* clsSala::getSalas() const { return salas; }

void clsSala::vaciarSalas() {
    cantidad = 0;
}

void clsSala::agregarSala(const clsDataSalas& sala) {
    if (cantidad < capacidadMax) {
        salas[cantidad++] = sala;
    }
}
