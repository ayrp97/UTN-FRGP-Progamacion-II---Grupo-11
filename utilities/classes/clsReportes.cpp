#include "../../mainHeader.h"
#include "clsReportes.h"
#include "../../functions/ventas/clsmaestroVentas.h"
#include "../rlutil.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdio>

using namespace std;

// ========================================================
// MENU PRINCIPAL DE REPORTES 📊
// ========================================================
void clsReportes::menuPrincipalReportes() {
    while (true) {
        rlutil::cls();
        fondoVentana();
        const char* opciones[] = {
            " RECAUDACIONES CONSOLIDADAS ",
            " REPORTES DE CANDY          ",
            " REPORTES DE PELICULAS      ",
            " REPORTES DE CLIENTES       ",
            " ANALISIS HORARIOS PICO     ",
            " VOLVER AL MENU PRINCIPAL   "
        };
        int op = menuInteractivo(opciones, 6, "CENTRO DE ESTADISTICAS", 46, 12);

        if (op == -1 || op == 5) return;

        switch(op) {
            case 0: menuRecaudaciones(); break;
            case 1: menuCandy(); break;
            case 2: menuPeliculas(); break;
            case 3: menuClientes(); break;
            case 4: reporteHorariosPico(); break;
        }
    }
}

// ========================================================
// SUBMENU 1: RECAUDACIONES 💰
// ========================================================
void clsReportes::menuRecaudaciones() {
    while(true) {
        rlutil::cls();
        fondoVentana();
        const char* ops[] = {
            " RECAUDACION DE HOY         ",
            " RANGO DE FECHAS            ",
            " HISTOGRAMA COMPARATIVO     ",
            " VOLVER                     "
        };
        int op = menuInteractivo(ops, 4, "INFORMES DE CAJA", 46, 14);
        if(op == -1 || op == 3) return;

        rlutil::cls();
        switch(op) {
            case 0: reporteDiario(); break;
            case 1: reportePorFechas(); break;
            case 2: histogramaMensual(); break;
        }
    }
}

void clsReportes::reporteDiario() {
    time_t t = time(0);
    tm* now = localtime(&t);
    int diaHoy = now->tm_mday;
    int mesHoy = now->tm_mon + 1;
    int anioHoy = now->tm_year + 1900;

    fondoVentana();
    rlutil::setColor(rlutil::YELLOW);
    rlutil::locate(40, 10); cout << "RECAUDACION DEL DIA (" << diaHoy << "/" << mesHoy << "/" << anioHoy << ")";

    FILE* p = fopen("ventas.dat", "rb");
    if (!p) {
        rlutil::locate(40, 12); cout << "No se pudo abrir el archivo de ventas.";
        rlutil::anykey(); return;
    }

    float total = 0;
    int cantidadVentas = 0;
    clsmaestroVenta ticket;

    while (fread(&ticket, sizeof(clsmaestroVenta), 1, p)) {
        if (ticket.getFecha().getDia() == diaHoy &&
            ticket.getFecha().getMes() == mesHoy &&
            ticket.getFecha().getAnio() == anioHoy) {

            total += ticket.getImporteTotal();
            cantidadVentas++;
        }
    }
    fclose(p);

    rlutil::setColor(rlutil::WHITE);
    rlutil::locate(40, 13); cout << "Tickets emitidos: " << cantidadVentas;
    rlutil::locate(40, 15);
    rlutil::setColor(rlutil::GREEN);
    cout << "TOTAL RECAUDADO: $ " << fixed << setprecision(2) << total;
    rlutil::anykey();
}

