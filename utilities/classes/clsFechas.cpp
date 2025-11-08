#include <iostream>
#include "clsFechas.h"
using namespace std;

// --- Métodos privados ---
bool clsFecha::esBisiesto(int a) const {
    return (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
}

int clsFecha::diasEnMes(int m, int a) const {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return esBisiesto(a) ? 29 : 28;
        default: return 0;
    }
}

bool clsFecha::fechaValida(int d, int m, int a) const {
    if (a < 1900 || m < 1 || m > 12) return false;
    int maxDias = diasEnMes(m, a);
    return d >= 1 && d <= maxDias;
}

// --- Constructores ---
clsFecha::clsFecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
}

clsFecha::clsFecha(int d, int m, int a) {
    if (fechaValida(d, m, a)) {
        dia = d;
        mes = m;
        anio = a;
    } else {
        dia = 1;
        mes = 1;
        anio = 2000;
    }
}

// --- Setters ---
void clsFecha::setDia(int d) {
    if (fechaValida(d, mes, anio)) dia = d;
}

void clsFecha::setMes(int m) {
    if (fechaValida(dia, m, anio)) mes = m;
}

void clsFecha::setAnio(int a) {
    if (fechaValida(dia, mes, a)) anio = a;
}

// --- Getters ---
int clsFecha::getDia() const { return dia; }
int clsFecha::getMes() const { return mes; }
int clsFecha::getAnio() const { return anio; }

// --- Métodos públicos ---
void clsFecha::cargar() {
    int d, m, a;
    do {
        cout << "Ingrese dia: ";
        cin >> d;
        cout << "Ingrese mes: ";
        cin >> m;
        cout << "Ingrese anio: ";
        cin >> a;
        if (!fechaValida(d, m, a)) {
            cout << "Fecha invalida, intente nuevamente.\n";
        }
    } while (!fechaValida(d, m, a));

    dia = d;
    mes = m;
    anio = a;
}

void clsFecha::mostrar() const {
    cout << (dia < 10 ? "0" : "") << dia << "/"
         << (mes < 10 ? "0" : "") << mes << "/"
         << anio;
}

int clsFecha::comparar(const clsFecha& otra) const {
    if (anio < otra.anio) return -1;
    if (anio > otra.anio) return 1;
    if (mes < otra.mes) return -1;
    if (mes > otra.mes) return 1;
    if (dia < otra.dia) return -1;
    if (dia > otra.dia) return 1;
    return 0;
}

// --- Sumar días (simplificado, sin cronología negativa) ---
void clsFecha::sumarDias(int cantidad) {
    dia += cantidad;
    while (dia > diasEnMes(mes, anio)) {
        dia -= diasEnMes(mes, anio);
        mes++;
        if (mes > 12) {
            mes = 1;
            anio++;
        }
    }
}
