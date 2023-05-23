#include <iostream>
using namespace std;

template<typename T>
class List
{
private:
    class NodoL
    {
        protected:
        T dato;
        NodoL *siguiente;

        public:
        NodoL(T valor)
        {
            dato = valor;
            siguiente = nullptr;
        }
        friend class List;
    };
    NodoL *cabeza;
    NodoL *cola;
public:
    List();
    void insertar(T valor);
    void mostrar();
    void eliminar(T valor);
    ~List();
};

template<typename T>
List<T>::List()
{
    cabeza = nullptr;
    cola = nullptr;
}

template<typename T>
List<T>::~List()
{
}

template<typename T>
void List<T> :: insertar(T valor)
{
    NodoL *nuevo = new NodoL(valor);

    if(cabeza)
    {
        cola->siguiente = nuevo;
        cola = nuevo;
    }
    
    else
    {
        cabeza = nuevo;
        cola = nuevo;
    }
}

template<typename T>
void List<T> :: mostrar()
{
    Nodo *reco = cabeza;

    while(reco != nullptr)
    {
        cout<<reco->dato<<endl;
        reco = reco->siguiente;
    }

}

template<typename T>
void List<T> :: eliminar(T valor)
{
    Nodo *anterior = cabeza;
    Nodo *actual = cabeza;

    while(actual != NULL)
    {
        if(actual->dato == valor)
        {
            if(actual == cabeza)
            {
                cabeza = cabeza->siguiente;
            }

            else
            {
                anterior->siguiente =actual->siguiente;
            }
            return;
        }
        actual = actual->siguiente;
        anterior = actual;
    }
}