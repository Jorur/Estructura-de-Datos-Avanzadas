#include <iostream>
#include <list>
using namespace std;

typedef char Tipoelemento;

class Vertice
{
public:
    Tipoelemento dato;
    list<Vertice*> adyacentes;

public:
    Vertice(Tipoelemento valor);
    void agregarAdy(Vertice *v);
    ~Vertice();

friend class Grafo;
};

Vertice :: Vertice(Tipoelemento valor)
{
    dato = valor;
}

void Vertice :: agregarAdy(Vertice *v)
{
    for (Vertice *w: adyacentes)
    {
        if(v->dato == w->dato)
        {
            return;
        }
    }
    
    adyacentes.push_back(v);
}

Vertice::~Vertice()
{
}