void clsReportes::reportePorFechas() {
    fondoVentana();
    int d1, m1, a1, d2, m2, a2;

    rlutil::setColor(rlutil::YELLOW);
    rlutil::locate(35, 8); cout << "REPORTE POR RANGO DE FECHAS";
    rlutil::setColor(rlutil::WHITE);

    rlutil::showcursor();
    rlutil::locate(35, 10); cout << "Fecha Inicio (D M A): "; cin >> d1 >> m1 >> a1;
    rlutil::locate(35, 12); cout << "Fecha Fin    (D M A): "; cin >> d2 >> m2 >> a2;
    rlutil::hidecursor();

    // Convertir a long para comparar facil (YYYYMMDD)
    long fechaDesde = (a1 * 10000) + (m1 * 100) + d1;
    long fechaHasta = (a2 * 10000) + (m2 * 100) + d2;

    FILE* p = fopen("ventas.dat", "rb");
    if (!p) return;

    float total = 0;
    int count = 0;
    clsmaestroVenta ticket;

    rlutil::cls();
    fondoVentana();
    rlutil::locate(20, 10);
    cout << "FECHA       HORA     TICKET       MONTO";
    cout << "\n                    ----------------------------------------";

    int y = 12;
    while (fread(&ticket, sizeof(clsmaestroVenta), 1, p)) {
        long fechaTicket = (ticket.getFecha().getAnio() * 10000) +
                           (ticket.getFecha().getMes() * 100) +
                           ticket.getFecha().getDia();

        if (fechaTicket >= fechaDesde && fechaTicket <= fechaHasta) {
            if (y < 25) { // Mostrar solo los primeros para no desbordar pantalla
                rlutil::locate(20, y++);
                cout << ticket.getFecha().toString() << "  "
                     << ticket.getHora() << "     "
                     << ticket.getIdVenta() << "    $ "
                     << ticket.getImporteTotal();
            }
            total += ticket.getImporteTotal();
            count++;
        }
    }
    fclose(p);

    rlutil::locate(20, y+2);
    rlutil::setColor(rlutil::GREEN);
    cout << "TOTAL PERIODO: $" << fixed << setprecision(2) << total << " (" << count << " ventas)";
    rlutil::anykey();
}

void clsReportes::histogramaMensual() {
    fondoVentana();
    rlutil::setColor(rlutil::YELLOW);
    rlutil::locate(35, 5); cout << "COMPARATIVA MENSUAL (Max 5 periodos)";

    int meses[5] = {0}, anios[5] = {0};
    float totales[5] = {0};
    int cantidadPeriodos = 0;

    // 1. PEDIR DATOS
    rlutil::showcursor();
    for(int i=0; i<5; i++) {
        rlutil::locate(30, 7 + i);
        rlutil::setColor(rlutil::WHITE);
        cout << "Periodo " << i+1 << " (MM AAAA) - 0 0 para terminar: ";
        cin >> meses[i] >> anios[i];
        if (meses[i] == 0) break;
        cantidadPeriodos++;
    }
    rlutil::hidecursor();

    if (cantidadPeriodos == 0) return;

    // 2. CALCULAR
    FILE* p = fopen("ventas.dat", "rb");
    if (p) {
        clsmaestroVenta ticket;
        while(fread(&ticket, sizeof(clsmaestroVenta), 1, p)) {
            int m = ticket.getFecha().getMes();
            int a = ticket.getFecha().getAnio();

            for(int i=0; i<cantidadPeriodos; i++) {
                if (meses[i] == m && anios[i] == a) {
                    totales[i] += ticket.getImporteTotal();
                }
            }
        }
        fclose(p);
    }

    // 3. DIBUJAR
    rlutil::cls();
    fondoVentana();

    float maxVal = 0;
    for(int i=0; i<cantidadPeriodos; i++) if(totales[i] > maxVal) maxVal = totales[i];
    if (maxVal == 0) maxVal = 1;

    int alturaMax = 14;
    int xInicio = 20;
    int yBase = 22;

    rlutil::locate(30, 4);
    rlutil::setColor(rlutil::YELLOW);
    cout << "HISTOGRAMA DE RECAUDACION";

    for(int i=0; i<cantidadPeriodos; i++) {
        int alturaBarra = (totales[i] * alturaMax) / maxVal;

        // Color dinámico (9=Azul, 10=Verde, 12=Rojo, etc)
        int color = (i % 5) + 9;
        rlutil::setBackgroundColor(color);

        // Dibujar barra
        for(int h=0; h<alturaBarra; h++) {
            for(int w=0; w<8; w++) { // Ancho 8
                rlutil::locate(xInicio + (i*14) + w, yBase - h);
                cout << " ";
            }
        }

        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);

        // Texto abajo (Fecha)
        rlutil::locate(xInicio + (i*14), yBase + 1);
        cout << meses[i] << "/" << anios[i];

        // Texto arriba (Monto)
        rlutil::locate(xInicio + (i*14), yBase - alturaBarra - 1);
        cout << "$" << (int)totales[i];
    }
    rlutil::anykey();
}


