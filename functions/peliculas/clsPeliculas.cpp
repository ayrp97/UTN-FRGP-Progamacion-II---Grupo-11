#include "clsPeliculas.h"
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>


// ------------------- Constructor y Destructor -------------------

clsPelicula::clsPelicula() {
    capacidad = 5;
    cantidad = 0;
    peliculas = new clsDataPeliculas[capacidad];
    guardadoAutomatico = true; // 🔹 activado por defecto
}

clsPelicula::~clsPelicula() {
    delete[] peliculas;
}

// ------------------- Métodos de control -------------------

void clsPelicula::setGuardadoAutomatico(bool estado) {
    guardadoAutomatico = estado;
}

bool clsPelicula::getGuardadoAutomatico() const {
    return guardadoAutomatico;
}

// ------------------- Métodos privados -------------------


std::string clsPelicula::generarId() {
    const std::string archivo = "contador_id_peliculas.txt";
    int contador = 1;

    // Leer el último valor del archivo
    std::ifstream in(archivo);
    if (in.is_open()) {
        in >> contador;
        in.close();
    }

    // Generar el ID con 5 dígitos
    std::ostringstream oss;
    oss << "PE" << std::setw(5) << std::setfill('0') << contador;

    // Guardar el siguiente valor en el archivo
    std::ofstream out(archivo);
    if (out.is_open()) {
        out << (contador + 1);
        out.close();
    }

    return oss.str();
}

void clsPelicula::redimensionar() {
    int nuevaCapacidad = capacidad * 2;
    clsDataPeliculas* nuevoArray = new clsDataPeliculas[nuevaCapacidad];

    for (int i = 0; i < cantidad; i++) {
        nuevoArray[i] = peliculas[i];
    }

    delete[] peliculas;
    peliculas = nuevoArray;
    capacidad = nuevaCapacidad;
}

// ------------------- Métodos públicos -------------------

void clsPelicula::cargarNuevaPelicula() {
    if (cantidad == capacidad) redimensionar();

    clsDataPeliculas p;
    p.setId(generarId());

    std::string temp;
    int dur;

    std::cout << "Nombre: "; std::getline(std::cin, temp); p.setNombre(temp);
    std::cout << "Duracion (minutos): "; std::cin >> dur; std::cin.ignore();
    p.setDuracion(dur);
    std::cout << "Genero: "; std::getline(std::cin, temp); p.setGenero(temp);
    std::cout << "Clasificacion (ATP, +16, +18): "; std::getline(std::cin, temp); p.setClasificacion(temp);
    std::cout << "Director: "; std::getline(std::cin, temp); p.setDirector(temp);

    std::cout << "Fecha de estreno:\n";
    clsFecha f; f.cargar();
    p.setFechaEstreno(f);

    std::cout << "Idiomas disponibles: ";
    std::cin.ignore();
    std::getline(std::cin, temp); p.setIdiomas(temp);
    std::cout << "Formato de proyeccion: ";
    std::cin.ignore();
    std::getline(std::cin, temp); p.setFormatos(temp);

    p.setActiva(true);
    peliculas[cantidad++] = p;

    std::cout << "Película cargada con ID: " << p.getId() << "\n";

    // 🔹 Guardado automático
    if (guardadoAutomatico) guardarPeliculas(*this);

    std::cout << "Presione ENTER para continuar...";
    std::cin.get();

}

