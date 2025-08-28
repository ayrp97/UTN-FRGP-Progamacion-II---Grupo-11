#include <iostream>
#include <locale>
#include "rlutil.h"
#include "mainHeader.h"
using namespace std;

void salas(){

    rlutil::hidecursor(); // Herramienta que oculta el cursosor
    rlutil::cls();        // Herramienta que limpia la terminal

    int corteSalas = 1;

    while (corteSalas !=0) {
        fondoVentana();



        rlutil::setColor(rlutil::GREEN);
        rlutil::locate(41,29);  cout << " <ESC> ";
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(48,29);  cout <<" Para volver al menu principal  ";

        switch(rlutil::getkey()){
            case 0:
                PlaySound(TEXT("keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                corteSalas = 0;
                rlutil::cls();
                break;

            default:
                rlutil::cls();
                rlutil::setColor(rlutil::RED);
                rlutil::locate(7,4);  cout << "=========================================";
                rlutil::locate(7,5);  cout << "|";
                rlutil::locate(47,5); cout << "|";
                rlutil::locate(7,6);  cout << "=========================================";
                rlutil::setColor(rlutil::WHITE);
                rlutil::locate(8,5);  cout << "  Utilice las teclas correspondientes!";
                break;
            }

    }

 }





