#include <iostream>
#include <locale>
#include <string>
#include "rlutil.h"
#include <windows.h>
#include "mainHeader.h"
using namespace std;

void mostrarItem(const char* text, int posx, int posy, bool selected){
    if (selected){
        rlutil::setBackgroundColor(rlutil::BLUE);
    }else{
        rlutil::setBackgroundColor(rlutil::BLACK);
    }

    rlutil::locate(posx, posy);
    cout << text << endl;
    rlutil::setBackgroundColor(rlutil::BLACK);
}

void menuGestor(){
    // Configuraciones visuales
    rlutil::hidecursor();                      //Oculta el cursor
    rlutil::setBackgroundColor(rlutil::BLACK); //Configura el fondo de consola en Negro
    rlutil::cls();                             //Limpia la consola
    rlutil::setColor(rlutil::WHITE);           //Configura el texto a color BLANCO

    int corteMenu  = 1;    //Se declara y se asigna un valor a la variable de corte del Do While que contendrá todo el menu del programa
    int  y = 0;            //Se declara y se asigna valor a la variable Y para ser usada en el switch para poder moverse verticalmente en el menu

    while (corteMenu !=0){

        // FONDO DE VENTANA (MARCO)
        fondoVentana();    //Funcion que configura el marco blanco de la consola
        dibujoMenu();      //Funcion que dibuja los pochoclos y el simbolo de cine

        rlutil::setColor(rlutil::YELLOW);    //Configura el texto a color AMARILLO
        rlutil::locate(35,17);  cout << "ADMINISTRACION DE SALAS DE CINE << CINEMA PARADISO >>";

        // MENU DISPONIBLE EN ESTA CAPA (OPCIONES)
        rlutil::setColor(rlutil::WHITE);   //Configura el texto a color BLANCO

        mostrarItem(" PELICULAS  ", 55, 20, y==0 );
        mostrarItem("   SALAS    ", 55, 21, y==1 );
        mostrarItem("   VENTAS   ", 55, 22, y==2 );
        mostrarItem("  CREDITOS  ", 55, 23, y==3 );
        mostrarItem("   SALIR    ", 55, 24, y==4 );


        // NOTA EN LA PARTE INFERIOR DEL MARCO
        rlutil::setColor(rlutil::GREEN);   //Configura el texto a color VERDE
        rlutil::locate(20,29);  cout << "  <NOTA> ";
        rlutil::setColor(rlutil::WHITE);   //Configura el texto a color AMARILLO
        rlutil::locate(29,29);  cout << " Utilizar las TECLAS DE NAVEGACION + ENTER para acceder a las secciones  ";


        // PUNTERO >> DE SELECCION
        rlutil::locate(52,20+y);  cout << (char)175 << endl;  // con char 175 obtenemos el simbolo >>

        switch (rlutil::getkey()) {  // getKey te permite obtener el valor numerico de una tecla precionada.

            case 14:  // Cursor hacia arriba el numero de esa tecla es el 14
                rlutil::locate(52,20+y);
                cout << " " << endl;
                y--;
                PlaySound(TEXT("keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                if (y<0){y=0;}
                break;

            case 15:  // Cursor hacia abajo el numero de esa tecla es el 15
                rlutil::locate(52,20+y);
                cout << " " << endl;
                y++;
                PlaySound(TEXT("keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                if (y>4){y=4;}
                break;

            case 1: // AL PRECIONAR LA TECLA ENTER
                PlaySound(TEXT("keySoundStrong.wav"),NULL,SND_FILENAME | SND_ASYNC );
                switch (y){
                    case 0: // SI SE ESTA POSICIONADO EN "PELICULAS"
                        peliculas();
                        break;

                    case 1: // SI SE ESTA POSICIONADO EN "SALAS"
                        salas();
                        break;

                    case 2: // SI SE ESTA POSICIONADO EN "VENTAS"
                        ventas();
                        break;

                    case 3: // SI SE ESTA POSICIONADO EN "CREDITOS"
                        creditos();
                        break;

                    case 4: // SI SE ESTA POSICIONADO EN "SALIR"
                        salir();
                        corteMenu = 0;
                        break;
                    }
                break;

            default:
                rlutil::cls();
                rlutil::setColor(rlutil::RED);
                rlutil::locate(6,23);  cout << "=========================================";
                rlutil::locate(6,24);  cout << "|";
                rlutil::locate(46,24); cout << "|";
                rlutil::locate(6,25);  cout << "=========================================";
                rlutil::setColor(rlutil::WHITE);
                rlutil::locate(7,24);  cout << "  Utilice las teclas correspondientes!";
                break;
            }
    }
}