void clsPelicula::modificarPelicula(const std::string& id) {
    for (int i = 0; i < cantidad; i++) {
        if (peliculas[i].getId() == id) {
            clsDataPeliculas& p = peliculas[i];
            int opcion = 0;

            while (opcion != 9) {
                std::cout << "\n--- Modificar Película ---\n";
                std::cout << "1. Nombre (" << p.getNombre() << ")\n";
                std::cout << "2. Duracion (" << p.getDuracion() << ")\n";
                std::cout << "3. Genero (" << p.getGenero() << ")\n";
                std::cout << "4. Clasificacion (" << p.getClasificacion() << ")\n";
                std::cout << "5. Director (" << p.getDirector() << ")\n";
                std::cout << "6. Idiomas (" << p.getIdiomas() << ")\n";
                std::cout << "7. Formato (" << p.getFormatos() << ")\n";
                std::cout << "8. Fecha de estreno ("; p.getFechaEstreno().mostrar(); std::cout << ")\n";
                std::cout << "9. Salir\n";
                std::cout << "Ingrese la opcion a modificar: ";
                std::cin >> opcion; std::cin.ignore();

                std::string temp;
                int dur;

                switch(opcion) {
                    case 1: std::cout << "Nuevo Nombre: "; std::getline(std::cin, temp); if (!temp.empty()) p.setNombre(temp); break;
                    case 2: std::cout << "Nueva Duracion (min): "; std::cin >> dur; std::cin.ignore(); p.setDuracion(dur); break;
                    case 3: std::cout << "Nuevo Genero: "; std::getline(std::cin, temp); if (!temp.empty()) p.setGenero(temp); break;
                    case 4: std::cout << "Nueva Clasificacion: "; std::getline(std::cin, temp); if (!temp.empty()) p.setClasificacion(temp); break;
                    case 5: std::cout << "Nuevo Director: "; std::getline(std::cin, temp); if (!temp.empty()) p.setDirector(temp); break;
                    case 6: std::cout << "Nuevos Idiomas: "; std::getline(std::cin, temp); if (!temp.empty()) p.setIdiomas(temp); break;
                    case 7: std::cout << "Nuevo Formato: "; std::getline(std::cin, temp); if (!temp.empty()) p.setFormatos(temp); break;
                    case 8: {
                        std::cout << "Nueva fecha de estreno:\n";
                        clsFecha nuevaFecha; nuevaFecha.cargar(); p.setFechaEstreno(nuevaFecha);
                        break;
                    }
                    case 9: std::cout << "Saliendo del menu de modificacion...\n"; break;
                    default: std::cout << "Opcion invalida.\n";
                }
            }

            std::cout << "Película modificada!\n";

            // 🔹 Guardado automático
            if (guardadoAutomatico) guardarPeliculas(*this);
            return;
        }
    }
    std::cout << "ID no encontrado.\n";
}

void clsPelicula::darDeBaja(const std::string& id) {
    for (int i = 0; i < cantidad; i++) {
        if (peliculas[i].getId() == id) {
            peliculas[i].setActiva(false);
            std::cout << "Película dada de baja.\n";

            // 🔹 Guardado automático
            if (guardadoAutomatico) guardarPeliculas(*this);
            return;
        }
    }
    std::cout << "ID no encontrado.\n";
}

void clsPelicula::darDeAlta(const std::string& id) {
    for (int i = 0; i < cantidad; i++) {
        if (peliculas[i].getId() == id) {
            peliculas[i].setActiva(true);
            std::cout << "Película activada.\n";

            // 🔹 Guardado automático
            if (guardadoAutomatico) guardarPeliculas(*this);
            return;
        }
    }
    std::cout << "ID no encontrado.\n";
}

void clsPelicula::mostrarPeliculas() const {
    for (int i = 0; i < cantidad; i++) {
        const clsDataPeliculas& p = peliculas[i];
        std::cout << p.getId() << " - " << p.getNombre()
                  << " (" << p.getDuracion() << " min) - ";
        p.getFechaEstreno().mostrar();
        std::cout << " - " << (p.estaActiva() ? "Activa" : "Inactiva") << "\n";
    }
}

// ------------------- Métodos auxiliares -------------------

int clsPelicula::getCantidad() const { return cantidad; }
const clsDataPeliculas* clsPelicula::getPeliculas() const { return peliculas; }

void clsPelicula::agregarPelicula(const clsDataPeliculas& p) {
    if (cantidad == capacidad) redimensionar();
    peliculas[cantidad++] = p;
}

void clsPelicula::vaciarPeliculas() {
    cantidad = 0;
}

int clsPelicula::buscarPelicula(const std::string& id) const {
    for (int i = 0; i < cantidad; i++) {
        if (peliculas[i].getId() == id) {
            return i;
        }
    }
    return -1;  // No encontrada
}

/// ===============================================
/// Obtener duración de la película por índice
/// ===============================================
int clsPelicula::getDuracion(int index) const {
    if (index < 0 || index >= cantidad) {
        return -1;  // índice inválido
    }
    return peliculas[index].getDuracion();
}
