/*
Respuestas a las preguntas:
1.- Cuantos elementos es capaz de generar este programa?
Con el tipo de dato de int aguanta hasta mostrar 47 datos, con unsgined int hasta 48 elementos y con el 
unsigned long int igual me llega a 48

*/


#include <iostream>
using namespace std;
#define Max 100000


int main()
{
    unsigned long int V[Max], n, R[Max];
    unsigned long int a = 0, b =1, c;
    V[0] = a;
    V[1] = b;
    cout<<"Ingrese el valor de N: "; cin>>n;
    
    cout<<"Vector Normal: "<<endl;
    cout<<"1.- "<<V[0]<<endl;
    cout<<"2.- "<<V[1]<<endl;
    for (int i = 2; i < n; i++)
    {
        c = a+b;
        V[i] = c;
        cout<<i+1<<".- "<<V[i]<<endl;
        a = b;
        b = c;
        if(a > b)
        {
            return 0;
        }
    }
    
   /* int j = 0;
    int aux = 0;
    for (int i = n-1; i >= 0; i--)
    {
        aux = V[i];
        R[j] = aux;
        j++;
    }

    cout<<"Vector inverso: "<<endl;
    for (int k = 0; k < n; k++)
    {
        cout<<k+1<<".- "<<R[k]<<endl;
    }
    */
    

    return 0;
}