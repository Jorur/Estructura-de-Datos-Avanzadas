#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>
using namespace std;

#define FUENTE "d:\\Parcial\\Datos.csv"
#define ARCHIVODAT "d:\\Parcial\\Lista.DAT"
#define ARCHIVOIDX "d:\\Parcial\\Lista.idx"
#define AUX1 "d:\\Parcial\\aux1.DAT"
#define AUX2 "d:\\Parcial\\aux2.DAT"
#define Poblacion "d:\\Parcial\\Poblacion.txt"

struct RegistroDep
{
    int llave;
    char Departamento[15];
    int edad;
    int total;
    int hombres;
    int mujeres;
};

struct RegistroIdx
{
    int llave;
    int posicion;
};

struct SumatoriaDep
{
    char departamento[15];
    int poblacion_total = 0;
    int hombres = 0;
    int mujeres = 0;
};


RegistroIdx MemIdx[850];

void CrearOrigen();
void MostrarDatos();
void Buscar(int codigo);
int cuentaReg();
void distribuir(int lonsec, int n);
void mezclar(int lonsec, int n);
void mezclaDirecta();
void poblacion_total();
void operaciones();
void mostrarArchivo();




int main()
{
    char opcion;
    cout<<"Parcial 2: Operaciones combinadas de archivos:\n";
    cout<<endl;

    cout<<"Creando el archivo de listado .dat"<<endl;
    cout<<endl;

    CrearOrigen();
    cout<<"Origen Creado!!!\n";

    operaciones();
    cout<<"Elija una opcion: ";
    cin>>opcion;

    while(opcion != '6')
    {
        switch (opcion)
        {
        case '1':
            cout<<"Datos del archivo .dat:\n";
            MostrarDatos();
            cout<<endl;

            operaciones();
            cout<<"Elija una opcion: ";
            cin>>opcion;
            break;

        case '2':
            cout<<"Ordenando el archivo de manera decreciente...\n";
            mezclaDirecta();
            cout<<endl;

            operaciones();
            cout<<"Elija una opcion: ";
            cin>>opcion;            
            break;

        case '3':
            int codigo;
            cout<<"Ingrese la llave del registro que desea buscar: ";
            cin>>codigo;
            cout<<"Buscando...\n";
            Buscar(codigo);

            operaciones();
            cout<<"Elija una opcion: ";
            cin>>opcion;            
            break;

        case '4':
            cout<<"Creando el archivo de texto con las sumatorias...\n";
            poblacion_total();

            operaciones();
            cout<<"Elija una opcion: ";
            cin>>opcion;            
            break;

        case '5':
            cout<<"Abriendo el archivo...\n";
            mostrarArchivo();

            operaciones();
            cout<<"Elija una opcion: ";
            cin>>opcion;            
            break;



        case '6':
            cout<<"Adios...."<<endl;
            break;
        
        default:
            cout<<"No ha ingresado una opcion correcta :(\n";
            cout<<"Intentelo otra vez...\n";

            operaciones();
            cout<<"Elija una opcion: ";
            cin>>opcion;
            break;
        }
    }

    return 0;
}

void CrearOrigen()
{
    ifstream fuente(FUENTE);
    string linea;
    char limitador = ',';
    int numReg = 1;
    ofstream fdat, fidx;
    RegistroDep RegMod;
    RegistroIdx RegIndice;

    fdat.open(ARCHIVODAT, ios::out | ios :: binary);
    fidx.open(ARCHIVOIDX, ios::out | ios:: binary);

    while (getline(fuente, linea))
    {
        stringstream stream(linea);
        
        string llave, Departamento, edad, total, hombres, mujeres;
        getline(stream, llave, limitador);
        getline(stream, Departamento, limitador);
        getline(stream, edad, limitador);
        getline(stream, total, limitador);
        getline(stream, hombres, limitador);
        getline(stream, mujeres, limitador);

         cout<<"================\n";
         cout<<"Llave: "<< llave<<endl;
         cout<<"Departamento: "<< Departamento<<endl;
         cout<<"Edad: "<< edad<<endl;
         cout<<"Total por edad: "<< total<<endl;
         cout<<"Poblacion Hombres: "<< hombres<<endl;
        cout<<"Poblacion Mujeres: "<<mujeres<<endl;
        
        //Registrando datos en la estructura
        RegMod.llave = stoi(llave);
        strncpy_s(RegMod.Departamento, sizeof(RegMod.Departamento), Departamento.c_str(), _TRUNCATE);
        RegMod.edad = stoi(edad);
        RegMod.total = stoi(total);
        RegMod.hombres = stoi(hombres);
        RegMod.mujeres = stoi(mujeres);

        RegIndice.llave = stoi(llave);
        RegIndice.posicion = numReg;
        
        fdat.write((char*)&RegMod, sizeof(RegMod));
        fidx.write((char*)&RegIndice, sizeof(RegIndice));
        numReg ++;

    }
    fuente.close();
    fdat.close();
    fidx.close();
    
}

