#include <iostream>
using namespace std;

class Pila
{
private:
    struct Nodo
    {
        int valor;
        Nodo *siguiente;
    };

    Nodo *top;
    
public:
    Pila();
    ~Pila();
    void push(int valor);
    int pop();
    void imprimir();
};

Pila::Pila()
{
    top = NULL;
}

void Pila :: push(int valor)
{
    Nodo *nuevo;
    nuevo = new Nodo();
    nuevo->valor = valor;

    if(top == NULL)
    {
        top = nuevo;
        nuevo->siguiente = NULL;
    }
    else
    {
        nuevo->siguiente = top;
        top = nuevo;
        
    }

}

void Pila :: imprimir()
{
    Nodo *reco = top;
    cout<<"Listado de los elementos de la pila.\n";
    while(reco != NULL)
    {
        cout<<reco->valor<<"-";
        reco = reco->siguiente;
    }
    cout<<endl;
}

int Pila :: pop()
{
    if(top != NULL)
    {
        int info = top->valor;
        Nodo *bor = top;
        top = top->siguiente;
        delete bor;
        return info;
    }

    else
    {
        return -1;
    }
}

Pila::~Pila()
{
    Nodo *reco = top;
    Nodo *bor;

    while(reco != NULL)
    {
        bor = reco;
        reco = reco->siguiente;
        delete bor;
    }
}


int main()
{
    int c;
    Pila p = Pila();
    
    p.push(1);
    p.push(2);
    p.push(3);
    p.imprimir();
    c = p.pop();
    p.imprimir();
   

    return 0;
}