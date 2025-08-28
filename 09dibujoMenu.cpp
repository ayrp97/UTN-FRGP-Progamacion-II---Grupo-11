#include <iostream>
#include <locale>
#include "rlutil.h"
using namespace std;

void dibujoMenu(){

    // POCHOCLO  1

    rlutil::setColor(rlutil::WHITE); // BORDE BLANCO

    rlutil::locate(26,9);      cout << (char)219 << endl;
    rlutil::locate(26,10);     cout << (char)219 << endl;
    rlutil::locate(26,11);     cout << (char)219 << endl;
    rlutil::locate(26,12);     cout << (char)219 << endl;
    rlutil::locate(26,13);     cout << (char)219 << endl;
    rlutil::locate(28,9);      cout << (char)219 << endl;
    rlutil::locate(28,10);     cout << (char)219 << endl;
    rlutil::locate(28,11);     cout << (char)219 << endl;
    rlutil::locate(28,12);     cout << (char)219 << endl;
    rlutil::locate(28,13);     cout << (char)219 << endl;
    rlutil::locate(30,9);      cout << (char)219 << endl;
    rlutil::locate(30,10);     cout << (char)219 << endl;
    rlutil::locate(30,11);     cout << (char)219 << endl;
    rlutil::locate(30,12);     cout << (char)219 << endl;
    rlutil::locate(30,13);     cout << (char)219 << endl;
    rlutil::locate(32,9);      cout << (char)219 << endl;
    rlutil::locate(32,10);     cout << (char)219 << endl;
    rlutil::locate(32,11);     cout << (char)219 << endl;
    rlutil::locate(32,12);     cout << (char)219 << endl;
    rlutil::locate(32,13);     cout << (char)219 << endl;
    rlutil::locate(34,9);      cout << (char)219 << endl;
    rlutil::locate(34,10);     cout << (char)219 << endl;
    rlutil::locate(34,11);     cout << (char)219 << endl;
    rlutil::locate(34,12);     cout << (char)219 << endl;
    rlutil::locate(34,13);     cout << (char)219 << endl;
    rlutil::locate(35,9);      cout << (char)219 << endl;

    rlutil::setColor(rlutil::RED); // FRANJA ROJA

    rlutil::locate(27,9);      cout << (char)219 << endl;
    rlutil::locate(27,10);     cout << (char)219 << endl;
    rlutil::locate(27,11);     cout << (char)219 << endl;
    rlutil::locate(27,12);     cout << (char)219 << endl;
    rlutil::locate(27,13);     cout << (char)219 << endl;
    rlutil::locate(27,14);     cout << (char)219 << endl;
    rlutil::locate(29,9);      cout << (char)219 << endl;
    rlutil::locate(29,10);     cout << (char)219 << endl;
    rlutil::locate(29,11);     cout << (char)219 << endl;
    rlutil::locate(29,12);     cout << (char)219 << endl;
    rlutil::locate(29,13);     cout << (char)219 << endl;
    rlutil::locate(29,14);     cout << (char)219 << endl;
    rlutil::locate(31,9);      cout << (char)219 << endl;
    rlutil::locate(31,10);     cout << (char)219 << endl;
    rlutil::locate(31,11);     cout << (char)219 << endl;
    rlutil::locate(31,12);     cout << (char)219 << endl;
    rlutil::locate(31,13);     cout << (char)219 << endl;
    rlutil::locate(31,14);     cout << (char)219 << endl;
    rlutil::locate(33,9);      cout << (char)219 << endl;
    rlutil::locate(33,10);     cout << (char)219 << endl;
    rlutil::locate(33,11);     cout << (char)219 << endl;
    rlutil::locate(33,12);     cout << (char)219 << endl;
    rlutil::locate(33,13);     cout << (char)219 << endl;
    rlutil::locate(33,14);     cout << (char)219 << endl;

    rlutil::setColor(rlutil::RED); // BASE ROJA

    rlutil::locate(26,14);     cout << (char)219 << endl;
    rlutil::locate(28,14);     cout << (char)219 << endl;
    rlutil::locate(28,14);     cout << (char)219 << endl;
    rlutil::locate(30,14);     cout << (char)219 << endl;
    rlutil::locate(32,14);     cout << (char)219 << endl;
    rlutil::locate(34,14);     cout << (char)219 << endl;

    rlutil::setColor(rlutil::YELLOW); // PALOMITAS 1

    rlutil::locate(25,9);      cout << (char)219 << endl;
    rlutil::locate(26,8);      cout << (char)219 << endl;
    rlutil::locate(27,8);      cout << (char)219 << endl;
    rlutil::locate(28,8);      cout << (char)219 << endl;
    rlutil::locate(29,8);      cout << (char)219 << endl;
    rlutil::locate(30,8);      cout << (char)219 << endl;
    rlutil::locate(31,8);      cout << (char)219 << endl;
    rlutil::locate(32,8);      cout << (char)219 << endl;
    rlutil::locate(33,8);      cout << (char)219 << endl;
    rlutil::locate(26,7);      cout << (char)219 << endl;
    rlutil::locate(27,7);      cout << (char)219 << endl;
    rlutil::locate(29,7);      cout << (char)219 << endl;
    rlutil::locate(30,7);      cout << (char)219 << endl;
    rlutil::locate(32,7);      cout << (char)219 << endl;
    rlutil::locate(33,7);      cout << (char)219 << endl;

    // CINE
    rlutil::setColor(rlutil::WHITE); // BORDE BLANCO

    rlutil::locate(50,8);      cout << (char)219 << endl;
    rlutil::locate(51,8);      cout << (char)219 << endl;
    rlutil::locate(51,7);      cout << (char)219 << endl;
    rlutil::locate(52,7);      cout << (char)219 << endl;
    rlutil::locate(53,7);      cout << (char)219 << endl;
    rlutil::locate(53,6);      cout << (char)219 << endl;
    rlutil::locate(54,6);      cout << (char)219 << endl;
    rlutil::locate(55,6);      cout << (char)219 << endl;
    rlutil::locate(55,5);      cout << (char)219 << endl;
    rlutil::locate(56,5);      cout << (char)219 << endl;
    rlutil::locate(57,5);      cout << (char)219 << endl;
    rlutil::locate(57,4);      cout << (char)219 << endl;
    rlutil::locate(58,4);      cout << (char)219 << endl;
    rlutil::locate(59,4);      cout << (char)219 << endl;
    rlutil::locate(59,3);      cout << (char)219 << endl;
    rlutil::locate(60,3);      cout << (char)219 << endl;
    rlutil::locate(61,3);      cout << (char)219 << endl;
    rlutil::locate(50,9);      cout << (char)219 << endl;
    rlutil::locate(50,10);     cout << (char)219 << endl;
    rlutil::locate(50,11);     cout << (char)219 << endl;
    rlutil::locate(50,12);     cout << (char)219 << endl;
    rlutil::locate(50,13);     cout << (char)219 << endl;
    rlutil::locate(50,14);     cout << (char)219 << endl;
    rlutil::locate(51,9);      cout << (char)219 << endl;
    rlutil::locate(51,10);     cout << (char)219 << endl;
    rlutil::locate(51,11);     cout << (char)219 << endl;
    rlutil::locate(51,12);     cout << (char)219 << endl;
    rlutil::locate(51,13);     cout << (char)219 << endl;
    rlutil::locate(51,14);     cout << (char)219 << endl;
    rlutil::locate(52,9);      cout << (char)219 << endl;
    rlutil::locate(52,10);     cout << (char)219 << endl;
    rlutil::locate(52,11);     cout << (char)219 << endl;
    rlutil::locate(52,12);     cout << (char)219 << endl;
    rlutil::locate(52,13);     cout << (char)219 << endl;
    rlutil::locate(52,14);     cout << (char)219 << endl;
    rlutil::locate(53,9);      cout << (char)219 << endl;
    rlutil::locate(53,11);     cout << (char)219 << endl;
    rlutil::locate(53,13);     cout << (char)219 << endl;

    rlutil::setColor(rlutil::WHITE); // BORDE BLANCO

    rlutil::locate(53,14);     cout << (char)219 << endl;
    rlutil::locate(54,9);      cout << (char)219 << endl;
    rlutil::locate(54,11);     cout << (char)219 << endl;
    rlutil::locate(54,13);     cout << (char)219 << endl;
    rlutil::locate(54,14);     cout << (char)219 << endl;
    rlutil::locate(55,9);      cout << (char)219 << endl;
    rlutil::locate(55,11);     cout << (char)219 << endl;
    rlutil::locate(55,13);     cout << (char)219 << endl;
    rlutil::locate(55,14);     cout << (char)219 << endl;
    rlutil::locate(56,9);      cout << (char)219 << endl;
    rlutil::locate(56,11);     cout << (char)219 << endl;
    rlutil::locate(56,13);     cout << (char)219 << endl;
    rlutil::locate(56,14);     cout << (char)219 << endl;
    rlutil::locate(57,9);      cout << (char)219 << endl;
    rlutil::locate(57,11);     cout << (char)219 << endl;
    rlutil::locate(57,13);     cout << (char)219 << endl;
    rlutil::locate(57,14);     cout << (char)219 << endl;
    rlutil::locate(58,9);      cout << (char)219 << endl;
    rlutil::locate(58,11);     cout << (char)219 << endl;
    rlutil::locate(58,13);     cout << (char)219 << endl;
    rlutil::locate(58,14);     cout << (char)219 << endl;
    rlutil::locate(59,9);      cout << (char)219 << endl;
    rlutil::locate(59,11);     cout << (char)219 << endl;
    rlutil::locate(59,13);     cout << (char)219 << endl;
    rlutil::locate(59,14);     cout << (char)219 << endl;
    rlutil::locate(60,9);      cout << (char)219 << endl;
    rlutil::locate(60,11);     cout << (char)219 << endl;
    rlutil::locate(60,13);     cout << (char)219 << endl;
    rlutil::locate(60,14);     cout << (char)219 << endl;
    rlutil::locate(61,9);      cout << (char)219 << endl;
    rlutil::locate(61,11);     cout << (char)219 << endl;
    rlutil::locate(61,13);     cout << (char)219 << endl;
    rlutil::locate(61,14);     cout << (char)219 << endl;
    rlutil::locate(62,9);      cout << (char)219 << endl;
    rlutil::locate(62,11);     cout << (char)219 << endl;
    rlutil::locate(62,13);     cout << (char)219 << endl;
    rlutil::locate(62,14);     cout << (char)219 << endl;
    rlutil::locate(63,9);      cout << (char)219 << endl;
    rlutil::locate(63,11);     cout << (char)219 << endl;
    rlutil::locate(63,13);     cout << (char)219 << endl;
    rlutil::locate(63,14);     cout << (char)219 << endl;
    rlutil::locate(64,9);      cout << (char)219 << endl;
    rlutil::locate(64,11);     cout << (char)219 << endl;
    rlutil::locate(64,13);     cout << (char)219 << endl;
    rlutil::locate(64,14);     cout << (char)219 << endl;
    rlutil::locate(65,9);      cout << (char)219 << endl;
    rlutil::locate(65,11);     cout << (char)219 << endl;
    rlutil::locate(65,13);     cout << (char)219 << endl;
    rlutil::locate(65,14);     cout << (char)219 << endl;
    rlutil::locate(66,9);      cout << (char)219 << endl;
    rlutil::locate(66,11);     cout << (char)219 << endl;
    rlutil::locate(66,13);     cout << (char)219 << endl;
    rlutil::locate(66,14);     cout << (char)219 << endl;
    rlutil::locate(67,9);      cout << (char)219 << endl;
    rlutil::locate(67,10);     cout << (char)219 << endl;
    rlutil::locate(67,11);     cout << (char)219 << endl;
    rlutil::locate(67,12);     cout << (char)219 << endl;
    rlutil::locate(67,13);     cout << (char)219 << endl;
    rlutil::locate(67,14);     cout << (char)219 << endl;
    rlutil::locate(68,9);      cout << (char)219 << endl;
    rlutil::locate(68,10);     cout << (char)219 << endl;
    rlutil::locate(68,11);     cout << (char)219 << endl;
    rlutil::locate(68,12);     cout << (char)219 << endl;
    rlutil::locate(68,13);     cout << (char)219 << endl;
    rlutil::locate(68,14);     cout << (char)219 << endl;

    // POCHOCLO  2

    rlutil::setColor(rlutil::WHITE); // BORDE BLANCO

    rlutil::locate(86,9);      cout << (char)219 << endl;
    rlutil::locate(86,10);     cout << (char)219 << endl;
    rlutil::locate(86,11);     cout << (char)219 << endl;
    rlutil::locate(86,12);     cout << (char)219 << endl;
    rlutil::locate(86,13);     cout << (char)219 << endl;
    rlutil::locate(88,9);      cout << (char)219 << endl;
    rlutil::locate(88,10);     cout << (char)219 << endl;
    rlutil::locate(88,11);     cout << (char)219 << endl;
    rlutil::locate(88,12);     cout << (char)219 << endl;
    rlutil::locate(88,13);     cout << (char)219 << endl;
    rlutil::locate(90,9);      cout << (char)219 << endl;
    rlutil::locate(90,10);     cout << (char)219 << endl;
    rlutil::locate(90,11);     cout << (char)219 << endl;
    rlutil::locate(90,12);     cout << (char)219 << endl;
    rlutil::locate(90,13);     cout << (char)219 << endl;
    rlutil::locate(92,9);      cout << (char)219 << endl;
    rlutil::locate(92,10);     cout << (char)219 << endl;
    rlutil::locate(92,11);     cout << (char)219 << endl;
    rlutil::locate(92,12);     cout << (char)219 << endl;
    rlutil::locate(92,13);     cout << (char)219 << endl;
    rlutil::locate(94,9);      cout << (char)219 << endl;
    rlutil::locate(94,10);     cout << (char)219 << endl;
    rlutil::locate(94,11);     cout << (char)219 << endl;
    rlutil::locate(94,12);     cout << (char)219 << endl;
    rlutil::locate(94,13);     cout << (char)219 << endl;
    rlutil::locate(95,9);      cout << (char)219 << endl;

    rlutil::setColor(rlutil::RED); // FRANJA ROJA

    rlutil::locate(87,9);      cout << (char)219 << endl;
    rlutil::locate(87,10);     cout << (char)219 << endl;
    rlutil::locate(87,11);     cout << (char)219 << endl;
    rlutil::locate(87,12);     cout << (char)219 << endl;
    rlutil::locate(87,13);     cout << (char)219 << endl;
    rlutil::locate(87,14);     cout << (char)219 << endl;
    rlutil::locate(89,9);      cout << (char)219 << endl;
    rlutil::locate(89,10);     cout << (char)219 << endl;
    rlutil::locate(89,11);     cout << (char)219 << endl;
    rlutil::locate(89,12);     cout << (char)219 << endl;
    rlutil::locate(89,13);     cout << (char)219 << endl;
    rlutil::locate(89,14);     cout << (char)219 << endl;
    rlutil::locate(91,9);      cout << (char)219 << endl;
    rlutil::locate(91,10);     cout << (char)219 << endl;
    rlutil::locate(91,11);     cout << (char)219 << endl;
    rlutil::locate(91,12);     cout << (char)219 << endl;
    rlutil::locate(91,13);     cout << (char)219 << endl;
    rlutil::locate(91,14);     cout << (char)219 << endl;
    rlutil::locate(93,9);      cout << (char)219 << endl;
    rlutil::locate(93,10);     cout << (char)219 << endl;
    rlutil::locate(93,11);     cout << (char)219 << endl;
    rlutil::locate(93,12);     cout << (char)219 << endl;
    rlutil::locate(93,13);     cout << (char)219 << endl;
    rlutil::locate(93,14);     cout << (char)219 << endl;

    rlutil::setColor(rlutil::RED); // BASE ROJA

    rlutil::locate(86,14);     cout << (char)219 << endl;
    rlutil::locate(88,14);     cout << (char)219 << endl;
    rlutil::locate(90,14);     cout << (char)219 << endl;
    rlutil::locate(92,14);     cout << (char)219 << endl;
    rlutil::locate(94,14);     cout << (char)219 << endl;

    rlutil::setColor(rlutil::YELLOW); // PALOMITAS

    rlutil::locate(85,9);      cout << (char)219 << endl;
    rlutil::locate(86,8);      cout << (char)219 << endl;
    rlutil::locate(87,8);      cout << (char)219 << endl;
    rlutil::locate(88,8);      cout << (char)219 << endl;
    rlutil::locate(89,8);      cout << (char)219 << endl;
    rlutil::locate(90,8);      cout << (char)219 << endl;
    rlutil::locate(91,8);      cout << (char)219 << endl;
    rlutil::locate(92,8);      cout << (char)219 << endl;
    rlutil::locate(93,8);      cout << (char)219 << endl;
    rlutil::locate(90,7);      cout << (char)219 << endl;
    rlutil::locate(91,7);      cout << (char)219 << endl;
    rlutil::locate(92,7);      cout << (char)219 << endl;
    rlutil::locate(93,7);      cout << (char)219 << endl;
    rlutil::locate(94,7);      cout << (char)219 << endl;
    rlutil::locate(95,7);      cout << (char)219 << endl;

}
