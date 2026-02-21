#include <iostream>
using namespace std;

int main() {

    char letra;

    cout << "Ingresa una letra: ";
    cin >> letra;

    cout << "La letra ingresada es: " << letra << endl;

    cout << "La letra repetida 3 veces: " 
         << letra << letra << letra << endl;

    cout << "Valor numerico interno: " 
         << int(letra) << endl;

    return 0;
}
