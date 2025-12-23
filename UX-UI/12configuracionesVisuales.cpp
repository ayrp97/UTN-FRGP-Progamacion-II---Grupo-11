#include <iostream>
#include <locale>
#include "../rlutil.h"
#include "../mainHeader.h"

using namespace std;

void configuracionesVisuales() {
    rlutil::hidecursor();
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::cls();
    rlutil::setColor(rlutil::WHITE);
};