void MostrarDatos()
{
    int numRegMem = 0;
    ifstream fdat, fidx;
    RegistroDep RegMod;
    RegistroIdx RegInd;

    fdat.open(ARCHIVODAT, ios::in | ios::binary);
    fdat.read((char*)&RegMod, sizeof(RegMod));

    while(!fdat.eof())
    {
        cout<<"================\n";
        cout<<"Llave: "<< RegMod.llave<<endl;
        cout<<"Departamento: "<< RegMod.Departamento<<endl;
        cout<<"Edad: "<< RegMod.edad<<endl;
        cout<<"Total por edad: "<< RegMod.total<<endl;
        cout<<"Poblacion Hombres: "<< RegMod.hombres<<endl;
        cout<<"Poblacion Mujeres: "<<RegMod.mujeres<<endl;
        fdat.read((char*)&RegMod, sizeof(RegMod));
    }
    fdat.close();

    fidx.open(ARCHIVOIDX, ios::in | ios::binary);
    fidx.read((char*)&RegInd, sizeof(RegInd));

    while(!fidx.eof())
    {
        cout<<"Codigo Departamento: "<<RegInd.llave<<endl;
        cout<<"Posicion: "<< RegInd.posicion << endl;

        //Aprovechando de meter en la lista
        MemIdx[numRegMem].llave = RegInd.llave;
        MemIdx[numRegMem].posicion = RegInd.posicion;

        fidx.read((char*)&RegInd, sizeof(RegInd));
        numRegMem++;
    }
    fidx.close();
}

void Buscar(int codigo)
{
    ifstream fdat,fidx;
    RegistroDep RegMod;
    int numRegMem = 0;

    fdat.open(ARCHIVODAT, ios::in | ios::binary);
    //fidx.open(ARCHIVOIDX, ios::in | ios::binary);

    while(numRegMem < 730)
    {
        if(MemIdx[numRegMem].llave == codigo)
        {
            fdat.seekg((MemIdx[numRegMem].posicion - 1) * sizeof(RegMod));
            fdat.read((char*)&RegMod, sizeof(RegMod));
            cout<<"================\n";
            cout<<"Llave: "<< RegMod.llave<<endl;
            cout<<"Departamento: "<< RegMod.Departamento<<endl;
            cout<<"Edad: "<< RegMod.edad<<endl;
            cout<<"Total por edad: "<< RegMod.total<<endl;
            cout<<"Poblacion Hombres: "<< RegMod.hombres<<endl;
            cout<<"Poblacion Mujeres: "<<RegMod.mujeres<<endl;
            fdat.read((char*)&RegMod, sizeof(RegMod));
            numRegMem = 731;
        }
        numRegMem++;
    }
    fdat.close();
    //fidx.close();
}

int cuentaReg()
{
    int contador = 0;
    RegistroDep registro;
    ifstream f(ARCHIVODAT, ios::binary);

    while(f.read((char*)&registro, sizeof(registro)))
    {
        contador ++;
    }
    f.close();
    return contador;
}

void distribuir(int lonsec, int n)
{
    int numSec, resto, i;
    numSec = n/(2*lonsec);
    resto = n % (2*lonsec);
    RegistroDep RegMod;
    ifstream fdat(ARCHIVODAT, ios::binary);
    ofstream aux1(AUX1, ios::binary);
    ofstream aux2(AUX2, ios::binary);

    if(fdat.bad() || aux1.bad() || aux2.bad())
    {
        throw "Error en el proceso de separacion\n";
    }

    for(i = 1; i <= numSec; i++)
    {
        for(int j = 1; j <= lonsec; j++)
        {
            fdat.read((char*)&RegMod, sizeof(RegMod));
            aux1.write((char*)&RegMod, sizeof(RegMod));
        }

        for(int j = 1; j <= lonsec; j++)
        {
            fdat.read((char*)&RegMod, sizeof(RegMod));
            aux2.write((char*)&RegMod, sizeof(RegMod)); 
            
        }
    }

    if(resto > lonsec)
    {
        resto -= lonsec;
    }

    else
    {
        lonsec = resto;
        resto = 0;
    }

    for(int j = 1; j <= lonsec; j ++)
    {
        fdat.read((char*)&RegMod, sizeof(RegMod));
        aux1.write((char*)&RegMod, sizeof(RegMod));
    }

    for(int j = 1; j <= lonsec; j ++)
    {
        fdat.read((char*)&RegMod, sizeof(RegMod));
        aux2.write((char*)&RegMod, sizeof(RegMod));
    }
    fdat.close();
    aux1.close();
    aux2.close();

}

