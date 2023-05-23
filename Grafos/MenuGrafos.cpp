#include <iostream>
#include "Grafo.h"
#include <fstream>
using namespace std;

void menu();
void guarda_grafo(Grafo g);
void carga_grafo(Grafo *g);
void insertar_nodo_txt(Tipoelemento valor, Grafo *g);
void insertar_arista_txt(Tipoelemento inicio, Tipoelemento fin, Grafo *g);

int main()
{
    char opcion;
    Grafo grafo;
    menu();

    cout<<"Cual opcion: "; cin>>opcion;
    while (opcion != '0')
    {
        Tipoelemento x, y;
        switch (opcion)
        {
        case '1':
            cout<<"Ingrese el valor del primer vertice: "; cin>>x;
            grafo.agregarVertice(x);
            cout<<"Grafo creado!\n";
            cout<<"---------------------\n";
            menu();
            cout<<"Opcion: "; cin >> opcion;
            break;
        
        case '2':
            char op;
            do
            {
                cout<<"Ingrese el valor del vertice: "; cin>>x;
                grafo.agregarVertice(x);
                cout<<"Vertice agregado!\n";
                cout<<"Otro elemento?(s/n): "; cin>>op;
            } while (op != 'n');
            
            cout<<"---------------------\n";
            menu();
            cout<<"Opcion: "; cin >> opcion;
            break;

        case '3':
            char op1;
            do
            {
                cout<<"Ingrese el valor del primer nodo adyacente: "; cin>>x;
                cout<<"Ingrese el valor del segundo nodo adyacente: "; cin>>y;
                grafo.agregarArista(x, y);
                cout<<"Arista agregada!\n";
                cout<<"Otro elemento?(s/n): "; cin>>op1;
            } while (op1 != 'n');
            cout<<"---------------------\n";
            menu();
            cout<<"Opcion: "; cin >> opcion;
            break;

        case '4':
            cout<<"Ingrese el valor del nodo de inicio: "; cin>>x;
            cout<<"Recorrido en profundidad:\n";
            grafo.dfs(x);
            cout<<"---------------------\n";
            menu();
            cout<<"Opcion: "; cin >> opcion;
            break;

        case '5':
            cout<<"Ingrese el valor del nodo de inicio: "; cin>>x;
            cout<<"Recorrido en amplitud:\n";
            grafo.bfs(x);
            cout<<"---------------------\n";
            menu();
            cout<<"Opcion: "; cin >> opcion;
            break;

        case '6':
            cout<<"Ingrese el valor del vertice para buscar: "; cin>>x;
            grafo.buscar(x);
            cout<<"---------------------\n";
            menu();
            cout<<"Opcion: "; cin >> opcion;
            break;

        case '7':
            carga_grafo(&grafo);
            cout<<"---------------------\n";
            menu();
            cout<<"Opcion: "; cin >> opcion;
            break;

        case '8':
            guarda_grafo(grafo);
            cout<<"---------------------\n";
            menu();
            cout<<"Opcion: "; cin >> opcion;
            break;

        default:
            cout<<"No se ha encontrado esa opcion...\n";
            menu();
            break;
        }
    }
    
    return 0;
}

void menu()
{
    cout<<"Trabajando con Grafos:\n";
    cout<<"1.-Crear el grafo\n";
    cout<<"2.- Insertar vertice en el grafo\n";
    cout<<"3.- Insertar arista en el grafo\n";
    cout<<"4.- Recorrido primero en profundidad:\n";
    cout<<"5.- Recorrido primero en amplitud\n";
    cout<<"6.- Buscar vertice en el grafo\n";
    cout<<"7.- Cargar el grafo\n";
    cout<<"8.- Guardar el grafo\n";
    cout<<"0.- Salir\n";

}

//Guardando Nodos del grafo
void guarda_grafo(Grafo g)
{
    cout<<"Grabando la representacion del grafo:\n";

    ofstream fichero;
    char nombre[81];
    cout<<"Nombre del archivo: ";
    cin>>nombre;
    fichero.open(nombre, ios::out);

    if(!fichero.good())
    {
        cout<<"Error al abrir el archivo...\n";
        exit(-1);
    }
//Lista de Nodos
    fichero.put('#');
    fichero.put('N');
    fichero.put('\n');

    for(Vertice *v : g.vertices)
    {
        fichero.put(v->dato);
        fichero.put('\n');
        cout<<endl;
    }
//Lista de Arcos
    fichero.put('#');
    fichero.put('A');
    fichero.put('\n');
    for (Vertice *v : g.vertices)
    {
        for (Vertice *w : v->adyacentes)
        {
            fichero.put(v->dato);
            fichero.put(' ');
            fichero.put(w->dato);
            fichero.put('\n');
        }
        cout<<endl;
    }
    cout<<"Se guardo el grafo exitosamente";
    fichero.close();
    return;
}

void carga_grafo(Grafo *g)
{
    string linea;
    char etapa = ' ';
    cout<<"Recuperando representacion del Grafo\n";

    ifstream fichero;
    char nombre[81];
    cout<<"Nombre del archivo: ";
    cin>> nombre;
    
    fichero.open(nombre, ios::in);
    if(!fichero.good())
    {
        cout<<"Error al abrir el archivo...\n";
        exit(-1);
    }

    while(getline(fichero,linea))
    {
        if(linea == "#N")
        {
            etapa = 'N';
            cout<<"Creamos los nodos..."<<endl;
        }
        if(linea == "#A")
        {
            etapa = 'A';
            cout<<"Creamos los arcos"<<endl;
        }
        cout<<linea<<endl;

        if(etapa == 'N' && linea != "#N")
        {
            insertar_nodo_txt(linea[0], g);
        }
        if(etapa == 'A' && linea != "#A")
        {
            insertar_arista_txt(linea[0], linea[2], g);
        }
    }
    fichero.close();
}

void insertar_nodo_txt(Tipoelemento valor, Grafo *g)
{
    g->agregarVertice(valor);
}

void insertar_arista_txt(Tipoelemento inicio, Tipoelemento fin, Grafo *g)
{
    g->agregarArista(inicio, fin);
}