// ========================================================
// SUBMENU 2: CANDY 🍿
// ========================================================
void clsReportes::menuCandy() {
    while(true) {
        rlutil::cls();
        fondoVentana();
        const char* ops[] = {" RECAUDACION DIARIA ", " ARTICULOS MAS VENDIDOS ", " VOLVER "};
        int op = menuInteractivo(ops, 3, "REPORTES CANDY", 46, 14);
        if(op == -1 || op == 2) return;

        rlutil::cls();
        switch(op) {
            case 0: reporteDiario(); break; // Reutilizamos el diario (es general)
            case 1: rankingCandy(); break;
        }
    }
}

void clsReportes::rankingCandy() {
    // ARRAYS PARALELOS (Max 50 productos)
    char skus[50][10];
    char nombres[50][30];
    float recaudacion[50] = {0};
    int cantidad = 0;

    // 1. Cargar Articulos
    FILE* fC = fopen("candy.dat", "rb");
    if(!fC) return;
    clsArticulo art;
    while(fread(&art, sizeof(clsArticulo), 1, fC) && cantidad < 50) {
        if(art.estaActivo()) {
            strcpy(skus[cantidad], art.getSKU().c_str());
            strcpy(nombres[cantidad], art.getNombre().c_str());
            recaudacion[cantidad] = 0;
            cantidad++;
        }
    }
    fclose(fC);

    // 2. Sumar Ventas
    FILE* fV = fopen("ventas.dat", "rb");
    if(fV) {
        clsmaestroVenta t;
        while(fread(&t, sizeof(clsmaestroVenta), 1, fV)) {
            for(int i=0; i<t.getCantidadDetalles(); i++) {
                clsdetalleVenta d = t.leerDetalle(i);
                if(d.getCodigo().substr(0,3) == "SKU") {
                    // Buscar indice
                    for(int k=0; k<cantidad; k++) {
                        if(strcmp(skus[k], d.getCodigo().c_str()) == 0) {
                            recaudacion[k] += d.getSubTotal();
                            break;
                        }
                    }
                }
            }
        }
        fclose(fV);
    }

    // 3. Ordenar (Burbuja)
    for(int i=0; i<cantidad-1; i++) {
        for(int j=0; j<cantidad-i-1; j++) {
            if(recaudacion[j] < recaudacion[j+1]) {
                // Swap float
                float auxF = recaudacion[j]; recaudacion[j] = recaudacion[j+1]; recaudacion[j+1] = auxF;
                // Swap strings
                char auxS[50];
                strcpy(auxS, nombres[j]); strcpy(nombres[j], nombres[j+1]); strcpy(nombres[j+1], auxS);
                strcpy(auxS, skus[j]); strcpy(skus[j], skus[j+1]); strcpy(skus[j+1], auxS);
            }
        }
    }

    // 4. Mostrar
    fondoVentana();
    rlutil::locate(30, 5); cout << "TOP RECAUDACION CANDY";
    rlutil::locate(20, 8); cout << "PRODUCTO                        RECAUDACION";

    int limite = (cantidad > 10) ? 10 : cantidad;
    for(int i=0; i<limite; i++) {
        rlutil::locate(20, 10+i);
        cout << left << setw(30) << nombres[i] << "$ " << fixed << setprecision(2) << recaudacion[i];
    }
    rlutil::anykey();
}


// ========================================================
// SUBMENU 3: PELICULAS 🎬
// ========================================================
void clsReportes::menuPeliculas() {
    while(true) {
        rlutil::cls();
        fondoVentana();
        const char* ops[] = {" TOP 10 RECAUDACION ", " RECAUDACION POR GENERO ", " VOLVER "};
        int op = menuInteractivo(ops, 3, "REPORTES PELICULAS", 46, 14);
        if(op == -1 || op == 2) return;

        rlutil::cls();
        switch(op) {
            case 0: top10Peliculas(); break;
            case 1: recaudacionPorGenero(); break;
        }
    }
}

