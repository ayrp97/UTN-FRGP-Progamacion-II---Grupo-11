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

    clsFecha();
    clsFecha(int d, int m, int a);

    void setDia(int d);
    void setMes(int m);
    void setAnio(int a);

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    void cargar();
    void mostrar() const;

    int comparar(const clsFecha& otra) const;
    void sumarDias(int cantidad);

    std::string toString() const;

};
