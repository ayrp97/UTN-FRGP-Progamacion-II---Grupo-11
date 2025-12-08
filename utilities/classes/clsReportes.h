#pragma once
#include "../../functions/ventas/clsVentas.h"
#include "../../functions/peliculas/clsPeliculas.h"
#include "../../functions/ventas/Candy/clsCandy.h"

class clsReportes {
public:
    // MÉTODOS PÚBLICOS
    // Este es el único que llamarás desde el menú principal (menuGestor)
    void menuPrincipalReportes();

private:
    // SUBMENÚS INTERNOS
    void menuRecaudaciones();
    void menuCandy();
    void menuPeliculas();
    void menuClientes();

    // REPORTES DE RECAUDACIÓN
    void reporteDiario();        // Muestra lo recaudado hoy
    void reportePorFechas();     // Filtra por rango de fechas
    void histogramaMensual();    // Gráfico de barras comparativo

    // REPORTES DE CANDY
    void rankingCandy();         // Productos más vendidos

    // REPORTES DE PELÍCULAS
    void top10Peliculas();       // Las más taquilleras
    void recaudacionPorGenero(); // Acción vs Terror vs Comedia...

    // REPORTES DE CLIENTES
    void topClientesVentas();    // Quién compró más veces
    void topClientesMonto();     // Quién gastó más dinero

    // EXTRAS
    void reporteHorariosPico();  // Análisis de horas concurridas
};
