#pragma once
#include <string>
#include "clsdetalleVentas.h"         // Incluimos la clase hija
#include "../../utilities/classes/clsFechas.h" // Asegurate que la ruta sea correcta

class clsmaestroVenta {
private:
    char idVenta[10];           // Número de ticket
    int dniCliente;        // DNI del comprador
    clsFecha fecha;        // Fecha de la operación
    int hora;              // HHMM
    
    // AQUÍ ESTÁ LA MAGIA DE LA COMPOSICIÓN:
    // El maestro "contiene" hasta 20 detalles adentro.
    clsdetalleVenta detalles[20]; 
    int cantidadDetalles;  // Contador de cuántos items cargamos (0 a 20)
    
    float importeTotal;    // Suma total
    bool activa;           // true = válida, false = anulada

public:
    clsmaestroVenta();

    // Setters de Cabecera
    void setIdVenta(const std::string& id);
    void setDniCliente(int dni);
    void setFecha(const clsFecha& f);
    void setHora(int h);
    void setActiva(bool a);

    // Getters de Cabecera
    std::string getIdVenta() const;
    int getDniCliente() const;
    clsFecha getFecha() const;
    int getHora() const;
    float getImporteTotal() const;
    bool estaActiva() const;

    // --- MÉTODOS PARA MANEJAR EL DETALLE ---
    
    // Agrega un item al array y suma el precio al total automáticamente
    bool agregarDetalle(const clsdetalleVenta& item);
    
    // Devuelve cuántos items tiene este ticket
    int getCantidadDetalles() const;
    
    // Devuelve un detalle específico (para leerlo o imprimirlo)
    clsdetalleVenta leerDetalle(int indice) const;
};