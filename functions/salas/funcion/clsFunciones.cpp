#include "clsFunciones.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "../../../rlutil.h"
using namespace std;

clsFunciones::clsFunciones(int maxFunciones) {
    capacidadMax = maxFunciones;
    cantidad = 0;
    funciones = new clsDataFuncion[capacidadMax];
}

clsFunciones::~clsFunciones() {
    delete[] funciones;
}

int clsFunciones::redondear10(int minutos) const {
    return ((minutos + 9) / 10) * 10;
}

string clsFunciones::generarIdFuncion(const string& idPelicula,
                                      const string& idSala,
                                      int horaInicio,
                                      int dia, int mes, int anio) const
{
    ostringstream oss;
    oss << idPelicula << "_"
        << idSala << "_FU"
        << setw(4) << setfill('0') << horaInicio << "_"
        << setw(2) << setfill('0') << dia
        << setw(2) << setfill('0') << mes
        << anio;

    return oss.str();
}

bool clsFunciones::verificarSolapamiento(const string& idSala,
                                         int dia, int mes, int anio,
                                         int horaInicio, int horaFin) const
{
    for (int i = 0; i < cantidad; i++) {
        const clsDataFuncion& f = funciones[i];

        if (f.getIdSala() == idSala &&
            f.getDia() == dia &&
            f.getMes() == mes &&
            f.getAnio() == anio)
        {
            if (horaInicio < f.getHoraFin() &&
                f.getHoraInicio() < horaFin)
                return true;
        }
    }
    return false;
}

void clsFunciones::crearFuncion(clsSala& salas, clsPelicula& peliculas)
{
    if (cantidad >= capacidadMax) {
        cout << "No hay mas espacio para funciones.\n";
        return;
    }

    string idSala, idPeli;
    int dia, mes, anio, hora;

    cout << "ID Sala: ";
    getline(cin, idSala);
    int posSala = salas.buscarSala(idSala);
    if (posSala == -1) { cout << "Sala no encontrada.\n"; return; }

    cout << "ID Pelicula: ";
    getline(cin, idPeli);
    int posPeli = peliculas.buscarPelicula(idPeli);
    if (posPeli == -1) { cout << "Pelicula no encontrada.\n"; return; }

    cout << "Fecha (DD MM AAAA): ";
    cin >> dia >> mes >> anio;
    cin.ignore();

    cout << "Hora inicio (HHMM): ";
    cin >> hora;
    cin.ignore();

    if (hora > 2400) {
        cout << "ERROR: No se puede iniciar después de las 00:00.\n";
        return;
    }

    const clsDataSalas& sala = salas.getSalas()[posSala];
    const clsDataPeliculas& peli = peliculas.getPeliculas()[posPeli];

    clsDataFuncion f;

    f.setIdSala(idSala);
    f.setIdPelicula(idPeli);
    f.setFecha(clsFecha(dia, mes, anio));
    f.setHoraInicio(hora);
    f.setDuracionPelicula(peli.getDuracion() + 10 + 20);
    f.setCapacidadSala(sala.getCapacidad());
    f.setActiva(true);

    int horaFin = f.getHoraFin();

    if (verificarSolapamiento(idSala, dia, mes, anio, hora, horaFin)) {
        cout << "ERROR: Se solapa con otra función.\n";
        return;
    }

    string idFuncion = generarIdFuncion(idPeli, idSala, hora, dia, mes, anio);
    f.setIdFuncion(idFuncion);

    funciones[cantidad++] = f;

    cout << "Funcion creada con ID: " << idFuncion << "\n";
}

void clsFunciones::crearFuncionesPorDia(clsSala& salas, clsPelicula& peliculas)
{
    string idSala, idPeli;
    int dia, mes, anio;

    cout << "ID Sala: ";
    getline(cin, idSala);
    int posSala = salas.buscarSala(idSala);
    if (posSala == -1) { cout << "Sala no encontrada.\n"; return; }

    cout << "ID Pelicula: ";
    getline(cin, idPeli);
    int posPeli = peliculas.buscarPelicula(idPeli);
    if (posPeli == -1) { cout << "Pelicula no encontrada.\n"; return; }

    cout << "Fecha (DD MM AAAA): ";
    cin >> dia >> mes >> anio;
    cin.ignore();

    const clsDataSalas& sala = salas.getSalas()[posSala];
    const clsDataPeliculas& peli = peliculas.getPeliculas()[posPeli];

    int duracion = peli.getDuracion() + 10 + 20;

    int inicioMin = 12 * 60;    // 12:00
    int limiteInicio = 24 * 60; // 00:00

    while (inicioMin <= limiteInicio) {

        int horaInicio = (inicioMin / 60) * 100 + (inicioMin % 60);

        clsDataFuncion f;
        f.setIdSala(idSala);
        f.setIdPelicula(idPeli);
        f.setFecha(clsFecha(dia, mes, anio));
        f.setHoraInicio(horaInicio);
        f.setDuracionPelicula(duracion);
        f.setCapacidadSala(sala.getCapacidad());
        f.setActiva(true);

        int horaFin = f.getHoraFin();

        if (!verificarSolapamiento(idSala, dia, mes, anio, horaInicio, horaFin)) {

            string idFuncion = generarIdFuncion(idPeli, idSala, horaInicio, dia, mes, anio);
            f.setIdFuncion(idFuncion);

            funciones[cantidad++] = f;

            cout << "   Creada: " << idFuncion << "\n";
        }

        int finMin = (horaFin / 100) * 60 + (horaFin % 100);
        inicioMin = redondear10(finMin);
    }
}

