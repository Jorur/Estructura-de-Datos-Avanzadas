#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

struct PulsoM
{
    int hora;
    int pulsaciones;
};


int main()
{
    fstream f;
    f.open("c:\\prueba\\ENTRENAM.DAT", ios::out | ios:: binary);
    if(!f.good())
    {
        cout<<"Error de apertura ";
        exit(1);
    }
    //Lectura de 30 datos del pulsometro
    PulsoM pulsacion;
    cout<<"\n--- Datos del Pulsometro ---"<< endl;
    for (int m = 0; m < 30; m++)
    {
        pulsacion.hora = m;
        pulsacion.pulsaciones = m*2;
        f.write(reinterpret_cast<char*>(&pulsacion),sizeof(PulsoM));
    }
    f.close();
    cout<< "Lectura del archivo \n";
    f.open("c:\\prueba\\ENTRENAM.DAT",ios::in | ios::binary);
    //Lectura de los distintos datos del pulsometro de f
    for (int m = 0; m < 30; m++)
    {
        f.read(reinterpret_cast<char*>(&pulsacion),sizeof(PulsoM));
        cout<<"Hora: "<<pulsacion.hora<<endl;
        cout<<"Pulsaciones: "<<pulsacion.pulsaciones<<endl;
    }

    return 0;
}