void clsReportes::top10Peliculas() {
    // Arrays paralelos
    char ids[100][10];
    char nombres[100][50];
    float rec[100] = {0};
    int cant = 0;

    FILE* fP = fopen("peliculas.dat", "rb");
    if(!fP) return;
    clsDataPeliculas p;
    while(fread(&p, sizeof(clsDataPeliculas), 1, fP) && cant < 100) {
        if(p.estaActiva()) {
            strcpy(ids[cant], p.getId().c_str());
            strcpy(nombres[cant], p.getNombre().c_str());
            cant++;
        }
    }
    fclose(fP);

    FILE* fV = fopen("ventas.dat", "rb");
    if(fV) {
        clsmaestroVenta t;
        while(fread(&t, sizeof(clsmaestroVenta), 1, fV)) {
            // ID Funcion: PE00001_SA... -> Extraemos PE00001
            string idFull = t.getIdFuncion();
            if(idFull.length() < 7) continue;
            string idPeli = idFull.substr(0, 7);

            for(int i=0; i<cant; i++) {
                if(strcmp(ids[i], idPeli.c_str()) == 0) {
                    rec[i] += t.getImporteTotal();
                    break;
                }
            }
        }
        fclose(fV);
    }

    // Ordenar
    for(int i=0; i<cant-1; i++) {
        for(int j=0; j<cant-i-1; j++) {
            if(rec[j] < rec[j+1]) {
                float auxR = rec[j]; rec[j] = rec[j+1]; rec[j+1] = auxR;
                char auxS[50];
                strcpy(auxS, nombres[j]); strcpy(nombres[j], nombres[j+1]); strcpy(nombres[j+1], auxS);
            }
        }
    }

    fondoVentana();
    rlutil::locate(35, 5); cout << "TOP 10 PELICULAS";
    rlutil::locate(20, 8); cout << "PELICULA                        RECAUDACION";

    int lim = (cant > 10) ? 10 : cant;
    for(int i=0; i<lim; i++) {
        rlutil::locate(20, 10+i);
        cout << left << setw(30) << nombres[i] << "$ " << fixed << setprecision(2) << rec[i];
    }
    rlutil::anykey();
}

void clsReportes::recaudacionPorGenero() {
    char generos[20][30];
    float recGen[20] = {0};
    int cantGen = 0;

    // 1. Descubrir generos y mapear peliculas
    struct PeliGenero { char idPeli[10]; int idxGenero; };
    PeliGenero mapa[100];
    int totalMap = 0;

    FILE* fP = fopen("peliculas.dat", "rb");
    if(!fP) return;
    clsDataPeliculas p;
    while(fread(&p, sizeof(clsDataPeliculas), 1, fP)) {
        if(!p.estaActiva()) continue;

        // Buscar si el genero ya existe
        int idx = -1;
        for(int i=0; i<cantGen; i++) {
            if(strcmp(generos[i], p.getGenero().c_str()) == 0) {
                idx = i; break;
            }
        }
        if(idx == -1 && cantGen < 20) {
            strcpy(generos[cantGen], p.getGenero().c_str());
            idx = cantGen++;
        }

        if(idx != -1) {
            strcpy(mapa[totalMap].idPeli, p.getId().c_str());
            mapa[totalMap].idxGenero = idx;
            totalMap++;
        }
    }
    fclose(fP);

    // 2. Sumar ventas
    FILE* fV = fopen("ventas.dat", "rb");
    if(fV) {
        clsmaestroVenta t;
        while(fread(&t, sizeof(clsmaestroVenta), 1, fV)) {
            string idPeli = t.getIdFuncion().substr(0, 7);
            for(int i=0; i<totalMap; i++) {
                if(strcmp(mapa[i].idPeli, idPeli.c_str()) == 0) {
                    recGen[mapa[i].idxGenero] += t.getImporteTotal();
                    break;
                }
            }
        }
        fclose(fV);
    }

    // 3. Ordenar
    for(int i=0; i<cantGen-1; i++) {
        for(int j=0; j<cantGen-i-1; j++) {
            if(recGen[j] < recGen[j+1]) {
                float aux = recGen[j]; recGen[j] = recGen[j+1]; recGen[j+1] = aux;
                char auxS[30];
                strcpy(auxS, generos[j]); strcpy(generos[j], generos[j+1]); strcpy(generos[j+1], auxS);
            }
        }
    }

    fondoVentana();
    rlutil::locate(35, 5); cout << "RECAUDACION POR GENERO";
    int y=8;
    for(int i=0; i<cantGen; i++) {
        rlutil::locate(20, y++);
        cout << left << setw(20) << generos[i] << "$ " << fixed << setprecision(2) << recGen[i];
    }
    rlutil::anykey();
}


// ========================================================
// SUBMENU 4: CLIENTES 👤
// ========================================================
void clsReportes::menuClientes() {
    while(true) {
        rlutil::cls();
        fondoVentana();
        const char* ops[] = {" TOP 10 POR COMPRAS ", " TOP 10 POR MONTO ", " VOLVER "};
        int op = menuInteractivo(ops, 3, "REPORTES CLIENTES", 46, 14);
        if(op == -1 || op == 2) return;

        rlutil::cls();
        switch(op) {
            case 0: topClientesVentas(); break;
            case 1: topClientesMonto(); break;
        }
    }
}

