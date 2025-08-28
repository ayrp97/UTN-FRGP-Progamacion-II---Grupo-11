#include <iostream>
#include <locale>
#include "rlutil.h"
#include "mainHeader.h"
using namespace std;


void fondoVentana(){

    // DECLARAMOS VARIABLES A UTILIZAR
    int a , b , c, d;

    rlutil::setColor(rlutil::GREY);

    // ESQUINA SUPERIOR IZQUIERDA
    rlutil::locate(1,1);
    cout << (char)201 << endl;

    // ESQUINA SUPERIOR DERECHA
    rlutil::locate(120,1);
    cout << (char)187 << endl;

    // ESQUINA INFERIOR IZQUIERDA
    rlutil::locate(1,29);
    cout << (char)200 << endl;

    // ESQUINA INFERIOR DERECHA
    rlutil::locate(120,29);
    cout << (char)188 << endl;

    // MARCO DE ARRIBA
    for (a=2; a<=119; a++){
        rlutil::locate(a,1);
        cout << (char)205 << endl;
    }
    // MARCO DE ABAJO
    for (b=2; b<=119; b++){
        rlutil::locate(b,29);
        cout << (char)205 << endl;
    }

    // MARCO DE IZQUIERDA
    for (c=2; c<=28; c++){
        rlutil::locate(1,c);
        cout << (char)186 << endl;
    }
    // MARCO DE LA DERECHA
    for (d=2; d<=28; d++){
        rlutil::locate(120,d);
        cout << (char)186 << endl;
    }
}



