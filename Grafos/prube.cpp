#include <iostream>
#include "Grafo.h"
using namespace std;

int main()
{

    Grafo g;
    g.agregarArista(6, 4);
    g.agregarArista(4, 3);
    g.agregarArista(4, 5);
    g.agregarArista(3, 2);
    g.agregarArista(2, 1);
    g.agregarArista(5, 1);

    cout<<"Recorrido por profundidad\n";
    g.dfs(6);

    cout<<"Recorrido por amplitud\n";
    g.bfs(6);

    g.buscar(7);

    return 0;
}