void mezclar(int lonsec, int n)
{
    int numSec, i, j, k, resto;
    RegistroDep r1, r2;
    numSec = n/(2*lonsec);
    resto = n % (2*lonsec);
    ofstream fdat(ARCHIVODAT, ios::binary);
    ifstream aux1(AUX1, ios::binary);
    ifstream aux2(AUX2, ios::binary);

    aux1.read((char*)&r1, sizeof(r1));
    aux2.read((char*)&r2, sizeof(r2));

    for(int s = 1; s <= numSec + 1; s++)
    {
        int n1, n2;
        n1 = n2 = lonsec;

        if(s == numSec + 1)
        {
            if(resto > lonsec)
            {
                n2 = resto - lonsec;
            }
            else
            {
                n1 = resto;
                n2 = 0;
            }
        }
        i = j = 1;
        while(i <= n1 && j <= n2)
        {
            RegistroDep actual;

            if(r1.total > r2.total)
            {
                actual = r1;
                aux1.read((char*)&r1, sizeof(r1));
                i++;
            }

            else
            {
                actual = r2;
                aux2.read((char*)&r2, sizeof(r2));
                j++;
            }
            fdat.write((char*)&actual, sizeof(actual));
        }

        for(k = i; k <= n1; k++)
        {
            fdat.write((char*)&r1, sizeof(r1));
            aux1.read((char*)&r1, sizeof(r1));
        }

        for(k = j; k <= n2; k++)
        {
           fdat.write((char*)&r2, sizeof(r2));
           aux2.read((char*)&r2, sizeof(r2)); 
        }
    }
    lonsec *= 2;
    fdat.close();
    aux1.close();
    aux2.close();
}

void mezclaDirecta()
{
    int lonSec;
    int n;
    n = cuentaReg();
    lonSec = 1;

    while(lonSec < n)
    {
        distribuir(lonSec,n);
        mezclar(lonSec, n);
        lonSec *= 2;
    }

    //Actualizando el archivo Idx
    RegistroDep registro;
    RegistroIdx RegId;
    ofstream tempIdx("d:\\Parcial\\TEMPIDX", ios::binary);
    ifstream fdat(ARCHIVODAT, ios::binary);
    int numReg = 1;

    
    while(fdat.read((char*)&registro, sizeof(registro)))
    {
        RegId.llave = registro.llave;
        RegId.posicion = numReg;
        numReg ++;
        tempIdx.write((char*)&RegId, sizeof(RegId));
        
    }
    fdat.close();
    tempIdx.close();
    
    //Reemplazar el archivo Idx original con el archivo original Idx
    remove(ARCHIVOIDX);
    rename("d:\\Parcial\\TEMPIDX", ARCHIVOIDX);    
}

