#include <iostream>
#include "ListaE.h"

using namespace std;

int main()
{
    Lista l = Lista();

    l.insertar(1);
    l.insertar(2);
    l.insertar(3);
    l.mostrar();
    l.buscar(4);
   /* l.quitar(2);
    cout<<endl;
    l.mostrar();
    */
    return 0;
}