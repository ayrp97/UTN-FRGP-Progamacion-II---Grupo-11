#include "clsVentas.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "../../rlutil.h"
#include "../../mainHeader.h"

using namespace std;

// ========================================================
// GENERADOR DE ID (Autonumérico)
// ========================================================
string clsVentas::generarIdVenta() {
    int contador = 1;
    ifstream in(ARCHIVO_ID_VENTAS);
    if (in.is_open()) {
        in >> contador;
        in.close();
    }

    // Guardamos el siguiente número para la próxima
    ofstream out(ARCHIVO_ID_VENTAS);
    out << contador + 1;
    out.close();

    // Formateamos: "VE" + 5 dígitos
    ostringstream oss;
    oss << "VE" << setw(5) << setfill('0') << contador;

    return oss.str();
}

// ========================================================
// VALIDACIÓN DE HORARIO
// ========================================================
bool clsVentas::esFuncionFutura(const clsDataFuncion& f) {
    time_t t = time(0);
    tm* now = localtime(&t);

    int anioAct = now->tm_year + 1900;
    int mesAct = now->tm_mon + 1;
    int diaAct = now->tm_mday;
    int horaAct = (now->tm_hour * 100) + now->tm_min;

    if (f.getAnio() > anioAct) return true;
    if (f.getAnio() < anioAct) return false;

    if (f.getMes() > mesAct) return true;
    if (f.getMes() < mesAct) return false;

    if (f.getDia() > diaAct) return true;
    if (f.getDia() < diaAct) return false;

    // Si es hoy, comparamos hora
    if (f.getHoraInicio() > horaAct) return true;

    return false;
}

