#include <iostream>
#include "Nodo.h"
using namespace std;


class ArbolBalanceado
{
protected:
Nodo *raiz;
    
public:
    ArbolBalanceado();
    ArbolBalanceado(Nodo *r);
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
    void insertar(Nodo *r,Tipoelemento valor);
    void insercionBalance(Tipoelemento valor);
    int altura(Nodo *r);
    Nodo* eliminar(Tipoelemento valor);
    Nodo* eliminar(Nodo *r, Tipoelemento valor);
    Nodo *encontrarSucesor(Nodo *r);
    ~ArbolBalanceado();

private:
    void preorden(Nodo *r);
    void inorden(Nodo *r);
    void postorden(Nodo *r);
    Nodo* rotacionDerecha(Nodo *r);
    Nodo* rotacionIzquierda(Nodo *r);
    Nodo* balanceado(Nodo *r, Tipoelemento valor);
    int factorbalance(Nodo *r);
};

ArbolBalanceado::ArbolBalanceado()
{
    raiz = NULL;
}

ArbolBalanceado :: ArbolBalanceado(Nodo *r)
{
    raiz = r;
}

Nodo* ArbolBalanceado:: Oraiz(Nodo *r)
{
    return raiz;
}

Nodo ArbolBalanceado:: raizArbol()
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

void ArbolBalanceado :: Praiz(Nodo * r)
{
    raiz = r;
}

bool ArbolBalanceado :: esVacio()
{
    return raiz == NULL;
}

Nodo* ArbolBalanceado:: hijoizq()
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

Nodo* ArbolBalanceado:: hijoder()
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

Nodo* ArbolBalanceado::nuevoArbol(Nodo* ramaizq,Tipoelemento dato, Nodo *ramader)
{
    return new Nodo(ramaizq, dato, ramader);
}

void ArbolBalanceado::preorden()
{
    preorden(raiz);
}

void ArbolBalanceado:: inorden()
{
    inorden(raiz);
}

void ArbolBalanceado::postorden()
{
    postorden(raiz);
}

void ArbolBalanceado::preorden(Nodo *r)
{
    if(r != NULL)
    {
        r->visitar();
        preorden(r->subarbolizq());
        preorden(r->subarbolder());
    }

}

void ArbolBalanceado :: inorden(Nodo *r)
{
    if(r != NULL)
    {
        inorden(r->subarbolizq());
        r->visitar();
        inorden(r->subarbolder());
    }
}

void ArbolBalanceado:: postorden(Nodo *r)
{
    if(r != NULL)
    {
        postorden(r->subarbolizq());
        postorden(r->subarbolder());
        r->visitar();
    }
}
Nodo* ArbolBalanceado :: rotacionDerecha(Nodo *r)
{
    Nodo *nodoizq = r->izq;
    r->izq = nodoizq->der;
    nodoizq->der = r;
    return nodoizq;
}

Nodo* ArbolBalanceado :: rotacionIzquierda(Nodo *r)
{
    Nodo *nododer = r->der;
    r->der = nododer->izq;
    nododer->izq = r;
    return nododer;
}

int ArbolBalanceado :: altura (Nodo *r)
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


int ArbolBalanceado :: factorbalance(Nodo *r)
{
    if(r == NULL)
    {
        return 0;
    }
    else
    {
        int alturaizq = altura(r->izq);
        int alturader = altura(r->der);
        return alturaizq - alturader;
    }
}

void ArbolBalanceado :: insercionBalance(Tipoelemento valor)
{
    if(raiz == NULL)
    {
        raiz = new Nodo(valor);
    }

    else
    {
        raiz = balanceado(raiz, valor);
    }
}

Nodo* ArbolBalanceado :: balanceado(Nodo *r, Tipoelemento valor)
{
    if(r == nullptr)
    {
        return new Nodo(valor);
    }

    else if (valor < r->valorNodo())
    {
        r->izq = balanceado(r->izq, valor);
    }

    else
    {
        r->der = balanceado(r->der, valor);
    }

    int factor = factorbalance(r);

    if(factor > 1 && valor < r->izq->valorNodo())
    {
        return rotacionDerecha(r);
    }

    if(factor < -1 && valor > r->der->valorNodo())
    {
        return rotacionIzquierda(r);
    }

    if(factor > 1 && valor > r->izq->valorNodo())
    {
        r->izq = rotacionIzquierda(r->izq);
        return rotacionDerecha(r);
    }
    
    if(factor < -1 && valor < r->der->valorNodo())
    {
        r->der = rotacionDerecha(r->der);
        return rotacionIzquierda(r);
    }

    return r;
}

Nodo* ArbolBalanceado ::eliminar(Tipoelemento valor)
{
    raiz = eliminar(raiz, valor);
    return raiz;
}

Nodo* ArbolBalanceado ::eliminar(Nodo *r, Tipoelemento valor)
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

Nodo* ArbolBalanceado ::encontrarSucesor(Nodo *r)
{
   if(r->izq == NULL)
   {
        return r;
   }
   else
   {
        encontrarSucesor(r->izq);
   }
   return r;
}



ArbolBalanceado::~ArbolBalanceado()
{
}

