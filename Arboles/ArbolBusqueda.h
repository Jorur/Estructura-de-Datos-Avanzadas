#include <iostream>
#include "Nodo.h"
using namespace std;

class ArbolbOrdenado
{
protected:
Nodo *raiz;
    
public:
    ArbolbOrdenado();
    ArbolbOrdenado(Nodo *r);
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
    void insertar(Tipoelemento valor);
    Nodo* buscar(Nodo *r,Tipoelemento valor);
    bool isleaf(Nodo *r);
    Nodo* eliminar(Tipoelemento valor);
    Nodo* eliminar(Nodo *r, Tipoelemento valor);
    Nodo *encontrarSucesor(Nodo *r);
    int altura(Nodo *r);
    ~ArbolbOrdenado();

private:
    void preorden(Nodo *r);
    void inorden(Nodo *r);
    void postorden(Nodo *r);
};

ArbolbOrdenado::ArbolbOrdenado()
{
    raiz = NULL;
}

ArbolbOrdenado :: ArbolbOrdenado(Nodo *r)
{
    raiz = r;
}

Nodo* ArbolbOrdenado:: Oraiz(Nodo *r)
{
    return raiz;
}

Nodo ArbolbOrdenado:: raizArbol()
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

void ArbolbOrdenado :: Praiz(Nodo * r)
{
    raiz = r;
}

bool ArbolbOrdenado :: esVacio()
{
    return raiz == NULL;
}

Nodo* ArbolbOrdenado:: hijoizq()
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

Nodo* ArbolbOrdenado:: hijoder()
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

Nodo* ArbolbOrdenado::nuevoArbol(Nodo* ramaizq,Tipoelemento dato, Nodo *ramader)
{
    return new Nodo(ramaizq, dato, ramader);
}

void ArbolbOrdenado::preorden()
{
    preorden(raiz);
}

void ArbolbOrdenado:: inorden()
{
    inorden(raiz);
}

void ArbolbOrdenado::postorden()
{
    postorden(raiz);
}

void ArbolbOrdenado::preorden(Nodo *r)
{
    if(r != NULL)
    {
        r->visitar();
        preorden(r->subarbolizq());
        preorden(r->subarbolder());
    }

}

void ArbolbOrdenado :: inorden(Nodo *r)
{
    if(r != NULL)
    {
    
        inorden(r->subarbolizq());
        r->visitar();
        inorden(r->subarbolder());
    }
}

void ArbolbOrdenado:: postorden(Nodo *r)
{
    if(r != NULL)
    {
        postorden(r->subarbolizq());
        postorden(r->subarbolder());
        r->visitar();
    }
}




Nodo* ArbolbOrdenado::buscar(Nodo *r, Tipoelemento valor)
{

    if(r->valorNodo() > valor)
    {
        if(r->subarbolizq() == NULL)
        {
            return r;
        }
        else
        {
            return buscar(r->subarbolizq(), valor);
        }

    }

    else
    {
        if(r->subarbolder() == NULL)
        {
            return r;
        }
        else
        {
           return buscar(r->subarbolder(), valor);
        }
    }
    return r;
}

void ArbolbOrdenado::insertar(Tipoelemento valor)
{

    if(raiz == NULL)
    {
        raiz = new Nodo(valor);
    }
    else
    {
        Nodo *nuevo = buscar(raiz ,valor);

        if(nuevo->valorNodo() > valor)
        {
            nuevo->izq = new Nodo(valor);
        }
        else
        {
            nuevo->der = new Nodo(valor);
        }
        
    }
}

bool ArbolbOrdenado::isleaf(Nodo *r)
{
    return r->izq == NULL && r->der == NULL;
}

Nodo* ArbolbOrdenado::eliminar(Tipoelemento valor)
{
    raiz = eliminar(raiz, valor);
    return raiz;
}

Nodo* ArbolbOrdenado::eliminar(Nodo *r, Tipoelemento valor)
{
    if(r == NULL)
    {
        cout<<"No se ha encontrado el valor\n";
        return NULL;
    }

    if(r->valorNodo() > valor)
    {
        r->izq = eliminar(r->izq, valor);
    }

    else if(r->valorNodo() < valor)
    {
        r->der = eliminar(r->der, valor);
    }

    else
    {
        if(r->izq == NULL)
        {
            Nodo *temp = r->der;
            delete r;
            return temp;
        }

        else if(r->der == NULL)
        {
            Nodo *temp = r->izq;
            delete r;
            return temp;
        }
        Nodo *sucesor = encontrarSucesor(r->der);
        r->dato = sucesor->dato;
        r->der = eliminar(r->der, sucesor->dato);

    }

    return r;
}

Nodo* ArbolbOrdenado::encontrarSucesor(Nodo *r)
{
   if(r->izq == NULL)
   {
        return r;
   }
   else
   {
        encontrarSucesor(r->izq);
   }
}


int ArbolbOrdenado :: altura (Nodo *r)
{
    if(r == nullptr)
    {
        return 0;
    }
    else 
    {
        return 1 + max(altura(r->izq), altura(r->der));
    }
}



ArbolbOrdenado::~ArbolbOrdenado()
{
}

