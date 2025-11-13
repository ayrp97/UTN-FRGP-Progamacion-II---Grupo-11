#include "clsFunciones.h"
#include <iostream>
#include <iomanip>
using namespace std;

// =====================================================
// CONSTRUCTOR / DESTRUCTOR
// =====================================================

clsFunciones::clsFunciones(int maxFunciones) {
    capacidadMax = maxFunciones;
    cantidad = 0;
    funciones = new clsDataFuncion[capacidadMax];
}

clsFunciones::~clsFunciones() {
    delete[] funciones;
}

// =====================================================
// Redondear minutos a próximo múltiplo de 10
// =====================================================

int clsFunciones::redondear10(int minutos) const {
    return ((minutos + 9) / 10) * 10;
}

// =====================================================
// Generar ID de función
// Formato: PE00001_SA00001_FU1730
// =====================================================

string clsFunciones::generarIdFuncion(const string& idPelicula,
                                      const string& idSala,
                                      int horaInicio) const
{
    ostringstream oss;
    oss << idPelicula << "_"
        << idSala << "_FU"
        << setw(4) << setfill('0') << horaInicio;

    return oss.str();
}

// =====================================================
// Verificar solapamiento
// =====================================================

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

// =====================================================
// Crear función manual
// =====================================================

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

    string idFuncion = generarIdFuncion(idPeli, idSala, hora);
    f.setIdFuncion(idFuncion);

    funciones[cantidad++] = f;

    cout << "Funcion creada con ID: " << idFuncion << "\n";
}

// =====================================================
// Crear funciones por DIA
// =====================================================

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

            string idFuncion = generarIdFuncion(idPeli, idSala, horaInicio);
            f.setIdFuncion(idFuncion);

            funciones[cantidad++] = f;

            cout << "   Creada: " << idFuncion << "\n";
        }

        int finMin = (horaFin / 100) * 60 + (horaFin % 100);
        inicioMin = redondear10(finMin);
    }
}

// =====================================================
// Crear funciones por MES COMPLETO
// =====================================================

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

    cout << "Generando funciones para " << diasMes << " dias...\n";

    for (int dia = 1; dia <= diasMes; dia++)
    {
        crearFuncionesPorDia(salas, peliculas);
    }

    cout << ">>> MES COMPLETO GENERADO <<<\n";
}

// =====================================================
// Mostrar todas las funciones
// =====================================================

void clsFunciones::mostrarFunciones() const
{
    if (cantidad == 0) {
        cout << "No hay funciones cargadas.\n";
        return;
    }

    for (int i = 0; i < cantidad; i++) {
        const clsDataFuncion& f = funciones[i];

        cout << f.getIdFuncion()
             << " | Sala: " << f.getIdSala()
             << " | Pelicula: " << f.getIdPelicula()
             << " | Fecha: " << f.getDia() << "/" << f.getMes() << "/" << f.getAnio()
             << " | Inicio: " << f.getHoraInicio()
             << " | Fin: " << f.getHoraFin()
             << (f.estaActiva() ? " | Activa" : " | Inactiva")
             << "\n";
    }
}

// =====================================================
// Buscar función
// =====================================================

int clsFunciones::buscarFuncion(const string& id) const {
    for (int i = 0; i < cantidad; i++)
        if (funciones[i].getIdFuncion() == id)
            return i;
    return -1;
}

// =====================================================
// Desactivar función
// =====================================================

void clsFunciones::desactivarFuncion(const string& id)
{
    int pos = buscarFuncion(id);
    if (pos == -1) { cout << "Funcion no encontrada.\n"; return; }

    funciones[pos].setActiva(false);
}

// =====================================================
// Mostrar funciones por sala
// =====================================================

void clsFunciones::mostrarFuncionesPorSala(const string& idSala) const
{
    for (int i = 0; i < cantidad; i++)
        if (funciones[i].getIdSala() == idSala)
            cout << funciones[i].getIdFuncion() << "\n";
}

// =====================================================
// Mostrar funciones por fecha
// =====================================================

void clsFunciones::mostrarFuncionesPorFecha(int dia, int mes, int anio) const
{
    for (int i = 0; i < cantidad; i++)
        if (funciones[i].getDia() == dia &&
            funciones[i].getMes() == mes &&
            funciones[i].getAnio() == anio)
            cout << funciones[i].getIdFuncion() << "\n";
}

// =====================================================
// Persistencia: Guardar
// =====================================================

bool clsFunciones::guardarFunciones(const char* nombreArchivo) const
{
    FILE* p = fopen(nombreArchivo, "wb");
    if (p == nullptr) return false;

    fwrite(&cantidad, sizeof(int), 1, p);
    fwrite(funciones, sizeof(clsDataFuncion), cantidad, p);

    fclose(p);
    return true;
}

// =====================================================
// Persistencia: Cargar
// =====================================================

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

// =====================================================
// Getters
// =====================================================

int clsFunciones::getCantidad() const { return cantidad; }
const clsDataFuncion* clsFunciones::getFunciones() const { return funciones; }