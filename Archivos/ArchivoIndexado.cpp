#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#define ARCHIVOCSV "c:\\prueba\\alumnos2023.csv"
#define ARCHIVODAT "c:\\prueba\\ListadoEDAZ2_1.dat"
#define ARCHIVOIDX "c:\\prueba\\ListadoEDAZ2_1.idx"
using namespace std;

struct RegistroEst
{
    char borrado;
    char Registro[12];
    char Nombre[80];
    char Carrera[50];
    char email[90];
    char emailpers[100];
    char telefono[50];
};

struct RegistroIdx
{
    char Borrado;
    char Registro[12];
    int posicion;
};

RegistroIdx MemIndex[300];

void CrearOrigen();
void MostrarDatos();
void AccesoIndexado(char noRegLec[12]);

int main()
{
    char opcion, noRegLec[12];
    cout << "Manejo de archivos indexados\n";
    cout << "Debemos crear el archivo DAT? (S/N):";
    cin >> opcion;

    if (opcion == 's' || opcion == 'S')
    {
        CrearOrigen();
    }

    cout<<"Datos:\n";
    MostrarDatos();
    cout << "\n\n*************\n";
    cout << "Lectura Indexada\n";
    cout << "Que numero de registro quiere ver? (000 para terminar):";
    cin >> noRegLec;
    while (strcmp(noRegLec, "000") != 0)
    {
        AccesoIndexado(noRegLec);
        cout << "Que numero de registro quiere ver? (000 para terminar):";
        cin >> noRegLec;
    }
    return 0;
}

void CrearOrigen()
{
    ifstream archivo(ARCHIVOCSV);
    string linea;
    char delimitador = ';';
    int numReg = 1;
    ofstream fdat, fidx;
    RegistroEst RegistroModelo;
    RegistroIdx RegIndice;

    //Leemos la primera linea del csv para descartarla, pues es el encabezado
    getline(archivo, linea);
    //Creamos el archivo DAT donde guardaremos la estructura completa
    fdat.open(ARCHIVODAT, ios::out | ios::binary);
    //Creamos el archivo IDX donde guardaremos la estructura indice
    fidx.open(ARCHIVOIDX, ios::out | ios::binary);

    //Leemos todas las lineas del CSV y las guardamos en DAT e IDX
    while (getline(archivo, linea))
    {
        stringstream stream(linea); //Convertir la cadena a un stream
        string Registro, Nombre, Carrera, email, emailpers, telefono;
        //Extraer todos los valores de esa fila
        getline(stream, Registro, delimitador);
        getline(stream, Nombre, delimitador);
        getline(stream, Carrera, delimitador);
        getline(stream, email, delimitador);
        getline(stream, emailpers, delimitador);
        getline(stream, telefono, delimitador);
        //Imprimir
        cout << "================" << endl;
        cout << "Registro: " << Registro << endl;
        cout << "Nombre: " << Nombre << endl;
        cout << "Carrera: " << Carrera << endl;
        cout << "Email UPSA: " << email << endl;
        cout << "Email Personal: " << emailpers << endl;
        cout << "Telefono: " << telefono << endl;

        RegistroModelo.borrado = 32;
        Registro.copy(RegistroModelo.Registro, 10);
        RegistroModelo.Registro[10] = '\0';
        strncpy_s(RegistroModelo.Nombre, sizeof(RegistroModelo.Nombre), Nombre.c_str(), _TRUNCATE);
        RegistroModelo.Nombre[sizeof(RegistroModelo.Nombre) - 1] = '\0';
        strncpy_s(RegistroModelo.Carrera, sizeof(RegistroModelo.Carrera), Carrera.c_str(), _TRUNCATE);
        RegistroModelo.Carrera[sizeof(RegistroModelo.Carrera) - 1] = '\0';
        strncpy_s(RegistroModelo.email, sizeof(RegistroModelo.email), email.c_str(), _TRUNCATE);
        RegistroModelo.email[sizeof(RegistroModelo.email) - 1] = '\0';
        strncpy_s(RegistroModelo.emailpers, sizeof(RegistroModelo.emailpers), emailpers.c_str(),_TRUNCATE );
        RegistroModelo.emailpers[sizeof(RegistroModelo.emailpers) - 1] = '\0';
        strncpy_s(RegistroModelo.telefono, sizeof(RegistroModelo.telefono), telefono.c_str(), _TRUNCATE);
        RegistroModelo.telefono[sizeof(RegistroModelo.telefono) - 1] = '\0';

        RegIndice.Borrado = 32;
        Registro.copy(RegIndice.Registro, 10);
        RegIndice.Registro[10] = '\0';
        RegIndice.posicion = numReg;
        fdat.write((char*)&RegistroModelo, sizeof(RegistroModelo));
        fidx.write((char*)&RegIndice, sizeof(RegIndice));
        numReg++;

    }
    archivo.close();
    fdat.close();
    fidx.close();
}