void poblacion_total()
{
    SumatoriaDep suma[9];
    ifstream fdat;
    ofstream fichero;
    RegistroDep RegMod;
    int numRegMem = 0;

    fdat.open(ARCHIVODAT, ios::in | ios::binary);
    
    strcpy_s(suma[0].departamento, "Chuquisaca");
    strcpy_s(suma[1].departamento, "La Paz");
    strcpy_s(suma[2].departamento, "Cochabamba");
    strcpy_s(suma[3].departamento, "Oruro");
    strcpy_s(suma[4].departamento, "Potosi");
    strcpy_s(suma[5].departamento, "Tarija");
    strcpy_s(suma[6].departamento, "Santa Cruz");
    strcpy_s(suma[7].departamento, "Beni");
    strcpy_s(suma[8].departamento, "Pando");
    while(numRegMem < 730)
    {
        if(MemIdx[numRegMem].llave >= 100 && MemIdx[numRegMem].llave < 200)
        {
            fdat.seekg((MemIdx[numRegMem].posicion - 1) * sizeof(RegMod));
            fdat.read((char*)&RegMod, sizeof(RegMod));
            suma[0].poblacion_total += RegMod.total;
            suma[0].hombres += RegMod.hombres;
            suma[0].mujeres += RegMod.mujeres;
        }

        else if(MemIdx[numRegMem].llave >= 200 && MemIdx[numRegMem].llave < 300)
        {
            fdat.seekg((MemIdx[numRegMem].posicion - 1) * sizeof(RegMod));
            fdat.read((char*)&RegMod, sizeof(RegMod));
            suma[1].poblacion_total += RegMod.total;
            suma[1].hombres += RegMod.hombres;
            suma[1].mujeres += RegMod.mujeres;

        }

        else if(MemIdx[numRegMem].llave >= 300 && MemIdx[numRegMem].llave < 400)
        {
            fdat.seekg((MemIdx[numRegMem].posicion - 1) * sizeof(RegMod));
            fdat.read((char*)&RegMod, sizeof(RegMod));
            suma[2].poblacion_total += RegMod.total;
            suma[2].hombres += RegMod.hombres;
            suma[2].mujeres += RegMod.mujeres;

        }

        else if(MemIdx[numRegMem].llave >= 400 && MemIdx[numRegMem].llave < 500)
        {
            fdat.seekg((MemIdx[numRegMem].posicion - 1) * sizeof(RegMod));
            fdat.read((char*)&RegMod, sizeof(RegMod));
            suma[3].poblacion_total += RegMod.total;
            suma[3].hombres += RegMod.hombres;
            suma[3].mujeres += RegMod.mujeres;

        }

        else if(MemIdx[numRegMem].llave >= 500 && MemIdx[numRegMem].llave < 600)
        {
            fdat.seekg((MemIdx[numRegMem].posicion - 1) * sizeof(RegMod));
            fdat.read((char*)&RegMod, sizeof(RegMod));
            suma[4].poblacion_total += RegMod.total;
            suma[4].hombres += RegMod.hombres;
            suma[4].mujeres += RegMod.mujeres;

        }

        else if(MemIdx[numRegMem].llave >= 600 && MemIdx[numRegMem].llave < 700)
        {
            fdat.seekg((MemIdx[numRegMem].posicion - 1) * sizeof(RegMod));
            fdat.read((char*)&RegMod, sizeof(RegMod));
            suma[5].poblacion_total += RegMod.total;
            suma[5].hombres += RegMod.hombres;
            suma[5].mujeres += RegMod.mujeres;

        }

        else if(MemIdx[numRegMem].llave >= 700 && MemIdx[numRegMem].llave < 800)
        {
            fdat.seekg((MemIdx[numRegMem].posicion - 1) * sizeof(RegMod));
            fdat.read((char*)&RegMod, sizeof(RegMod));
            suma[6].poblacion_total += RegMod.total;
            suma[6].hombres += RegMod.hombres;
            suma[6].mujeres += RegMod.mujeres;

        }

        else if(MemIdx[numRegMem].llave >= 800 && MemIdx[numRegMem].llave < 900)
        {
            fdat.seekg((MemIdx[numRegMem].posicion - 1) * sizeof(RegMod));
            fdat.read((char*)&RegMod, sizeof(RegMod));
            suma[7].poblacion_total += RegMod.total;
            suma[7].hombres += RegMod.hombres;
            suma[7].mujeres += RegMod.mujeres;

        }

        else if(MemIdx[numRegMem].llave >= 900 && MemIdx[numRegMem].llave < 1000)
        {
            fdat.seekg((MemIdx[numRegMem].posicion - 1) * sizeof(RegMod));
            fdat.read((char*)&RegMod, sizeof(RegMod));
            suma[8].poblacion_total += RegMod.total;
            suma[8].hombres += RegMod.hombres;
            suma[8].mujeres += RegMod.mujeres;
        }
        numRegMem++;
    }
    fdat.close();

    fichero.open(Poblacion, ios::out);
    fichero << "Poblaciones totales\n";
    fichero << endl;
    for(int i = 0; i<9; i++)
    {
        // cout<<"Departamento: "<< suma[i].departamento<<endl;
        // cout<<"Poblacion total: "<< suma[i].poblacion_total<<endl;
        // cout<<"Poblacion total de hombres: "<<suma[i].hombres<<endl;
        // cout<<"Poblacion total de mujeres: "<<suma[i].mujeres<<endl;
        fichero << suma[i].departamento << endl;
        fichero <<"Poblacion total: " << to_string(suma[i].poblacion_total)<<endl;
        fichero <<"Poblacion total hombres: " << to_string(suma[i].hombres)<<endl;
        fichero <<"Poblacion total mujeres: " << to_string(suma[i].mujeres)<<endl;
        fichero << endl;

    }
    fichero.close();


}

void operaciones()
{
    cout<<"Operaciones\n";
    cout<<"1.- Mostrar los datos del archivo.\n";
    cout<<"2.- Ordenar el archivo de manera decreciente.\n";
    cout<<"3.- Buscar un registro del archivo con llave.\n";
    cout<<"4.- Crear el archivo de texto con las sumatorias\n";
    cout<<"5.- Ver el archivo de texto con las sumatorias\n";
}

void mostrarArchivo()
{
    string linea;
    ifstream fichero(Poblacion);

    if(!fichero.good())
    {
        throw "Error al abrir el archivo de texto....";
    }

    getline(fichero, linea);
    getline(fichero, linea);

    while(getline(fichero, linea))
    {
        cout<< linea << endl;

        getline(fichero, linea);
        cout<< linea << endl;

        getline(fichero, linea);
        cout<< linea << endl;

        getline(fichero, linea);
        cout<< linea << endl;

        getline(fichero, linea);
        cout<<endl;
    }  
    fichero.close(); 
}