void clsFunciones::crearFuncionesPorMes(clsSala& salas, clsPelicula& peliculas)
{
    string idSala, idPeli;
    int mes, anio;

    cout << "ID Sala: ";
    getline(cin, idSala);
    int posSala = salas.buscarSala(idSala);
    if (posSala == -1) { cout << "Sala no encontrada.\n"; return; }

    cout << "ID Pelicula: ";
    getline(cin, idPeli);
    int posPeli = peliculas.buscarPelicula(idPeli);
    if (posPeli == -1) { cout << "Pelicula no encontrada.\n"; return; }

    cout << "Mes y Anio (MM AAAA): ";
    cin >> mes >> anio;
    cin.ignore();

    int diasMes = 31;
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) diasMes = 30;
    else if (mes == 2) diasMes = (anio % 4 == 0 ? 29 : 28);

    const clsDataSalas& sala = salas.getSalas()[posSala];
    const clsDataPeliculas& peli = peliculas.getPeliculas()[posPeli];

    int duracion = peli.getDuracion() + 10 + 20;

    cout << "Generando funciones para " << diasMes << " dias...\n";

    for (int dia = 1; dia <= diasMes; dia++)
    {
        int inicioMin = 12 * 60;    // 12:00
        int limiteInicio = 24 * 60; // 00:00

        while (inicioMin <= limiteInicio && cantidad < capacidadMax) {
            int horaInicio = (inicioMin / 60) * 100 + (inicioMin % 60);

            clsDataFuncion f;
            f.setIdSala(idSala);
            f.setIdPelicula(idPeli);
            f.setFecha(clsFecha(dia, mes, anio));
            f.setHoraInicio(horaInicio);
            f.setDuracionPelicula(duracion);
            f.setCapacidadSala(sala.getCapacidad());
            f.setActiva(true);

            int horaFin = f.getHoraFin();

            if (!verificarSolapamiento(idSala, dia, mes, anio, horaInicio, horaFin)) {
                string idFuncion = generarIdFuncion(idPeli, idSala, horaInicio, dia, mes, anio);
                f.setIdFuncion(idFuncion);

                funciones[cantidad++] = f;

                cout << "Dia " << dia << " -> Creada: " << idFuncion << "\n";
            }

            int finMin = (horaFin / 100) * 60 + (horaFin % 100);
            inicioMin = redondear10(finMin);
        }
    }

    cout << ">>> MES COMPLETO GENERADO <<<\n";
}

void clsFunciones::mostrarFunciones(const clsPelicula& gestorPeliculas) const
{
    if (cantidad == 0) {
        cout << "No hay funciones cargadas.\n";
        return;
    }

    rlutil::setColor(rlutil::YELLOW);
    
    cout << left << setw(35) << "ID FUNCION"
         << left << setw(40) << "PELICULA"
         << left << setw(15) << "FECHA"
         << left << setw(10) << "HORARIO"
         << left << setw(10) << "LIBRES"
         << endl;

    cout << string(106, '-') << endl; 
    rlutil::setColor(rlutil::WHITE);

    for (int i = 0; i < cantidad; i++) {
        const clsDataFuncion& f = funciones[i];

        string nombrePelicula = "DESCONOCIDO";
        int pos = gestorPeliculas.buscarPelicula(f.getIdPelicula());

        if (pos != -1) {
            nombrePelicula = gestorPeliculas.getPeliculas()[pos].getNombre();
        }


        int hora = f.getHoraInicio();
        string horaStr = to_string(hora / 100) + ":" + (hora % 100 < 10 ? "0" : "") + to_string(hora % 100);

        cout << left << setw(35) << f.getIdFuncion()
             << left << setw(40) << nombrePelicula.substr(0, 24) 
             << left << setw(15) << f.getFecha().toString()
             << left << setw(10) << horaStr
             << left << setw(10) << f.getAsientosDisponibles()
             << "\n";
    }
}

int clsFunciones::buscarFuncion(const string& id) const {
    for (int i = 0; i < cantidad; i++)
        if (funciones[i].getIdFuncion() == id)
            return i;
    return -1;
}

