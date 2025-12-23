#include <iostream>
#include <string>

void menuGuardar(bool& binario, bool& csv, bool& guardar, bool& guardadoAutomatico) {
    int opcion = 0;
    while (true) {
        std::cout << "\n--- Menú de Guardado ---\n";
        std::cout << "1. Guardar en archivo binario (" << (binario ? "Si" : "No") << ")\n";
        std::cout << "2. Guardar en archivo CSV (" << (csv ? "Si" : "No") << ")\n";
        std::cout << "3. Guardar (" << (guardar ? "Si" : "No") << ")\n";
        std::cout << "4. Guardado automático (" << (guardadoAutomatico ? "Si" : "No") << ")\n";
        std::cout << "5. Salir sin guardar cambios\n";
        std::cout << "6. Confirmar y salir\n";
        std::cout << "Ingrese la opción a modificar: ";
        std::cin >> opcion;
        std::cin.ignore();  // limpiar buffer

        switch (opcion) {
            case 1:
                binario = !binario;
                std::cout << "Ahora Guardar en binario: " << (binario ? "Si" : "No") << "\n";
                break;
            case 2:
                csv = !csv;
                std::cout << "Ahora Guardar en CSV: " << (csv ? "Si" : "No") << "\n";
                break;
            case 3:
                guardar = !guardar;
                std::cout << "Ahora Guardar: " << (guardar ? "Si" : "No") << "\n";
                break;
            case 4:
                guardadoAutomatico = !guardadoAutomatico;
                std::cout << "Ahora Guardado automático: " << (guardadoAutomatico ? "Si" : "No") << "\n";
                break;
            case 5:
                std::cout << "Saliendo sin guardar cambios...\n";
                return;  // sale del menú sin modificar nada
            case 6:
                std::cout << "Opciones confirmadas. Saliendo...\n";
                return;  // sale del menú con los cambios
            default:
                std::cout << "Opción inválida. Intente nuevamente.\n";
        }
    }
}
