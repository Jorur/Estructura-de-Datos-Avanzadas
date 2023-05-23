#include <iostream>
using namespace std;

class Cola
{
private:
    struct Nodo
    {
        int valor;
        Nodo *sgt;
        
    };
    Nodo *cabeza;
    Nodo *cola;
public:
    Cola();
    void encolar(int valor);
    void desencolar();
    void mostrar();
    void imprimir();
    bool vacia();
    ~Cola();
};

Cola::Cola()
{
    cabeza = NULL;
    cola = NULL;
}

void Cola :: encolar(int valor)
{
    Nodo *nuevo;
    nuevo = new Nodo();
    nuevo->valor = valor;
    nuevo->sgt = NULL;

    if(vacia())
    {
        cabeza = nuevo;
        cola = nuevo;
        
        
    }
    else
    {
        cola->sgt = nuevo;
        cola = nuevo;
    }
}

void Cola :: desencolar()
{
    if(!vacia())
    {
        //int info = cabeza->valor;
        Nodo *bor = cabeza;
        if(cabeza == cola)
        {
            cabeza = NULL;
            cola = NULL;
        }
        else
        {
            cabeza = cabeza->sgt;
        }
        delete bor;
    }
  
}

void Cola :: mostrar()
{
    Nodo *rec = cabeza;
    cout<<"El listado de todos los elementos de la cola es:\n";
    while(rec != NULL)
    {
        cout<<rec->valor<<"-";
        rec = rec->sgt;
    }
    cout<<endl;

}

bool Cola :: vacia()
{
    return cabeza == NULL;
}

Cola::~Cola()
{
    Nodo *rec = cabeza;
    Nodo *bor;
    while(rec != NULL)
    {
        bor = rec;
        rec = rec->sgt;
        delete bor;
    }
}


int main()
{
    Cola q = Cola();
    q.encolar(1);
    q.encolar(2);
    q.encolar(3);
    q.encolar(4);
    q.mostrar();
    q.desencolar();
    q.desencolar();
    q.mostrar();
    return 0;
}