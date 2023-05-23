#include <iostream>
using namespace std;

typedef int Tipoelemento; //define que tipo de dato sera
class Nodo
{
protected: // Lo pueden utilizar las clases relacionadas mientras que en private no
    Tipoelemento dato;
    Nodo *izq;
    Nodo *der;
    
public:
    Nodo(Tipoelemento valor);
    Nodo(Nodo *ramizq, Tipoelemento valor, Nodo *ramder);
    //operaciones de acceso
    Tipoelemento valorNodo();
    Nodo* subarbolizq();
    Nodo* subarbolder();
    //operaciones de modificacion
    void nuevoValor(Tipoelemento d);
    void ramizq(Nodo *n);
    void ramder(Nodo *n);
    void visitar();
    int comparar();
    ~Nodo();

    friend class ArbolBinario;
    friend class ArbolbOrdenado;
    friend class ArbolBalanceado;
};

//sobrecarga o poliformismo de metodo
Nodo::Nodo(Tipoelemento valor)
{
    dato = valor;
    der = izq = NULL;
}

Nodo :: Nodo(Nodo *ramizq, Tipoelemento valor, Nodo *ramder)
{
    dato = valor;
    izq = ramizq;
    der = ramder;
}

Tipoelemento Nodo :: valorNodo()
{
    return dato;
}

Nodo* Nodo :: subarbolizq()
{
    return izq;
}

Nodo* Nodo:: subarbolder()
{
    return der;
}

void Nodo :: nuevoValor(Tipoelemento d)
{
    dato = d;
}

void Nodo:: ramizq(Nodo *n)
{
    izq = n;
}

void Nodo :: ramder(Nodo *n)
{
    der = n;
}

void Nodo :: visitar()
{
    cout<<dato<<endl;
}


Nodo::~Nodo()
{
}


