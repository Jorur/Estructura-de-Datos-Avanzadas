#include <iostream>
#include "ArbolBalanceado.h"
using namespace std;

void menu();

int main()
{
    char opcion;
    ArbolBalanceado a;

    
    menu();
    cout<<"Cual opcion: "; cin>>opcion;
    while(opcion!= '0')
    {
        int x;
        switch (opcion)
        {
        case '1':
            
            cout<<"Cual sera la raiz del arbol?\n";
            cout<<"Raiz: "; cin>>x;
            a.insercionBalance(x);
            cout<<"---------------------\n";
            menu();
            cout<<"Opcion: "; cin>>opcion;
            break;

        case '2':
            char op;
            do
            {
                cout<<"Que elementos insertaremos?\n";
                cout<<"Elemento: "; cin>>x;
                cout<<endl;
                a.insercionBalance(x);
                cout<<"Elemento agregado!\n";
                cout<<"Otro elemento?(s/n): "; cin>>op;
            } while (op != 'n');

            cout<<"---------------------------------\n";
            menu();
            cout<<"Opcion: "; cin>>opcion;
            break;

        case '3':
            cout<<"El recorrido del arbol en preorden se ve asi:\n";
            a.preorden();
            cout<<"---------------------------------\n";
            menu();
            cout<<"Ingrese otra opcion:\n";
            cout<<"Opcion: "; cin>>opcion;
            break;

        case '4':
            cout<<"El recorrido del arbol en inorden se ve asi:\n";
            a.inorden();
            cout<<"---------------------------------\n";
            menu();
            cout<<"Ingrese otra opcion:\n";
            cout<<"Opcion: "; cin>>opcion;
            break;

        case '5':
            cout<<"El recorrido del arbol en postorden se ve asi:\n";
            a.postorden();
            cout<<"---------------------------------\n";
            menu();
            cout<<"Ingrese otra opcion:\n";
            cout<<"Opcion: "; cin>>opcion;
            break;

        case '6':
            if(a.esVacio())
            {
                cout<<"El arbol esta vacio...\n";
            }

            else
            {
                cout<<"El arbol no esta vacio...\n";
            }
            cout<<"---------------------------------\n";
            menu();
            cout<<"Opcion: "; cin>>opcion;
            break;

            case '7':
                if(a.esVacio())
                {
                cout<<"El arbol esta vacio...\n";
                }   

                else
                {
                    cout<<"La raiz del arbol es: \n";
                    a.raizArbol().visitar();
                }
                cout<<"---------------------------------\n";
                menu();
                cout<<"Opcion: "; cin>>opcion;
                break;

        case '0':
            cout<<"Adios...\n";
            break;


        
        default:
            cout << opcion;
            cout << " - No reconozco esa opcion\n";
            menu();
            break;
            
        }
    }
    return 0;
}

void menu()
{
    cout<<"Trabajando con arboles:\n";
    cout<<"1.-Crear el arbol\n";
    cout<<"2.- Insertar nodo en el arbol\n";
    cout<<"3.- Recorrido en Preorden:\n";
    cout<<"4.- Recorrido en Inorden\n";
    cout<<"5.- Recorrido en Postorden\n";
    cout<<"6.- Esta vacio el arbol?\n";
    cout<<"7.- Cual es la raiz del arbol?\n";
    cout<<"0.- Salir\n";
}