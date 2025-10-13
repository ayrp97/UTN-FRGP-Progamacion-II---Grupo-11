#include "clsPeliculas.h"
#include <iostream>
#include <iomanip>

//PRIVATE

// Ejemplo simple de generar ID
std::string clsPelicula::generarId() {
    static int contador = 1; // Se puede reemplazar por algo más persistente
    // Formato AAAAMMXXXX **CONFIGURADOR DE AÑO Y MES**
    int year = 2025;
    int month = 01;
    std::ostringstream oss;
    oss << year << std::setw(2) << std::setfill('0') << month
        << std::setw(4) << std::setfill('0') << contador++;
    return oss.str();
}

//PUBLIC

void clsPelicula::cargarNuevaPelicula() {
    clsDataPeliculas p;
    p.setId(generarId());

    std::string temp;
    int dur;
    std::cout << "Nombre: "; std::getline(std::cin, temp); p.setNombre(temp);
    std::cout << "Duracion (minutos): "; std::cin >> dur; p.setDuracion(dur); std::cin.ignore();
    std::cout << "Genero: "; std::getline(std::cin, temp); p.setGenero(temp);
    std::cout << "Clasificacion (ATP, +16, +18): "; std::getline(std::cin, temp); p.setClasificacion(temp);
    std::cout << "Director: "; std::getline(std::cin, temp); p.setDirector(temp);
    // Fecha de estreno /* pendiente */
    std::cout << "Idiomas disponibles: "; std::getline(std::cin, temp); p.setIdiomas(temp);
    std::cout << "Formato de proyeccion: "; std::getline(std::cin, temp); p.setFormatos(temp);

    p.setActiva(true); // por defecto la película queda activa
    peliculas.push_back(p);

    // Registrar movimiento /* pendiente */
    std::cout << "Película cargada con ID: " << p.getId() << "\n";
}

void clsPelicula::modificarPelicula(const std::string& id) {
    for (auto& p : peliculas) {
        if (p.getId() == id) {
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
                // std::cout << "8. Fecha de estreno (pendiente)\n";
                std::cout << "9. Salir\n";
                std::cout << "Ingrese la opcion a modificar: ";
                std::cin >> opcion;
                std::cin.ignore(); // limpiar buffer

                std::string temp;
                int dur;

                switch (opcion) {
                    case 1:
                        std::cout << "Nuevo Nombre: "; std::getline(std::cin, temp); 
                        if (!temp.empty()) p.setNombre(temp);
                        break;
                    case 2:
                        std::cout << "Nueva Duracion (min): "; std::cin >> dur; std::cin.ignore();
                        p.setDuracion(dur);
                        break;
                    case 3:
                        std::cout << "Nuevo Genero: "; std::getline(std::cin, temp); 
                        if (!temp.empty()) p.setGenero(temp);
                        break;
                    case 4:
                        std::cout << "Nueva Clasificacion (ATP, +16, +18): "; std::getline(std::cin, temp);
                        if (!temp.empty()) p.setClasificacion(temp);
                        break;
                    case 5:
                        std::cout << "Nuevo Director: "; std::getline(std::cin, temp);
                        if (!temp.empty()) p.setDirector(temp);
                        break;
                    case 6:
                        std::cout << "Nuevos Idiomas: "; std::getline(std::cin, temp);
                        if (!temp.empty()) p.setIdiomas(temp);
                        break;
                    case 7:
                        std::cout << "Nuevo Formato: "; std::getline(std::cin, temp);
                        if (!temp.empty()) p.setFormatos(temp);
                        break;
                    case 9:
                        std::cout << "Saliendo del menu de modificacion...\n";
                        break;
                    default:
                        std::cout << "Opcion invalida.\n";
                }
            }
            std::cout << "Película modificada!\n";
            return;
        }
    }
    std::cout << "ID no encontrado.\n";
}

void clsPelicula::darDeBaja(const std::string& id) {
    for (auto& p : peliculas) {
        if (p.getId() == id) {
            p.setActiva(false);
            std::cout << "Película dada de baja.\n";
            return;
        }
    }
    std::cout << "ID no encontrado.\n";
}

void clsPelicula::darDeAlta(const std::string& id) {
    for (auto& p : peliculas) {
        if (p.getId() == id) {
            p.setActiva(true);
            std::cout << "Película activada.\n";
            return;
        }
    }
    std::cout << "ID no encontrado.\n";
}

void clsPelicula::mostrarPeliculas() const {
    for (const auto& p : peliculas) {
        std::cout << p.getId() << " - " << p.getNombre() 
                  << " (" << p.getDuracion() << " min) - " 
                  << (p.estaActiva() ? "Activa" : "Inactiva") << "\n";
    }
}
