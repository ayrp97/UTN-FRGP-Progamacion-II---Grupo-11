#include <iostream>
#include <locale>
#include "../rlutil.h"
#include "../mainHeader.h"

using namespace std;

void mostrarItem(const char* text, int x, int y, bool selected) {
    if (selected) {
        rlutil::setBackgroundColor(rlutil::WHITE);
        rlutil::setColor(rlutil::BLACK);
    } else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::GREY);
    }

    rlutil::locate(x, y);
    cout << text;

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
}
