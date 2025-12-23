#pragma once
#include "../../functions/ventas/clsVentas.h"
#include "../../functions/peliculas/clsPeliculas.h"
#include "../../functions/ventas/Candy/clsCandy.h"

class clsReportes {
public:
    void menuPrincipalReportes();

private:
    void menuRecaudaciones();
    void menuCandy();
    void menuPeliculas();
    void menuClientes();

    void reporteDiario();
    void reportePorFechas();
    void histogramaMensual();

    void rankingCandy();

    void top10Peliculas();
    void recaudacionPorGenero();

    void topClientesVentas();    
    void topClientesMonto();

    void reporteHorariosPico();
};
