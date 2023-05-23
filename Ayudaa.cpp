#include <iostream>
#include<string>

using namespace std;

class Nodo {
public:
    int val;
    Nodo* izq;
    Nodo* der;

    Nodo(int val) : val(val), izq(nullptr), der(nullptr) {}
};

class ArbolBinario {
public:
    ArbolBinario() : root(nullptr) {}

    ~ArbolBinario() {
        deleteTree(root);
    }

    void insert(int val) {
        insertHelper(root, val);
    }
    
    void traverseInorder() {
        traverseInorderHelper(root);
        cout << endl;
    }
    
     void traversePreorden() {
        traversePreordenHelper(root);
        cout << endl;
    }
    
    void traversePostorden() {
        traversePostordenHelper(root);
        cout << endl;
    }

    bool buscar(int val){
        return buscarhelper(root, val);
    }

    bool balance(){
        return Balanceado(root);
    }

    void insertarbalanced(int val){
        root = insertarbalanceado(root, val);
    }

    void mostrar(int val){
        mostrararbol(root, val);
    }
    

private:
    Nodo* root;

    Nodo* insertHelper(Nodo *nodo, int val) {
        if (nodo == nullptr) {
            return new Nodo(val);
        }
        if (val < nodo->val) {
            nodo->izq = insertHelper(nodo->izq, val);
        } else if (val > nodo->val) {
            nodo->der = insertHelper(nodo->der, val);
        }
        return nodo;
}
    
    bool buscarhelper(Nodo* nodo, int val)
    {
        if (nodo == nullptr) {
            return false;
        }
        else if (val < nodo->val) {
            return buscarhelper(nodo->izq, val);
        } 
        else if (val > nodo->val) {
            return buscarhelper(nodo->der, val);
        } 
        else {
            return true;
        }
    }

    int altura(Nodo *nodo){
        if (nodo == NULL){
            return 0;
        }else{
            int altura_izq = altura(nodo->izq);
            int altura_der = altura(nodo->der);
            return 1 + max(altura_der, altura_izq);
        }
    }

    bool Balanceado(Nodo* nodo){
        if(nodo == NULL){
            return true;

        }else {
            int altura_izq = altura(nodo->izq);
            int altura_der = altura(nodo->der);
            int diferencia = altura_der-altura_izq;
            if(diferencia<=1 && diferencia>=-1 && Balanceado(nodo->izq) && Balanceado(nodo->der)){
                return true;
            } else{
                return false;
            }
        }
    }

    int fb(Nodo* nodo){
        if(nodo==NULL){
            return 0;
        } else{
            int altura_izq = altura(nodo->izq);
            int altura_der = altura(nodo->der);
            return altura_der-altura_izq;
        }
    }

    void rotacionizq(Nodo *&nodo){
        Nodo *N = nodo;
        Nodo *N1 = nodo->izq;

        N ->izq = N1->der;
        N1->der = N;
        nodo = N1;
    }

    void rotacionder(Nodo *&nodo){
        Nodo *N = nodo;
        Nodo *N1 = nodo->der;

        N ->der = N1->izq;
        N1->izq = N;
        nodo = N1;
    }

    void rotacionderizq(Nodo *&nodo){
        Nodo *N = nodo;
        Nodo *N1 = N->der;
        Nodo *N2 = N1->izq;

        N1->izq = N2->der;
        N2->der = N1;
        N->der = N2->izq;
        N2->izq=N;
        nodo = N2;

    }

    void rotacionizqder(Nodo *&nodo){
        Nodo* N = nodo;
        Nodo* N1 = N->izq;
        Nodo* N2 = N1->der;

        N1->der = N2->izq;
        N2->izq = N1;
        N->izq = N2->der;
        N2->der=N;
        nodo = N2;
    }

