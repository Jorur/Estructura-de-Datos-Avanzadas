/*
Generamos un archivo binario estructurado
lo ordenamos por el metodo de la mezcla directa
Mostramos el resultado

Mejoras por terminar:
- La longitud del archivo esta fija, debemos volverla variable (input)
- Los nombres de los archivos estan fijos, debemos permitir que sea input
- La estructura está fija, debemos volverla flexible (adaptable a cualquier estructura)
- El texto anotado en el registro se puede mejorar, ahora es un texto fijo

-- En base a este modelo, realizar los otros metodos de mezcla: equilibrada multiple
*/

#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

typedef string nomArch;
nomArch fichero;
nomArch fileAux1;
nomArch fileAux2;

struct RegistroModelo
{
    int llave;
    char texto[50];
};

// funcion para determinar el numero de registros
int cuentaReg(nomArch nf);
void distribuir(nomArch nf, nomArch nf1, nomArch nf2, int lonSec, int numReg);
void mezclar(nomArch nf1, nomArch nf2, nomArch nf, int lonSec, int numReg);
void mezclaDirecta(nomArch f, int n);
void CrearOrigen(int n);
void ListaOrigen(int n);


int main()
{
    int n;

    cout << "Creacion del archivo de origen\n";
    cout << "Ingrese la cantidad de datos a crear: ";
    cin >> n;
    cout << "Ingrese la ruta de los archivos por favor:\n";
    cout << "Archivo principal: ";
    cin >> fichero;
    cout << "Archivo auxiliar 1: ";
    cin >> fileAux1;
    cout << "Archivo auxiliar 2: ";
    cin >> fileAux2;
    CrearOrigen(n);

    cout << "Listado del archivo de origen:\n";
    ListaOrigen(n);
    mezclaDirecta(fichero, n);
    cout << "Listado del archivo ordenado:\n";
    ListaOrigen(n);
}

int cuentaReg(nomArch nf)
{
    int k = 0;
    RegistroModelo registro;
    ifstream f(nf);

    while (f.read((char*)&registro, sizeof(registro)))
    {
        k++;
    }

    f.close();
    return k;
}

// funcion que separa secunecias ordenadas de registros
void distribuir(nomArch nf, nomArch nf1, nomArch nf2, int lonSec, int numReg)
{
    int numSec, resto, i;
    numSec = numReg / (2 * lonSec);
    resto = numReg % (2 * lonSec);
    RegistroModelo RegMod;
    ifstream f(nf, ios::binary);
    ofstream f1(nf1, ios::binary);
    ofstream f2(nf2, ios::binary);

    if (f.bad() || f1.bad() || f2.bad())
    {
        throw "Error en el proceso de Separacion \n";
    }

    for (i = 1; i <= numSec; i++)
    {
        // salvamos fallo de paso de archivo
        for (int j = 1; j <= lonSec; j++)
        {
            f.read((char*)&RegMod.llave, sizeof(RegMod.llave));
            f.read((char*)&RegMod.texto, sizeof(RegMod.texto));

            f1.write((char*)&RegMod.llave, sizeof(RegMod.llave));
            f1.write((char*)&RegMod.texto, sizeof(RegMod.texto));
        }

        // salvamos falla de paso de archivo
        for (int j = 1; j <= lonSec; j++)
        {
            f.read((char*)&RegMod.llave, sizeof(RegMod.llave));
            f.read((char*)&RegMod.texto, sizeof(RegMod.texto));

            f2.write((char*)&RegMod.llave, sizeof(RegMod.llave));
            f2.write((char*)&RegMod.texto, sizeof(RegMod.texto));
        }
    }

    // Se procesa el resto de registros de los archivos

    if (resto > lonSec)
    {
        resto -= lonSec;
    }
    else
    {
        lonSec = resto;
        resto = 0;
    }

    for (int j = 1; j <= lonSec; j++)
    {
        f.read((char*)&RegMod.llave, sizeof(RegMod.llave));
        f.read((char*)&RegMod.texto, sizeof(RegMod.texto));

        f1.write((char*)&RegMod.llave, sizeof(RegMod.llave));
        f1.write((char*)&RegMod.texto, sizeof(RegMod.texto));
    }
    //

    for (int j = 1; j <= lonSec; j++)
    {
        f.read((char*)&RegMod.llave, sizeof(RegMod.llave));
        f.read((char*)&RegMod.texto, sizeof(RegMod.texto));

        f2.write((char*)&RegMod.llave, sizeof(RegMod.llave));
        f2.write((char*)&RegMod.texto, sizeof(RegMod.texto));
    }

    f1.close();
    f2.close();
    f.close();
}

