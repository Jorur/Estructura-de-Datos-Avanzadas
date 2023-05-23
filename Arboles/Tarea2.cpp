#include <iostream>
#include "ArbolBinario.h"
using namespace std;

int main()
{
    ArbolBinario a = ArbolBinario();


    a.insertar(51);
    a.insertar(36);
    a.insertar(159);
    a.insertar(89);
    a.insertar(142);
    a.insertar(108);
    a.insertar(25);
    a.insertar(177);
    a.insertar(78);
    a.insertar(157);
    a.insertar(3);
    a.insertar(178);
    a.insertar(28);
    a.insertar(150);
    a.insertar(179);
    a.insertar(164);
    a.insertar(71);
    a.insertar(169);
    a.insertar(113);
    a.insertar(81);

    a.inorden();

    return 0;
}