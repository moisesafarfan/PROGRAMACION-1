#include <iostream>
using namespace std;

int main() {

    double precio;   
    double cantidad;   
    double total;      
    cout << "Ingrese el precio del producto: ";
    cin >> precio;

    cout << "¿Cuantas unidades compro?: ";
    cin >> cantidad;

    total = precio * cantidad;   

    cout << "El total a pagar es: " << total << endl;

    return 0;
}