void mezclar(nomArch nf1, nomArch nf2, nomArch nf, int lonSec, int numReg)
{
    int numSec, resto, i, j, k;
    RegistroModelo r1, r2, RegMod;
    numSec = numReg / (2 * lonSec);
    resto = numReg % (2 * lonSec);
    ofstream f(nf, ios::binary);
    ifstream f1(nf1, ios::binary);
    ifstream f2(nf2, ios::binary);

    f1.read((char*)&r1.llave, sizeof(r1.llave));
    f1.read((char*)&r1.texto, sizeof(r1.texto));

    f2.read((char*)&r2.llave, sizeof(r2.llave));
    f2.read((char*)&r2.texto, sizeof(r2.texto));


    for (int s = 1; s <= numSec + 1; s++)
    {
        int n1, n2;
        n1 = n2 = lonSec;

        if (s == numSec + 1)
        {
            if (resto > lonSec)
            {
                n2 = resto - lonSec;
            }
            else
            {
                n1 = resto;
                n2 = 0;
            }
        }
        i = j = 1;
        while (i <= n1 && j <= n2)
        {
            RegistroModelo actual;

            if (r1.llave < r2.llave)
            {
                actual.llave = r1.llave;
                strcpy_s(actual.texto, r1.texto);
                f1.read((char*)&r1.llave, sizeof(r1.llave));
                f1.read((char*)&r1.texto, sizeof(r1.texto));
                i++;
            }

            else
            {
                actual.llave = r2.llave;
                strcpy_s(actual.texto, r2.texto);
                f2.read((char*)&r2.llave, sizeof(r2.llave));
                f2.read((char*)&r2.texto, sizeof(r2.texto));
                j++;
            }
            cout << "Comparando registros r1 y r2:" << endl;
            cout << "r1.llave = " << r1.llave << ", r1.texto = " << r1.texto << endl;
            cout << "r2.llave = " << r2.llave << ", r2.texto = " << r2.texto << endl;
            f.write((char*)&actual.llave, sizeof(actual.llave));
            f.write((char*)&actual.texto, sizeof(actual.texto));
        }
        // Los registros no procesados se escriben directamente
        for (k = i; k <= n1; k++)
        {
            f.write((char*)&r1.llave, sizeof(r1.llave));
            f.write((char*)&r1.texto, sizeof(r1.texto));

            f1.read((char*)&r1.llave, sizeof(r1.llave));
            f1.read((char*)&r1.texto, sizeof(r1.texto));
        }
        for (k = j; k <= n2; k++)
        {
            f.write((char*)&r2.llave, sizeof(r2.llave));
            f.write((char*)&r2.texto, sizeof(r2.texto));

            f2.read((char*)&r2.llave, sizeof(r2.llave));
            f2.read((char*)&r2.texto, sizeof(r2.texto));
        }
    }

    f.close();
    f1.close();
    f2.close();
}

void mezclaDirecta(nomArch f, int n)
{
    int lonSec;
    int numReg;
    nomArch f1 = fileAux1;
    nomArch f2 = fileAux2;
    numReg = n;
    lonSec = 1;
    while (lonSec < numReg)
    {
        cout << "Distribuir: \n";
        cout << "LonSec: " << lonSec << endl;
        distribuir(f, f1, f2, lonSec, numReg);
        mezclar(f1, f2, f, lonSec, numReg);
        lonSec = lonSec * 2;
    }
}

void CrearOrigen(int n)
{
    ofstream f;
    RegistroModelo RegMod;
    string aux;
    int num;

    f.open(fichero, ios::out | ios::binary);
    for (int m = 0; m < n; m++)
    {
        // Generar la llave aleatoria
        cout << "Ingrese la llave: ";
        cin >> num;
        RegMod.llave = num;
        cout << "Ingrese el texto: ";
        cin >> aux;
        strncpy_s(RegMod.texto, sizeof(RegMod.texto), aux.c_str(), _TRUNCATE);
        f.write((char*)&RegMod.llave, sizeof(RegMod.llave));
        f.write((char*)&RegMod.texto, sizeof(RegMod.texto));
    }
    f.close();
}

void ListaOrigen(int n)
{

    ifstream f;
    RegistroModelo RegMod;
    f.open(fichero, ios::in | ios::binary);
    for (int m = 0; m < n; m++)
    {
        f.read((char*)&RegMod.llave, sizeof(RegMod.llave));
        f.read((char*)&RegMod.texto, sizeof(RegMod.texto));
        cout << m + 1 << ".- ";
        cout << "---Llave: " << RegMod.llave << " -- ";
        cout << "Texto: " << RegMod.texto << endl;
    }
    f.close();
}
