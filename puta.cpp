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

#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;
typedef string nomArch;
nomArch fichero = "c:\\prueba\\original.DAT";
nomArch fileAux1 = "c:\\prueba\\auxiliar1.DAT";
nomArch fileAux2 = "c:\\prueba\\auxiliar2.DAT";

struct RegistroModelo
{
	int llave;
//    string texto;
	char texto[50];
};

// función para determinar el número de registros
int cuentaReg(nomArch nf)
{
	int k = 0;
	int registro;
	ifstream f(nf);
	while (!f.eof())
	{
		f >> registro;
		k++;
	}
	f.close();
	return k;
}

// lee de f una secuencia y la escribe en t
//void subSecuencia(ifstream f, ofstream t, int longSec)
void subSecuencia(nomArch nf, nomArch nt, int longSec)
{
	ifstream f(nf, ios :: binary);
	ofstream t(nt, ios::binary);
	RegistroModelo RegMod;
	for (int j = 1; j <= longSec; j++)
	{
		int reg;
//		f >> reg; // lee (extrae) del archivo asociado a f
		f.read((char*)&RegMod, sizeof(RegMod));
//		t << reg << " "; // escribe en archivo asociato a t
		t.write((char*)&RegMod, sizeof(RegMod));
	}
}


// función que separa secuencias ordenadas de registros
void distribuir(nomArch nf, nomArch nf1, nomArch nf2, int lonSec, int numReg)
{
	int numSec, resto, i;
	numSec = numReg / (2 * lonSec);
	resto = numReg % (2 * lonSec);
	RegistroModelo RegMod;
	ifstream f(nf, ios:: binary);
	ofstream f1(nf1, ios::binary);
	ofstream f2(nf2, ios::binary);
	if (f.bad() || f1.bad() || f2.bad())
		throw " Error en el proceso de separación ";
	for (i = 1; i <= numSec; i++)
	{
//		subSecuencia(f, f1, lonSec);
//		subSecuencia(f, f2, lonSec);

//		subSecuencia(nf, nf1, lonSec);
//salvamos falla de paso de archivo
		for (int j = 1; j <= lonSec; j++)
		{
			f.read((char*)&RegMod, sizeof(RegMod));
			f1.write((char*)&RegMod, sizeof(RegMod));
		}
//
//		subSecuencia(nf, nf2, lonSec);
		//salvamos falla de paso de archivo
		for (int j = 1; j <= lonSec; j++)
		{
			f.read((char*)&RegMod, sizeof(RegMod));
			f2.write((char*)&RegMod, sizeof(RegMod));
		}
//
	}
	/*
	Se procesa el resto de registros del archivo
	*/
	if (resto > lonSec)
		resto -= lonSec;
	else
	{
		lonSec = resto;
		resto = 0;
	}
//	subSecuencia(f, f1, lonSec);
//	subSecuencia(f, f2, resto);

//	subSecuencia(nf, nf1, lonSec);
	//salvamos falla de paso de archivo
	for (int j = 1; j <= lonSec; j++)
	{
		f.read((char*)&RegMod, sizeof(RegMod));
		f1.write((char*)&RegMod, sizeof(RegMod));
	}
	//
//	subSecuencia(nf, nf2, lonSec);
	//salvamos falla de paso de archivo
	for (int j = 1; j <= lonSec; j++)
	{
		f.read((char*)&RegMod, sizeof(RegMod));
		f2.write((char*)&RegMod, sizeof(RegMod));
	}
	//
	f1.close(); f2.close(); f.close();
}
// mezcla pares de secuencias ordenadas
void mezclar(nomArch nf1, nomArch nf2, nomArch nf, int lonSec, int numReg)
{
	int numSec, resto, i, j, k;
//	int reg1, reg2;
	RegistroModelo reg1, reg2;
	RegistroModelo RegMod;
	numSec = numReg / (2 * lonSec); // número de subsecuencias
	resto = numReg % (2 * lonSec);
	ofstream f(nf, ios::binary);
	ifstream f1(nf1, ios::binary);
	ifstream f2(nf2, ios::binary);
//	f1 >> reg1;
	f1.read((char*)&reg1, sizeof(RegMod));
//	f2 >> reg2;
	f2.read((char*)&reg2, sizeof(RegMod));
	for (int s = 1; s <= numSec + 1; s++)
	{
		int n1, n2;
		n1 = n2 = lonSec;
		if (s == numSec + 1)
		{ // proceso de los registros de la subsecuencia incompleta
			if (resto > lonSec)
				n2 = resto - lonSec;
			else
			{
				n1 = resto;
				n2 = 0;
			}
		}
		i = j = 1;
		while (i <= n1 && j <= n2)
		{
			//int actual;
			RegistroModelo actual;
			if (reg1.llave < reg2.llave)
			{
				actual = reg1;
				//f1 >> reg1;
				f1.read((char*)&reg1, sizeof(RegMod));
				i++;
			}
			else
			{
				actual = reg2;
				//f2 >> reg2;
				f2.read((char*)&reg2, sizeof(RegMod));
				j++;
			}
			//f << actual << " ";
			f.write((char*)&actual, sizeof(RegMod));
		}
		/*
		Los registros no procesados se escriben directamente
		*/
		for (k = i; k <= n1; k++)
		{
			//f << reg1 << " ";
			f.write((char*)&reg1, sizeof(RegMod));
			//f1 >> reg1;
			f1.read((char*)&reg1, sizeof(RegMod));
		}
		for (k = j; k <= n2; k++)
		{
			//f << reg2 << " ";
			f.write((char*)&reg2, sizeof(RegMod));
			//f2 >> reg2;
			f2.read((char*)&reg2, sizeof(RegMod));
		}
	}
	lonSec *= 2;
	f.close(); f1.close(); f2.close();
}

