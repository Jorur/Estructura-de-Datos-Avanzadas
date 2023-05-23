#include <iostream>
using namespace std;

typedef int TipoElemento;

class Nodo
{
    protected:
    TipoElemento valor;
    Nodo *sig;

    friend class Lista;
};

class Lista
{
    protected:
    Nodo *cabeza;
    Nodo *cola;

    public:
        Lista();
        Lista(Nodo *h);
        void insertar(TipoElemento info);
        void quitar(TipoElemento x);
        bool vacia();
        void mostrar();
        void buscar(TipoElemento x);
        ~Lista();
};

Lista::Lista()
{
    cabeza = NULL;
    cola = NULL;
}

Lista::Lista(Nodo *h)
{
    cabeza = h;
    cola = h;
}

void Lista::insertar(TipoElemento info)
{
    Nodo *nuevo;
    nuevo = new Nodo();
    nuevo->valor = info;
    

    if(cabeza)
    {
        cola->sig = nuevo;
        cola = nuevo;
    }

    else
    {
        cabeza = nuevo;
        cola = nuevo;
    }
}

void Lista::quitar(TipoElemento x)
{
    Nodo *anterior = cabeza;
    Nodo *actual = cabeza;
    Nodo *bor;

    while (actual != NULL)
    {
        if(actual->valor == x)
        {
            if (actual == cabeza)
            {
                cabeza = actual->sig;
            }

            else
            {
                anterior->sig = actual->sig;
            }

            return;
            
        }

        anterior = actual;
        actual = actual->sig;
    }
}

bool Lista :: vacia()
{
    return cabeza == NULL;
}

void Lista::mostrar()
{
    Nodo *reco = cabeza;

    while(reco != NULL)
    {
        cout<<reco->valor<<endl;
        reco = reco->sig;
    }
}

void Lista::buscar(TipoElemento x)
{
    Nodo *rec = cabeza;

    while(rec != NULL)
    {
        if(rec->valor == x)
        {
            cout<<"El elemento si esta en la lista!"<<endl;
            return;
        }
        rec = rec->sig;
    }
    cout<<"El elemento no esta en la lista :("<<endl;
}

Lista::~Lista()
{
}
