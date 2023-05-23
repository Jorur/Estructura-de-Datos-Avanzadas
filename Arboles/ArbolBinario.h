#include <iostream>
#include "Nodo.h"
using namespace std;

class ArbolBinario
{
public:
Nodo *raiz;
    
public:
    ArbolBinario();
    ArbolBinario(Nodo *r);
    void Praiz(Nodo *r);
    Nodo* Oraiz(Nodo *r);
    Nodo raizArbol();
    bool esVacio();
    Nodo* hijoizq();
    Nodo* hijoder();
    Nodo* nuevoArbol(Nodo* ramaizq,Tipoelemento dato, Nodo *ramader);
    void preorden();
    void inorden();
    void postorden();
    Nodo* insertar(Nodo *r, Nodo *subArbol);
    ~ArbolBinario();

private:
    void preorden(Nodo *r);
    void inorden(Nodo *r);
    void postorden(Nodo *r);
};

ArbolBinario::ArbolBinario()
{
    raiz = nullptr;
}

ArbolBinario :: ArbolBinario(Nodo *r)
{
    raiz = r;
}

Nodo* ArbolBinario:: Oraiz(Nodo *r)
{
    return raiz;
}

Nodo ArbolBinario:: raizArbol()
{
    if(raiz)
    {
        return *raiz;
    }
    else
    {
        throw "Arbol vacio";
        cout<<"Arbol vacio";  
    }
}

void ArbolBinario :: Praiz(Nodo * r)
{
    raiz = r;
}

bool ArbolBinario :: esVacio()
{
    return raiz == NULL;
}

Nodo* ArbolBinario :: hijoizq()
{ 
    if(raiz)
    {
        return raiz->subarbolizq();


    }
    else
    {
        throw "Arbol vacio";
        cout<<"Arbol vacio";
    }

}

Nodo* ArbolBinario:: hijoder()
{ 
    if(raiz)
    {
        return raiz->subarbolder();
    }
    else
    {
        throw "Arbol vacio";
        cout<<"Arbol vacio";
    }

}

Nodo* ArbolBinario::nuevoArbol(Nodo* ramaizq,Tipoelemento dato, Nodo *ramader)
{
    return new Nodo(ramaizq, dato, ramader);
}

void ArbolBinario::preorden()
{
    preorden(raiz);
}

void ArbolBinario:: inorden()
{
    inorden(raiz);
}

void ArbolBinario::postorden()
{
    postorden(raiz);
}

void ArbolBinario::preorden(Nodo *r)
{
    if(r != NULL)
    {
        r->visitar();
        preorden(r->subarbolizq());
        preorden(r->subarbolder());
    }

}

void ArbolBinario :: inorden(Nodo *r)
{
    if(r != NULL)
    {
        inorden(r->subarbolizq());
        r->visitar();
        inorden(r->subarbolder());
    }
}

void ArbolBinario:: postorden(Nodo *r)
{
    if(r != NULL)
    {
        postorden(r->subarbolizq());
        postorden(r->subarbolder());
        r->visitar();
    }
}

Nodo* ArbolBinario :: insertar(Nodo *r, Nodo *subArbol)
{
    char direccion;
    if(r == nullptr)
    {
        return subArbol;
    }

    cout<<"Izquierda(i) o derecha(d) de "<<r->dato<<": "; cin>> direccion;

    if(direccion == 'i')
    {
        r->izq = insertar(r->izq, subArbol);
    }

    else if(direccion == 'd')
    {
        r->der = insertar(r->der, subArbol);
    }
    
    return r;

}

ArbolBinario::~ArbolBinario()
{
}