    Nodo* insertarbalanceado(Nodo* nodo, int val){
        if (nodo == nullptr) {
            return new Nodo(val);
        }
        if (val < nodo->val) {
            nodo->izq = insertarbalanceado(nodo->izq, val);
        } else if (val > nodo->val) {
            nodo->der = insertarbalanceado(nodo->der, val);
        }

        if (fb(nodo)>1){
            if(fb(nodo->der)>0)
            {
                rotacionder(nodo);
            }
            else{
                rotacionderizq(nodo);
            }
        } else if(fb(nodo)<-1){
            if(fb(nodo->izq)<0)
            {
                rotacionizq(nodo);
            }
            else{
                rotacionizqder(nodo);
            }
        }
        return nodo;
}
    void mostrararbol(Nodo *nodo, int val)
    {
        if (nodo == NULL)
        {
            return;
        }

        mostrararbol(nodo->der, val + 1);
        for (int i = 0; i < val; i++)
        {
            cout << "       ";
        }
        cout << nodo->val << "<" << endl;
        mostrararbol(nodo->izq, val+1);
}

    void traversePreordenHelper(Nodo* nodo) {
        if (nodo != nullptr) {
            cout << nodo->val << " ";
            traversePreordenHelper(nodo->izq);
            traversePreordenHelper(nodo->der);
        }   
    }

    void traverseInorderHelper(Nodo* nodo) {
        if (nodo == nullptr) {
            return;
        }

        traverseInorderHelper(nodo->izq);
        cout << nodo->val << " ";
        traverseInorderHelper(nodo->der);
    }

    void traversePostordenHelper(Nodo* nodo) {
        if (nodo == nullptr) {
            return;
        }
        traversePostordenHelper(nodo->izq);
        traversePostordenHelper(nodo->der);
        cout << nodo->val << " ";
    }

    void deleteTree(Nodo* nodo) {
        if (nodo == nullptr) {
            return;
        }

        deleteTree(nodo->izq);
        deleteTree(nodo->der);
        delete nodo;  
    
}
};

//MENU
void menu()
{   
        cout << "\n\tARBOLES\n\n";
        cout << " 1. INSERTAR NODOS EN EL ARBOL " <<endl;
        cout << " 2. INSERTAR NODOS DE MANERA BALANCEADA EN EL ARBOL " <<endl;
        cout << " 3. BUSCAR UN NODO" <<endl;
        cout << " 4. RECORRIDOS" <<endl;
        cout << " 5. SALIR " <<endl;
        cout << "\n INGRESE OPCION: ";
}


    

int main() {
    ArbolBinario bt;
    int op, valor, nodos, b;
    menu();
    do{
        cin>>op;
            switch(op){
                case 1:
        
                    cout<<"Cuantos nodos va a insertar? ";
                    cin>>nodos;
                    for(int i; i<nodos;i++){
            
                        cout<<"Valor nodo: ";
                        cin>>valor;
                        bt.insert(valor);
                        
                    }
                    cout<<"Inserte nueva opcion:";
                    cin>>op;
                    menu();
                    break;
                case 2: 
        
                    cout<<"Cuantos nodos va a insertar? ";
                    cin>>nodos;
                    for(int i; i<nodos;i++){
                    
                        cout<<"Valor nodo: ";
                        cin>>valor;
                        bt.insertarbalanced(valor);
                    }
                    cout<<"Inserte nueva opcion;";
                    cin>>op;
                    menu();
                    break;
                case 3:
                    cout<<"Inserte nodo a buscar: ";
                    cin>>b;
                    if(bt.buscar(b)==true){
                        cout<<"El nodo "<<b<<" se encuentra en el arbol";
                    }
                    else{
                        cout<<"El nodo "<<b<<" no se encuentra en el arbol";
                    }
                    cout<<"Inserte nueva opcion;";
                    cin>>op;
                    menu();
                    break;
                case 4:
                    cout << "Recorrido entreorden: ";
                    bt.traverseInorder();
                    cout<<"\nRecorrido preorden: ";
                    bt.traversePreorden();
                    cout<<"\nRecorrido postorden: ";
                    bt.traversePostorden();
                    cout<<"Inserte nueva opcion;";
                    cin>>op;
                    menu();
                    break;
                default: 
                    break;
        }
    } while(op != 5);    
    return 0; 
}