void clsFunciones::desactivarFuncion(const string& id)
{
    int pos = buscarFuncion(id);
    if (pos == -1) { cout << "Funcion no encontrada.\n"; return; }

    funciones[pos].setActiva(false);
}

void clsFunciones::mostrarFuncionesPorSala(const string& idSala, const clsPelicula& gestorPeliculas) const
{
    rlutil::setColor(rlutil::YELLOW);

    cout << left << setw(30) << "ID FUNCION"
         << left << setw(25) << "PELICULA"
         << left << setw(15) << "FECHA"
         << left << setw(10) << "HORARIO"
         << endl;
    cout << string(80, '-') << endl;
    rlutil::setColor(rlutil::WHITE);

    bool hayFunciones = false;

    for (int i = 0; i < cantidad; i++) {
       
        if (funciones[i].getIdSala() == idSala) {

            hayFunciones = true;
            const clsDataFuncion& f = funciones[i];

            string nombrePelicula = "DESCONOCIDO";
            int pos = gestorPeliculas.buscarPelicula(f.getIdPelicula());
            if (pos != -1) {
                nombrePelicula = gestorPeliculas.getPeliculas()[pos].getNombre();
            }

            int hora = f.getHoraInicio();
            string horaStr = to_string(hora / 100) + ":" + (hora % 100 < 10 ? "0" : "") + to_string(hora % 100);

            cout << left << setw(30) << f.getIdFuncion()
                 << left << setw(25) << nombrePelicula
                 << left << setw(15) << f.getFecha().toString()
                 << left << setw(10) << horaStr
                 << "\n";
        }
    }

    if (!hayFunciones) {
        cout << "\nNo se encontraron funciones para la sala: " << idSala << "\n";
    }
}

void clsFunciones::mostrarFuncionesPorFecha(int dia, int mes, int anio, const clsPelicula& gestorPeliculas) const
{
    rlutil::setColor(rlutil::YELLOW);

    cout << left << setw(30) << "ID FUNCION"
         << left << setw(25) << "PELICULA"
         << left << setw(15) << "FECHA"
         << left << setw(10) << "HORARIO"
         << endl;
    cout << string(80, '-') << endl;
    rlutil::setColor(rlutil::WHITE);

    bool hayFunciones = false;

    for (int i = 0; i < cantidad; i++) {
        if (funciones[i].getDia() == dia &&
            funciones[i].getMes() == mes &&
            funciones[i].getAnio() == anio)
        {
            hayFunciones = true;
            const clsDataFuncion& f = funciones[i];

            string nombrePelicula = "DESCONOCIDO";
            int pos = gestorPeliculas.buscarPelicula(f.getIdPelicula());
            if (pos != -1) {
                nombrePelicula = gestorPeliculas.getPeliculas()[pos].getNombre();
            }

            int hora = f.getHoraInicio();
            string horaStr = to_string(hora / 100) + ":" + (hora % 100 < 10 ? "0" : "") + to_string(hora % 100);

            cout << left << setw(30) << f.getIdFuncion()
                 << left << setw(25) << nombrePelicula
                 << left << setw(15) << f.getFecha().toString()
                 << left << setw(10) << horaStr
                 << "\n";
        }
    }

    if (!hayFunciones) {
        cout << "\nNo hay funciones programadas para la fecha: "
             << dia << "/" << mes << "/" << anio << "\n";
    }
}

bool clsFunciones::guardarFunciones(const char* nombreArchivo) const
{
    FILE* p = fopen(nombreArchivo, "wb");
    if (p == nullptr) return false;

    fwrite(&cantidad, sizeof(int), 1, p);
    fwrite(funciones, sizeof(clsDataFuncion), cantidad, p);

    fclose(p);
    return true;
}

bool clsFunciones::cargarFunciones(const char* nombreArchivo)
{
    FILE* p = fopen(nombreArchivo, "rb");
    if (p == nullptr) return false;

    fread(&cantidad, sizeof(int), 1, p);

    if (cantidad > capacidadMax) {
        fclose(p);
        return false;
    }

    fread(funciones, sizeof(clsDataFuncion), cantidad, p);

    fclose(p);
    return true;
}

int clsFunciones::getCantidad() const { return cantidad; }

const clsDataFuncion* clsFunciones::getFunciones() const { return funciones; }

bool clsFunciones::restarCapacidad(const std::string& idFuncion, int cantidad) {
    int pos = buscarFuncion(idFuncion); 

    if (pos == -1) return false; 

    int actuales = funciones[pos].getAsientosDisponibles();
    
    if (actuales < cantidad) return false; 

    funciones[pos].setAsientosDisponibles(actuales - cantidad);

    return guardarFunciones("funciones.dat");
}
