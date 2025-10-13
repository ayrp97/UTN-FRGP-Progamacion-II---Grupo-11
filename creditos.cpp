#include <iostream>
#include <locale>
#include "rlutil.h"
#include "mainHeader.h"
using namespace std;

void creditos(){

    rlutil::hidecursor(); // Herramienta que oculta el cursosor
    rlutil::cls();        // Herramienta que limpia la terminal

    int corteCreditos = 1;

    while (corteCreditos !=0) {

        fondoVentana();
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(54,3);    cout << "CREDITOS - GRUPO N 11";

        rlutil::locate(21,5);    cout << "      APELLIDO Y NOMBRE    |     ROL       |           COMENTARIO          ";
        rlutil::locate(21,7);    cout << " JORAJURIA TOMAS           |    ALUMNO     | LEGAJO =                 ";
        rlutil::locate(21,9);    cout << " FREDES JACOB SAMUEL       |    ALUMNO     | LEGAJO = 27233                ";
        rlutil::locate(21,11);   cout << " PAZ AYRTON AGUSTIN        |    ALUMNO     | LEGAJO =                 ";
        rlutil::locate(21,13);   cout << " MEDRANO GERMAN ANTONI     |    ALUMNO     | LEGAJO =                 ";
        rlutil::locate(21,15);   cout << " KLOSTER DANIEL            |    PROFESOR   | EXCELENTE PROFESIONAL         ";
        rlutil::locate(21,17);   cout << " CAMPOS LARA BRIAN         |    PROFESOR   | EXCELENTE PROFESIONAL         ";
        rlutil::locate(21,19);   cout << " WENNER MAXIMILIANO        |    JEFE JTP   | EXCELENTE PROFESIONAL         ";
        rlutil::locate(21,21);   cout << " CARBONARI VERONICA        |    JEFE JTP   | EXCELENTE PROFESIONAL         ";
        rlutil::locate(21,23);   cout << " SIMON ANGEL               |    JEFE JTP   | EXCELENTE PROFESIONAL         ";
        rlutil::locate(21,25);   cout << " GARCIA MARTIN             |    JEFE JTP   | EXCELENTE PROFESIONAL         ";
        rlutil::locate(21,27);   cout << " VAZQUEZ ADRIEL            |    JEFE JTP   | EXCELENTE PROFESIONAL         ";

        rlutil::locate(20,4);    cout <<(char)201;
        rlutil::locate(100,4);   cout <<(char)187;
        rlutil::locate(20,28);   cout <<(char)200;
        rlutil::locate(100,28);  cout <<(char)188;

        // LINEAS HORIZONTALES ok
        for (int y = 4; y <= 29; y += 2){
            for (int x = 21; x <= 99; x++){
            rlutil::locate(x,y);    cout <<(char)205;
            }
        }
        // MARCO IZQUIERDO ok
        for (int y = 5; y <= 27; y++){
            for (int x = 20; x <= 20; x++){
            rlutil::locate(x,y);    cout <<(char)186;
            }
        }
        // MARCO IZQUIERDO ok
        for (int y = 5; y <= 27; y++){
            for (int x = 100; x <= 100; x++){
            rlutil::locate(x,y);    cout <<(char)186;
            }
        }

        rlutil::setColor(rlutil::GREEN);
        rlutil::locate(41,29);  cout << " <ESC> ";
        rlutil::setColor(rlutil::WHITE);
        rlutil::locate(48,29);  cout <<" Para volver al menu principal  ";

        switch(rlutil::getkey()){
            case 0:
                PlaySound(TEXT("../../sounds/keySoundLight.wav"),NULL,SND_FILENAME | SND_ASYNC );
                corteCreditos = 0;
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











