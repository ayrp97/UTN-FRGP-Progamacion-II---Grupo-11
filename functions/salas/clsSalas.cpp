#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "clsSalas.h"

clsSala::clsSala() {
    capacidadMax = 15;
    cantidad = 0;
    salas = new clsDataSalas[capacidadMax];
}

clsSala::~clsSala() {
    delete[] salas;
}

int clsSala::buscarSala(const std::string& idSala) const {
    for (int i = 0; i < cantidad; i++) {
        if (salas[i].getIdSala() == idSala) return i;
    }
    return -1;
}

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

int obtenerCapacidadPorTipo(const std::string& tipo) {
    if (tipo == "BASIC 2D") return 120;
    if (tipo == "BASIC 3D") return 120;
    if (tipo == "PREMIUM 2D CONFORT") return 100;
    if (tipo == "PREMIUM 3D CONFORT") return 100;
    if (tipo == "PREMIUM 4D MOTION") return 80;
    return 0;
}

void clsSala::crearSala() {
    if (cantidad >= capacidadMax) {
        std::cout << "No se pueden crear más salas.\n";
        return;
    }

    clsDataSalas nueva;

    std::string id = generarIdSala();
    nueva.setIdSala(id);

    std::string tipoSeleccionado;
    int capacidad = 0;

    std::cout << "Ingrese tipo de sala:\n";
    std::cout << "1) BASIC 2D\n2) BASIC 3D\n3) PREMIUM 2D CONFORT\n4) PREMIUM 3D CONFORT\n5) PREMIUM 4D MOTION\n";
    std::cout << "Opcion: ";
    int op;
    std::cin >> op;
    std::cin.ignore();

    switch (op) {
        case 1: tipoSeleccionado = "BASIC 2D"; capacidad = 120; break;
        case 2: tipoSeleccionado = "BASIC 3D"; capacidad = 120; break;
        case 3: tipoSeleccionado = "PREMIUM 2D CONFORT"; capacidad = 100; break;
        case 4: tipoSeleccionado = "PREMIUM 3D CONFORT"; capacidad = 100; break;
        case 5: tipoSeleccionado = "PREMIUM 4D MOTION"; capacidad = 80; break;
        default:
            std::cout << "Tipo inválido.\n";
            return;
    }

    nueva.setTipoSala(tipoSeleccionado);
    nueva.setCapacidad(capacidad);
    
    nueva.setActiva(true);
    salas[cantidad++] = nueva;

    std::cout << "Sala " << tipoSeleccionado << " creada correctamente.\n";
}

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

void clsSala::verCapacidad(const std::string& idSala) const {
    int pos = buscarSala(idSala);
    if (pos == -1) {
        std::cout << "ID no encontrado.\n";
        return;
    }

    std::cout << "Capacidad de la sala " << idSala << ": "
              << salas[pos].getCapacidad() << " asientos.\n";
}

void clsSala::asignarPelicula(const std::string& idSala, const std::string& idPelicula) {
    std::cout << "(Pendiente, depende de clsDataFuncion y peliculas.dat)\n";
}

void clsSala::desasignarPelicula(const std::string& idSala) {
    std::cout << "(Pendiente, depende de clsDataFuncion)\n";
}

void clsSala::mostrarSalas() const {
    for (int i = 0; i < cantidad; i++) {
        std::cout << salas[i].getIdSala()
                  << " - Capacidad: " << salas[i].getCapacidad()
                  << " - Estado: " << (salas[i].estaActiva() ? "Activa" : "Inactiva")
                  << "\n";
    }
}

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
