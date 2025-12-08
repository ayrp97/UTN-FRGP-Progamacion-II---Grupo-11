#include <iostream>
#include <locale>
#include "../rlutil.h"
#include "../mainHeader.h"

using namespace std;

int menuInteractivo(const char* opciones[], int cantidad, const char* titulo, int x, int yBase) {
    int seleccion = 0;

    while (true) {
        rlutil::hidecursor();

        // 1. DIBUJAR TITULO
        rlutil::setColor(rlutil::YELLOW);
        rlutil::locate(x, yBase - 3);
        cout << titulo;

        for (int i = 0; i < cantidad; i++) {
            mostrarItem(opciones[i], x, yBase + i, (i == seleccion));
        }

        int key = rlutil::getkey();

        rlutil::locate(x - 3, yBase + seleccion);
        cout << " ";

        switch (key) {
            case 14: // ARRIBA
                seleccion--;
                if (seleccion < 0) seleccion = cantidad - 1;
                PlaySound(TEXT("sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case 15: // ABAJO
                seleccion++;
                if (seleccion >= cantidad) seleccion = 0;
                PlaySound(TEXT("sounds/keySoundLight.wav"), NULL, SND_FILENAME | SND_ASYNC);
                break;

            case 1: // ENTER
                PlaySound(TEXT("sounds/keySoundStrong.wav"), NULL, SND_FILENAME | SND_ASYNC);
                return seleccion;

            case 0: // ESCAPE
                rlutil::cls();
                return -1;
        }
    }
}
