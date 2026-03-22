#include <iostream>
using namespace std;

int main() {

        int numero = 0, suma = 0;

        for (int contador = 1; contador <= 5; contador ++)
        { cout << "ingresa un numero: " << endl;
        cin >> numero;
        suma = suma + numero;
    
        }

        cout << "la suma es igual a: " << suma << endl;

        return 0;

}