// ========================================================
// AUXILIAR: SELECCIÓN VISUAL INTERACTIVA (FLECHAS) 🎮
// ========================================================
int seleccionarFuncionUI(clsFunciones& gestorFunc,
                         clsPelicula& gestorPeli,
                         clsSala& gestorSala,
                         int filtroModo, int dia, int mes, int anio)
{
    // ----------------------------------------------------
    // 1. PREPARACIÓN DE DATOS
    // ----------------------------------------------------
    int indicesReales[100];
    int totalOpciones = 0;

    // FECHA DE HOY
    time_t t = time(0);
    tm* now = localtime(&t);
    int anioHoy = now->tm_year + 1900;
    int mesHoy = now->tm_mon + 1;
    int diaHoy = now->tm_mday;
    int horaActual = (now->tm_hour * 100) + now->tm_min;

    // FECHA DE MAÑANA (Truco: Sumamos 24hs en segundos)
    time_t t_manana = t + (24 * 60 * 60);
    tm* tm_manana = localtime(&t_manana);
    int anioManana = tm_manana->tm_year + 1900;
    int mesManana = tm_manana->tm_mon + 1;
    int diaManana = tm_manana->tm_mday;

    for (int i = 0; i < gestorFunc.getCantidad(); i++) {
        if (totalOpciones >= 100) break;

        const clsDataFuncion& f = gestorFunc.getFunciones()[i];
        if (!f.estaActiva()) continue;

        bool incluir = false;

        if (filtroModo == 1) { // VENTA RAPIDA: Solo HOY y MAÑANA

            bool esHoy = (f.getDia() == diaHoy && f.getMes() == mesHoy && f.getAnio() == anioHoy);
            bool esManana = (f.getDia() == diaManana && f.getMes() == mesManana && f.getAnio() == anioManana);

            if (esHoy || esManana) incluir = true;
        }
        else if (filtroModo == 2) { // FECHA EXACTA
            if (f.getDia() == dia && f.getMes() == mes && f.getAnio() == anio) incluir = true;
        }

        // Filtro de horario: Si es HOY, ocultamos las funciones que ya pasaron
        if (incluir && f.getDia() == diaHoy && f.getMes() == mesHoy && f.getAnio() == anioHoy) {
             if (f.getHoraInicio() < horaActual) incluir = false;
        }

        if (incluir) {
            indicesReales[totalOpciones] = i;
            totalOpciones++;
        }
    }

    if (totalOpciones == 0) {
        rlutil::cls();
        rlutil::setColor(rlutil::RED);
        cout << "\nNo hay funciones disponibles con ese criterio.\n";
        rlutil::setColor(rlutil::WHITE);
        rlutil::anykey();
        return -1;
    }
    // ----------------------------------------------------
    // 2. BUCLE VISUAL (Navegación)
    // ----------------------------------------------------
    int seleccion = 0;
    bool elegido = false;

    while (!elegido) {
        rlutil::cls();
        rlutil::hidecursor();

        // --- CABECERA ---
        rlutil::setColor(rlutil::YELLOW);
        if (filtroModo == 1) cout << "=== VENTA RAPIDA (HOY Y MANIANA) ===\n";
        else cout << "=== SELECCION POR FECHA (" << dia << "/" << mes << "/" << anio << ") ===\n";

        rlutil::setColor(rlutil::CYAN);
        cout << left << setw(18) << " FECHA/HORA"
             << left << setw(25) << "PELICULA"
             << left << setw(20) << "SALA" << endl;
        cout << string(65, '-') << endl;

        // --- LISTADO ---
        for (int i = 0; i < totalOpciones; i++) {
            int idxReal = indicesReales[i];
            const clsDataFuncion& f = gestorFunc.getFunciones()[idxReal];

            // Recuperar nombres
            string nombrePeli = "Desconocida";
            int posPeli = gestorPeli.buscarPelicula(f.getIdPelicula());
            if (posPeli != -1) nombrePeli = gestorPeli.getPeliculas()[posPeli].getNombre();

            string nombreSala = f.getIdSala();
            int posSala = gestorSala.buscarSala(f.getIdSala());
            if (posSala != -1) nombreSala = gestorSala.getSalas()[posSala].getTipoSala();

            // Formatear hora
            int h = f.getHoraInicio();
            string horaStr = to_string(h / 100) + ":" + (h % 100 < 10 ? "0" : "") + to_string(h % 100);
            string fechaHora = f.getFecha().toString() + " " + horaStr;

            // --- ARMADO DE LINEA ---
            stringstream ss;
            ss << " " << left << setw(17) << fechaHora
               << left << setw(25) << nombrePeli.substr(0, 24)
               << left << setw(20) << nombreSala;

            string linea = ss.str();

            // --- IMPRESION ---
            if (i == seleccion) {
                rlutil::setBackgroundColor(rlutil::BLUE);
                rlutil::setColor(rlutil::WHITE);
                cout << linea;
                rlutil::setBackgroundColor(rlutil::BLACK);
                cout << endl;
            } else {
                rlutil::setBackgroundColor(rlutil::BLACK);
                rlutil::setColor(rlutil::GREY);
                cout << linea << endl;
            }
        }

        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);

        // --- CONTROL ---
        int key = rlutil::getkey();
        switch (key) {
            case 14: // ARRIBA
                PlaySound(TEXT("sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                seleccion--;
                if (seleccion < 0) seleccion = totalOpciones - 1;
                break;
            case 15: // ABAJO
                PlaySound(TEXT("sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                seleccion++;
                if (seleccion >= totalOpciones) seleccion = 0;
                break;
            case 1: // ENTER
                PlaySound(TEXT("sounds/keySoundStrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
                return indicesReales[seleccion];
                break;
            case 0: // ESCAPE
                return -1;
                break;
        }
    }
    return -1;
}

int menuModoVenta() {
    int opcion = 0;

    while (true) {
        rlutil::cls();
        fondoVentana(); // Dibuja el marco

        rlutil::setColor(rlutil::YELLOW);
        rlutil::locate(48, 10);
        cout << "=== MODO DE VENTA ===";

        // Opciones
        const char* opciones[] = {
            " VENTA RAPIDA (HOY Y MAÑANA)    ",
            " BUSCAR POR FECHA ESPECIFICA    ",
            " VOLVER                         "
        };

        rlutil::setColor(rlutil::WHITE);

        for (int i = 0; i < 3; i++) {
            if (i == opcion) {
                rlutil::setBackgroundColor(rlutil::BLUE);
                rlutil::locate(43, 13 + i);
                cout << " " << opciones[i] << " "; // Espacios para el resaltado
            } else {
                rlutil::setBackgroundColor(rlutil::BLACK);
                rlutil::locate(43, 13 + i);
                cout << " " << opciones[i] << " ";
            }
        }
        rlutil::setBackgroundColor(rlutil::BLACK);

        // Puntero Visual
        rlutil::locate(40, 13 + opcion);
        cout << (char)175;

        // Control
        int key = rlutil::getkey();
        switch (key) {
            case 14: // ARRIBA
                PlaySound(TEXT("sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                opcion--;
                if (opcion < 0) opcion = 2;
                break;
            case 15: // ABAJO
                PlaySound(TEXT("sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                opcion++;
                if (opcion > 2) opcion = 0;
                break;
            case 1: // ENTER
                PlaySound(TEXT("sounds/keySoundStrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
                // Mapeamos el índice (0,1,2) a tu lógica (1,2,0)
                if (opcion == 0) return 1; // Venta Rápida
                if (opcion == 1) return 2; // Fecha Específica
                return 0; // Cancelar
                break;
            case 0: // ESCAPE
                return 0;
                break;
        }
    }
}

// ========================================================
// AUXILIAR: SELECCIÓN DE CANDY CON VISUALIZACIÓN DE CARRITO 🛒
// ========================================================
int seleccionarCandyUI(clsCandy& gestorCandy, const clsmaestroVenta& ticket) {
    // 1. CARGAMOS PRODUCTOS EN MEMORIA
    int indicesReales[100];
    int totalOpciones = 0;
    
    // Asumimos tope 100 productos o fin de archivo
    for (int i = 0; i < 100; i++) { 
        clsArticulo art = gestorCandy.leerArticulo(i);
        if (art.getPrecio() == 0 && art.getNombre() == "") {
            if (i > 20 && gestorCandy.leerArticulo(i+1).getPrecio() == 0) break; 
            continue; 
        }
        
        if (art.estaActivo()) {
            indicesReales[totalOpciones] = i;
            totalOpciones++;
        }
    }

    int seleccion = 0;
    
    while (true) {
        rlutil::cls();
        rlutil::hidecursor();

        // ------------------------------------------------
        // SECCIÓN 1: LISTA DE PRODUCTOS (ARRIBA)
        // ------------------------------------------------
        rlutil::setColor(rlutil::YELLOW);
        cout << "=== CANDY BAR - SELECCIONE PRODUCTOS ===\n";
        
        rlutil::setColor(rlutil::CYAN);
        cout << left << setw(8) << "STOCK"  // Un poco mas ancho para "AGOTADO"
             << left << setw(30) << "DESCRIPCION"
             << left << setw(10) << "PRECIO" << endl;
        cout << string(50, '-') << endl;

        for (int i = 0; i <= totalOpciones; i++) { 
            
            if (i == seleccion) {
                rlutil::setBackgroundColor(rlutil::BLUE);
                rlutil::setColor(rlutil::WHITE);
            } else {
                rlutil::setBackgroundColor(rlutil::BLACK);
                rlutil::setColor(rlutil::GREY);
            }

            if (i == totalOpciones) {
                cout << "  " << left << setw(44) << "<< FINALIZAR SELECCION >>" << endl;
            } else {
                // Producto Real
                clsArticulo art = gestorCandy.leerArticulo(indicesReales[i]);
                
                // --- LÓGICA DE STOCK DINÁMICO ---
                int stockReal = art.getStock();
                int enCarrito = 0;
                
                // Recorremos el ticket actual para ver cuántos ya tengo de este producto
                for(int k=0; k < ticket.getCantidadDetalles(); k++) {
                    // Comparamos SKU
                    if (ticket.leerDetalle(k).getCodigo() == art.getSKU()) {
                        enCarrito += ticket.leerDetalle(k).getCantidad();
                    }
                }
                
                int stockDisponible = stockReal - enCarrito;
                if (stockDisponible < 0) stockDisponible = 0; // Por seguridad

                // Mostramos el stock calculado, no el real
                string stockStr = to_string(stockDisponible);
                if (stockDisponible == 0) stockStr = "0"; // Opcional: "X" para agotado

                cout << " " << left << setw(8) << stockStr
                     << left << setw(30) << art.getNombre().substr(0,29)
                     << "$ " << art.getPrecio() << endl;
            }
            rlutil::setBackgroundColor(rlutil::BLACK);
        }

        // ------------------------------------------------
        // SECCIÓN 2: EL CARRITO (ABAJO) - IGUAL QUE ANTES
        // ------------------------------------------------
        rlutil::locate(1, 20); 
        rlutil::setColor(rlutil::GREEN);
        cout << "=== CARRITO ACTUAL ===\n";
        cout << string(60, '=') << endl;
        
        if (ticket.getCantidadDetalles() == 0) {
            rlutil::setColor(rlutil::GREY);
            cout << "(Carrito vacio)\n";
        } else {
            for (int k = 0; k < ticket.getCantidadDetalles(); k++) {
                clsdetalleVenta d = ticket.leerDetalle(k);
                rlutil::setColor(rlutil::WHITE);
                cout << left << setw(3) << d.getCantidad() << "x " 
                     << left << setw(30) << d.getDescripcion() 
                     << "$ " << d.getSubTotal() << endl;
            }
            cout << string(60, '-') << endl;
            rlutil::setColor(rlutil::YELLOW);
            cout << "SUBTOTAL ACUMULADO: $" << ticket.getImporteTotal() << endl;
        }

        // CONTROL
        int key = rlutil::getkey();
        switch (key) {
            case 14: // ARRIBA
                PlaySound(TEXT("sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                seleccion--;
                if (seleccion < 0) seleccion = totalOpciones;
                break;
            case 15: // ABAJO
                PlaySound(TEXT("sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                seleccion++;
                if (seleccion > totalOpciones) seleccion = 0;
                break;
            case 1: // ENTER
                PlaySound(TEXT("sounds/keySoundStrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
                if (seleccion == totalOpciones) return -1; 
                return indicesReales[seleccion]; 
                break;
            case 0: // ESCAPE
                return -1;
                break;
        }
    }
}

// ========================================================
// REALIZAR VENTA (FINAL Y CORREGIDA) 🛒
// ========================================================
void clsVentas::realizarVenta(clsFunciones& gestorFunciones, 
                              clsPelicula& gestorPeliculas, 
                              clsSala& gestorSalas, 
                              clsPrecios& gestorPrecios,
                              clsCandy& gestorCandy) 
{
    // --- MENU VISUAL ---
    int modo = menuModoVenta(); 

    if (modo == 0) return; // Si eligió "Volver" o presionó ESC

    int posFunc = -1;

    if (modo == 1) {
        // Venta Rápida
        posFunc = seleccionarFuncionUI(gestorFunciones, gestorPeliculas, gestorSalas, 1, 0, 0, 0);
    } 
    else if (modo == 2) {
        // Fecha Específica
        rlutil::cls();
        fondoVentana();
        rlutil::setColor(rlutil::YELLOW);
        rlutil::locate(45, 12); cout << "INGRESE FECHA DE LA FUNCION";
        
        int d, m, a;
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(45, 14); cout << "Dia: "; cin >> d;
        rlutil::locate(45, 15); cout << "Mes: "; cin >> m;
        rlutil::locate(45, 16); cout << "Anio: "; cin >> a;
        
        posFunc = seleccionarFuncionUI(gestorFunciones, gestorPeliculas, gestorSalas, 2, d, m, a);
    }

    if (posFunc == -1) return; // Cancelado

    // RECUPERAR DATOS
    const clsDataFuncion* arrayFunciones = gestorFunciones.getFunciones();
    clsDataFuncion laFuncion = arrayFunciones[posFunc]; 
    string idFuncion = laFuncion.getIdFuncion(); 

    // VALIDAR ASIENTOS
    if (laFuncion.getAsientosDisponibles() <= 0) {
        cout << "ERROR: SALA LLENA (Sold Out).\n"; rlutil::anykey(); return;
    }

    int posPeli = gestorPeliculas.buscarPelicula(laFuncion.getIdPelicula());
    int posSala = gestorSalas.buscarSala(laFuncion.getIdSala());
    string tipoSala = gestorSalas.getSalas()[posSala].getTipoSala();
    
    clsTarifa tarifa = gestorPrecios.buscarPorDescripcion(tipoSala);

    // INICIO TICKET
    clsmaestroVenta ticket;
    ticket.setIdVenta(generarIdVenta());
    
    time_t t = time(0);
    tm* now = localtime(&t);
    ticket.setFecha(clsFecha(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900));
    ticket.setHora((now->tm_hour * 100) + now->tm_min);

    // MUESTRA DATOS
    rlutil::cls();
    rlutil::setColor(rlutil::YELLOW);
    cout << "DATOS DE LA FUNCION SELECCIONADA:\n";
    rlutil::setColor(rlutil::WHITE);
    cout << "> Pelicula: " << gestorPeliculas.getPeliculas()[posPeli].getNombre() << endl;
    cout << "> Sala:     " << tipoSala << endl;
    cout << "> Horario:  " << laFuncion.getHoraInicio() << " hs" << endl;
    cout << "> Libres:   " << laFuncion.getAsientosDisponibles() << endl;
    cout << "> Precio:   $" << tarifa.getPrecio() << endl;
    cout << string(40, '-') << endl;

    // VENTA ENTRADAS
    int cantEntradas;
    cout << "Cantidad de entradas: ";
    cin >> cantEntradas;

    if (cantEntradas > laFuncion.getAsientosDisponibles()) {
        rlutil::setColor(rlutil::RED);
        cout << "No hay suficientes asientos disponibles.\n"; 
        rlutil::setColor(rlutil::WHITE);
        rlutil::anykey(); return;
    }

    clsdetalleVenta itemEntrada;
    itemEntrada.setCodigo(tarifa.getCodigo());
    itemEntrada.setDescripcion("ENTRADA " + tipoSala);
    itemEntrada.setCantidad(cantEntradas);
    itemEntrada.setPrecioUnitario(tarifa.getPrecio());
    ticket.agregarDetalle(itemEntrada);

    // ----------------------------------------------------
    // 4. VENTA DE CANDY (LÓGICA CORREGIDA) 🍬
    // ----------------------------------------------------
    char opc;
    cout << "\n¿Desea agregar Candy? (S/N): ";
    cin >> opc;

    if (opc == 's' || opc == 'S') {
        bool seguirComprando = true;
        
        while (seguirComprando) {
            // UI SPLIT SCREEN
            int posCandy = seleccionarCandyUI(gestorCandy, ticket);

            if (posCandy == -1) {
                seguirComprando = false;
            } 
            else {
                clsArticulo art = gestorCandy.leerArticulo(posCandy);
                
                // CALCULO DE STOCK DINÁMICO
                int yaEnCarrito = 0;
                for(int k=0; k < ticket.getCantidadDetalles(); k++) {
                    if (ticket.leerDetalle(k).getCodigo() == art.getSKU()) {
                        yaEnCarrito += ticket.leerDetalle(k).getCantidad();
                    }
                }
                
                int disponibleReal = art.getStock() - yaEnCarrito;

                // UI DE INPUT
                rlutil::locate(60, 5); 
                rlutil::setColor(rlutil::YELLOW);
                cout << ">> SELECCIONADO: " << art.getNombre();
                
                rlutil::locate(60, 6);
                cout << ">> Precio: $" << art.getPrecio();
                
                rlutil::locate(60, 7);
                rlutil::setColor(rlutil::CYAN);
                cout << ">> Disp. Real: " << disponibleReal << "   "; 

                rlutil::locate(60, 9);
                rlutil::setColor(rlutil::WHITE);
                cout << "Cantidad a llevar: ";
                
                int cantCandy; // <--- SE DECLARA AQUÍ ÚNICAMENTE
                cin >> cantCandy;

                if (cantCandy > 0) {
                    if (cantCandy <= disponibleReal) {
                        clsdetalleVenta itemCandy;
                        itemCandy.setCodigo(art.getSKU());
                        itemCandy.setDescripcion(art.getNombre());
                        itemCandy.setCantidad(cantCandy);
                        itemCandy.setPrecioUnitario(art.getPrecio());
                        
                        if (ticket.agregarDetalle(itemCandy)) {
                            rlutil::locate(60, 11);
                            rlutil::setColor(rlutil::GREEN);
                            cout << "AGREGADO AL CARRITO!";
                            rlutil::msleep(800); 
                        } else {
                            rlutil::locate(60, 11);
                            rlutil::setColor(rlutil::RED);
                            cout << "CARRITO LLENO!";
                            rlutil::anykey();
                        }
                    } else {
                        rlutil::locate(60, 11);
                        rlutil::setColor(rlutil::RED);
                        cout << "STOCK INSUFICIENTE!";
                        rlutil::anykey();
                    }
                }
            }
        }
    }

    // ----------------------------------------------------
    // 5. CONFIRMACIÓN Y PAGO
    // ----------------------------------------------------
    rlutil::cls();
    rlutil::setColor(rlutil::GREEN);
    cout << "TOTAL A PAGAR: $" << ticket.getImporteTotal() << endl;
    rlutil::setColor(rlutil::WHITE);

    int dni;
    cout << "Ingrese DNI Cliente (0 si no informa): ";
    cin >> dni;
    ticket.setDniCliente(dni);

    cout << "\nConfirmar venta? (S/N): ";
    cin >> opc;

    if (opc == 's' || opc == 'S') {
        FILE* p = fopen(ARCHIVO_VENTAS.c_str(), "ab");
        fwrite(&ticket, sizeof(clsmaestroVenta), 1, p);
        fclose(p);

        // RESTAMOS CAPACIDAD (Usando ID ÚNICO)
        gestorFunciones.restarCapacidad(idFuncion, cantEntradas); 

        // RESTAMOS STOCK CANDY
        for (int i = 0; i < ticket.getCantidadDetalles(); i++) {
            clsdetalleVenta d = ticket.leerDetalle(i);
            if (d.getCodigo().substr(0, 3) == "SKU") {
                gestorCandy.restarStock(d.getCodigo(), d.getCantidad());
            }
        }

        rlutil::setColor(rlutil::GREEN);
        cout << "Venta registrada con exito!\n";
        rlutil::anykey();
        
        imprimirTicketEnPantalla(ticket, gestorPeliculas);
    } else {
        cout << "Venta cancelada.\n";
    }
    rlutil::anykey();
}

// ========================================================
// SIMULACIÓN DE TICKET
// ========================================================
void clsVentas::imprimirTicketEnPantalla(const clsmaestroVenta& venta, const clsPelicula& peliGestor) {
    rlutil::cls();
    cout << string(40, '*') << endl;
    cout << "         GESTOR DE CINE - TICKET OFICIAL      \n";
    cout << string(40, '*') << endl;
    cout << "Ticket #: " << venta.getIdVenta() << endl; // <--- Ahora sale VE00001
    cout << "Fecha: " << venta.getFecha().toString() << "  Hora: " << venta.getHora() << endl;
    if (venta.getDniCliente() > 0) cout << "Cliente DNI: " << venta.getDniCliente() << endl;
    cout << string(40, '-') << endl;
    cout << left << setw(20) << "DESCRIPCION" << setw(5) << "CANT" << " IMPORTE" << endl;
    cout << string(40, '-') << endl;

    for (int i = 0; i < venta.getCantidadDetalles(); i++) {
        clsdetalleVenta d = venta.leerDetalle(i);
        cout << left << setw(20) << d.getDescripcion().substr(0,19)
             << setw(5) << d.getCantidad()
             << "$" << d.getSubTotal() << endl;
    }

    cout << string(40, '=') << endl;
    cout << "TOTAL: $" << venta.getImporteTotal() << endl;
    cout << string(40, '=') << endl;
    cout << "       GRACIAS POR SU VISITA       \n\n";
    rlutil::anykey();
}

// ========================================================
// HISTORIAL DE VENTAS
// ========================================================
void clsVentas::mostrarHistorialVentas() {
    rlutil::cls();
    FILE* p = fopen(ARCHIVO_VENTAS.c_str(), "rb");
    if (p == NULL) {
        cout << "No hay ventas registradas aun.\n";
        rlutil::anykey();
        return;
    }

    clsmaestroVenta venta;

    rlutil::setColor(rlutil::YELLOW);
    // Ajusté el ancho de ID TICKET para que entre VE00001
    cout << left << setw(12) << "ID TICKET"
         << left << setw(15) << "FECHA"
         << left << setw(10) << "HORA"
         << left << setw(10) << "ITEMS"
         << left << setw(15) << "TOTAL"
         << left << setw(15) << "CLIENTE (DNI)"
         << endl;
    cout << string(75, '-') << endl;
    rlutil::setColor(rlutil::WHITE);

    while (fread(&venta, sizeof(clsmaestroVenta), 1, p)) {
        if (venta.estaActiva()) {
            int h = venta.getHora();
            string horaStr = to_string(h / 100) + ":" + (h % 100 < 10 ? "0" : "") + to_string(h % 100);

            cout << left << setw(12) << venta.getIdVenta() // <--- Ahora imprime el string
                 << left << setw(15) << venta.getFecha().toString()
                 << left << setw(10) << horaStr
                 << left << setw(10) << venta.getCantidadDetalles()
                 << left << setw(2) << "$" << setw(13) << fixed << setprecision(2) << venta.getImporteTotal()
                 << left << setw(15) << (venta.getDniCliente() > 0 ? to_string(venta.getDniCliente()) : "-")
                 << endl;
        }
    }
    fclose(p);
    rlutil::anykey();
}
