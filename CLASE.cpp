#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string nombre;

    cout<< "ingresa tu nombre: ";
    getline(cin, nombre);

    ofstream archivo( "usuario.txt",ios::app);
    archivo << nombre << endl;
    archivo.close();

    return 0;
}

    