//Lee el DAT secuencialmente
void MostrarDatos()
{
    int numRegMem = 0;
    ifstream fdat, fidx;
    RegistroEst RegistroModelo;
    RegistroIdx RegIndice;

    //Abrimos el archivo DAT para la lectura y leemos el primer registro
    fdat.open(ARCHIVODAT, ios::in | ios::binary);
    fdat.read((char*)&RegistroModelo, sizeof(RegistroModelo));

    //Leemos y motramos todos los registros
    while (!fdat.eof())
    {
        //Imprimir
        cout << "=================" << endl;
        cout << "Registro: " << RegistroModelo.Registro << endl;
        cout << "Nombre: " << RegistroModelo.Nombre << endl;
        cout << "Carrera: " << RegistroModelo.Carrera << endl;
        cout << "Email UPSA: " << RegistroModelo.email << endl;
        cout << "Email Personal: " << RegistroModelo.emailpers << endl;
        cout << "Telefono: " << RegistroModelo.telefono << endl;
        cout << "Marcado para borrar: " << RegistroModelo.borrado << endl;
        fdat.read((char*)&RegistroModelo, sizeof(RegistroModelo));
    }
    fdat.close();

    //Abrimos el archivo IDX para la lectura y leemos el primer registro 
    fidx.open(ARCHIVOIDX, ios::in | ios::binary);
    fidx.read((char*)&RegIndice, sizeof(RegIndice));

    //Leemos y Mostramos todos los registros
    while (!fidx.eof())
    {
        //Imprimir
        cout << "==============" << endl;
        cout << "Registro: " << RegIndice.Registro << endl;
        cout << "Marcado para borrar: " << RegIndice.Borrado << endl;
        cout << "Posicion: " << RegIndice.posicion << endl;

        //aprovechamos para cargar el indice a memoria
        MemIndex[numRegMem].Borrado = RegIndice.Borrado;
        strcpy_s(MemIndex[numRegMem].Registro, RegIndice.Registro);
        MemIndex[numRegMem].posicion = RegIndice.posicion;

        //continuamos leyendo
        fidx.read((char*)&RegIndice, sizeof(RegIndice));
        numRegMem++;
    }
    fidx.close();
}

void AccesoIndexado(char noRegLec[12])
{
    ifstream fdat, fidx;
    int numRegMem = 0;
    RegistroEst RegistroLeido;
    fdat.open(ARCHIVODAT, ios::in | ios::binary);
    fidx.open(ARCHIVOIDX, ios::in | ios::binary);

    while (numRegMem < 300)
    {
        if ((strcmp(MemIndex[numRegMem].Registro, noRegLec) == 0) && (MemIndex[numRegMem].Borrado == 32))
        {
            //Encontramos el Registro
            fdat.seekg((MemIndex[numRegMem].posicion - 1) * sizeof(RegistroLeido));
            fdat.read((char*)&RegistroLeido, sizeof(RegistroLeido));
            cout << "==========Encontrado============\n";
            cout << "Registro: " << RegistroLeido.Registro << endl;
            cout << "Nombre: " << RegistroLeido.Nombre << endl;
            cout << "Carrera: " << RegistroLeido.Carrera << endl;
            cout << "Email UPSA: " << RegistroLeido.email << endl;
            cout << "Email Personal: " << RegistroLeido.emailpers << endl;
            cout << "Telefono: " << RegistroLeido.telefono << endl;
            cout << "Marcado para borrar: " << RegistroLeido.borrado << endl;
            numRegMem = 400;
        }
        numRegMem++;
    }
    fdat.close();
    fidx.close();
    if (numRegMem == 400)
    {
        cout << "======= No encontrado =========" << endl;
    }
}