void clsReportes::topClientesVentas() {
    int dnis[200] = {0};
    int cant[200] = {0};
    int totalC = 0;

    FILE* f = fopen("ventas.dat", "rb");
    if(!f) return;
    clsmaestroVenta t;
    while(fread(&t, sizeof(clsmaestroVenta), 1, f)) {
        int dni = t.getDniCliente();
        if(dni == 0) continue;

        int idx = -1;
        for(int i=0; i<totalC; i++) {
            if(dnis[i] == dni) { idx = i; break; }
        }

        if(idx != -1) cant[idx]++;
        else if(totalC < 200) {
            dnis[totalC] = dni;
            cant[totalC] = 1;
            totalC++;
        }
    }
    fclose(f);

    // Ordenar por cantidad
    for(int i=0; i<totalC-1; i++) {
        for(int j=0; j<totalC-i-1; j++) {
            if(cant[j] < cant[j+1]) {
                int aux = cant[j]; cant[j] = cant[j+1]; cant[j+1] = aux;
                int auxD = dnis[j]; dnis[j] = dnis[j+1]; dnis[j+1] = auxD;
            }
        }
    }

    fondoVentana();
    rlutil::locate(30, 5); cout << "TOP CLIENTES (Por Tickets)";
    int lim = (totalC > 10) ? 10 : totalC;
    for(int i=0; i<lim; i++) {
        rlutil::locate(30, 8+i);
        cout << i+1 << ". DNI " << dnis[i] << " - " << cant[i] << " compras";
    }
    rlutil::anykey();
}

void clsReportes::topClientesMonto() {
    int dnis[200] = {0};
    float montos[200] = {0};
    int totalC = 0;

    FILE* f = fopen("ventas.dat", "rb");
    if(!f) return;
    clsmaestroVenta t;
    while(fread(&t, sizeof(clsmaestroVenta), 1, f)) {
        int dni = t.getDniCliente();
        if(dni == 0) continue;

        int idx = -1;
        for(int i=0; i<totalC; i++) {
            if(dnis[i] == dni) { idx = i; break; }
        }

        if(idx != -1) montos[idx] += t.getImporteTotal();
        else if(totalC < 200) {
            dnis[totalC] = dni;
            montos[totalC] = t.getImporteTotal();
            totalC++;
        }
    }
    fclose(f);

    // Ordenar por monto
    for(int i=0; i<totalC-1; i++) {
        for(int j=0; j<totalC-i-1; j++) {
            if(montos[j] < montos[j+1]) {
                float aux = montos[j]; montos[j] = montos[j+1]; montos[j+1] = aux;
                int auxD = dnis[j]; dnis[j] = dnis[j+1]; dnis[j+1] = auxD;
            }
        }
    }

    fondoVentana();
    rlutil::locate(30, 5); cout << "TOP CLIENTES (Por Monto)";
    int lim = (totalC > 10) ? 10 : totalC;
    for(int i=0; i<lim; i++) {
        rlutil::locate(30, 8+i);
        cout << i+1 << ". DNI " << dnis[i] << " - $ " << fixed << setprecision(2) << montos[i];
    }
    rlutil::anykey();
}

// ========================================================
// EXTRA: HORARIOS PICO 🕒
// ========================================================
void clsReportes::reporteHorariosPico() {
    int ventasHora[24] = {0};
    FILE* f = fopen("ventas.dat", "rb");
    if(!f) return;
    clsmaestroVenta t;
    while(fread(&t, sizeof(clsmaestroVenta), 1, f)) {
        int hora = t.getHora() / 100;
        if(hora >= 0 && hora < 24) ventasHora[hora]++;
    }
    fclose(f);

    fondoVentana();
    rlutil::locate(35, 4); cout << "HORARIOS PICO (VENTAS)";
    rlutil::setColor(rlutil::CYAN);

    // Grafico simple de barras horizontal
    for(int i=10; i<24; i++) { // De 10am a 12pm
        rlutil::locate(20, 6 + (i-10));
        cout << i << "hs: ";

        rlutil::setBackgroundColor(rlutil::RED);
        for(int b=0; b<ventasHora[i]; b++) cout << " "; // Una barra por venta

        rlutil::setBackgroundColor(rlutil::BLACK);
        cout << " (" << ventasHora[i] << ")";
    }
    rlutil::anykey();
}
