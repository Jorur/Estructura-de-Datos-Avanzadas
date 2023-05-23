#include <iostream>
#include <list>
#include <queue>
#include "Vertice.h"
using namespace std;

class Grafo
{
public:
    list<Vertice*> vertices;

public:
    Grafo();
    void agregarVertice(Tipoelemento val);
    void agregarArista(Tipoelemento v1, Tipoelemento v2);
    void dfs(Tipoelemento valor);
    void bfs(Tipoelemento valor);
    void buscar(Tipoelemento valor);
    ~Grafo();

private:
    list<Vertice*> dfs(Vertice *verticeInicial, list<Vertice*>);
};

Grafo::Grafo()
{
}

void Grafo :: agregarVertice(Tipoelemento valor)
{
    vertices.push_back(new Vertice(valor));
    
}

void Grafo :: agregarArista(Tipoelemento v1, Tipoelemento v2)
{
    Vertice *vertice1 = nullptr;
    Vertice *vertice2 = nullptr;

    for(Vertice *v : vertices)
    {
        if(v->dato == v1)
        {
            vertice1 = v;
        }
        if(v->dato == v2)
        {
            vertice2 = v;
        }
        if(vertice1 != nullptr && vertice2 != nullptr)
        {
            break;
        }
    }

    if(vertice1 == nullptr)
    {
        vertice1 = new Vertice(v1);
        vertices.push_back(vertice1);
    }

    if(vertice2 == nullptr)
    {
        vertice2 = new Vertice(v2);
        vertices.push_back(vertice2);
    }

    vertice1->agregarAdy(vertice2);
    vertice2->agregarAdy(vertice1);
}

void Grafo :: dfs(Tipoelemento valor)
{
   list<Vertice*> visitados;
   Vertice *verticeInicial = nullptr;

   for (Vertice *v : vertices)
   {
        if(v->dato == valor)
        {
            verticeInicial = v;
        }
   }
   
   if(verticeInicial == nullptr)
   {
        return;
   }

    dfs(verticeInicial, visitados);
    
}

list<Vertice*> Grafo :: dfs(Vertice *vertice, list<Vertice*> visitados)
{
    visitados.push_back(vertice);
    cout<<vertice->dato<<endl;

    for (Vertice *v : vertice->adyacentes)
    {
        bool visitado = false;

        for (Vertice *w : visitados)
        {
            if(v->dato == w->dato)
            {
                visitado = true;
                break;
            }
        }

        if(!visitado)
        {
            visitados = dfs(v, visitados);
        }
        
    }
    return visitados;
    
}

void Grafo :: bfs(Tipoelemento valor)
{
    list<Vertice*> visitados;
    Vertice *verticeInicial = nullptr;

    for(Vertice *v : vertices)
    {
        if(v->dato == valor)
        {
            verticeInicial = v;
        }
    }

    if(verticeInicial == nullptr)
    {
        return;
    }

    queue<Vertice*> cola;
    cola.push(verticeInicial);
    visitados.push_back(verticeInicial);

    while (!cola.empty())
    {
        Vertice *verticeActual = cola.front();
        cola.pop();
        cout<<verticeActual->dato<<endl;

        for (Vertice *v : verticeActual->adyacentes)
        {
            bool visitado = false;

            for (Vertice *w : visitados)
            {
                if(v->dato == w->dato)
                {
                    visitado = true;
                    break;
                }
            }

            if(!visitado)
            {
                cola.push(v);
                visitados.push_back(v);
            }
            
        }  
    }
    
}

void Grafo :: buscar(Tipoelemento valor)
{
    bool encontrado = false;
    for(Vertice *v: vertices)
    {
        if(v->dato == valor)
        {
            encontrado = true;
            cout<<"El nodo "<<v->dato<<" esta dentro del grafo.\n";
            cout<<"Sus adyacencias son: ";

            if(!v->adyacentes.empty())
            {
                for(Vertice *w : v->adyacentes)
                {
                    cout<<w->dato<<", ";
                }
                cout<<endl;
            }
            return;
        }
    }
    if(!encontrado)
    {
        cout<<"El nodo "<<valor<<" no existe dentro del grafo"<<endl;
    }
}

Grafo::~Grafo()
{
}