// función que controla el algoritmo de ordenación
void mezclaDirecta(nomArch f, int n)
{
	int longSec;
	int numReg;
	nomArch f1 = fileAux1;
	nomArch f2 = fileAux2;
//	numReg = cuentaReg(f); // determina número de registros
	numReg = n;  //falta adaptar cuentaReg a la estructura
	longSec = 1;
	while (longSec < numReg)
	{
		cout << "Distribuir: LongSec:" << longSec << endl;
		distribuir(f, f1, f2, longSec, numReg);
		mezclar(f1, f2, f, longSec, numReg);
		//longSec++;
		longSec = longSec * 2;
	}
}

void CrearOrigen(int n)
{
	ofstream f;
	RegistroModelo RegMod;
	string aux;
//	f.open("c:\\files\\original.DAT", ios::out | ios::binary);
	f.open(fichero, ios::out | ios::binary);

	for (int m = 0; m < n; m++)
	{
		//Generar llave aleatoria
		RegMod.llave = rand() % 100 + 1;
		aux = to_string(RegMod.llave);
//		RegMod.texto = "La llave generada es " + aux;
		aux = "La llave generada es " + aux;
//		RegMod.texto = "La llave generada es ";
//		strcpy_s(RegMod.texto, (char*)aux); strcat_s("La llave generada es ", aux, );
		strcpy_s(RegMod.texto, "La llave generada es "); 
//		f.write(reinterpret_cast<char*>(&RegMod), sizeof(RegMod));
		f.write((char*)&RegMod, sizeof(RegMod));
	}
	f.close();
}

void ListaOrigen(int n)
{
	ifstream f;
	RegistroModelo RegMod;
	string aux;
	f.open(fichero, ios::in | ios::binary);
		for (int m = 0; m < n; m++)
		{
			f.read((char*)&RegMod, sizeof(RegMod));
			cout << m;
			cout << " -- Llave : " <<RegMod.llave << " -- ";
			cout << "Texto : " << RegMod.texto << endl;
		}
	f.close();
}

int main()
{
	int n;
	cout<<"Ingrese la cantidad de numeros: ";
	cin>>n;
	cout << " Creacion del archivo de origen\n";
	CrearOrigen(n);
	cout << " Listado del archivo de origen\n";
	ListaOrigen(n);
	mezclaDirecta(fichero, n);
	cout << " Listado del archivo de resultado\n";
	ListaOrigen(n);

}
