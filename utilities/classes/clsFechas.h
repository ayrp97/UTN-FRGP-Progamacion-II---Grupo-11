#pragma once
#include <string>


class clsFecha {
private:
    int dia;
    int mes;
    int anio;

    bool esBisiesto(int a) const;
    int diasEnMes(int m, int a) const;
    bool fechaValida(int d, int m, int a) const;

public:
    // Constructores
    clsFecha();  // Fecha por defecto (1/1/2000)
    clsFecha(int d, int m, int a);

    // Setters y Getters
    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // Métodos de utilidad
    void cargar();    // Cargar por consola con validación
    void mostrar() const;

    // Operaciones con fechas
    int comparar(const clsFecha& otra) const; // -1 si menor, 0 si igual, 1 si mayor
    void sumarDias(int cantidad);

    std::string toString() const;

};
