#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    fstream myfile;

    myfile.open("jorge.txt",ios::in);
    
    if(myfile.is_open())
    {
        string line;
        while(getline(myfile, line))
        {
            cout<<line<<endl;
        }
        myfile.close();
    }


    return 0;
}