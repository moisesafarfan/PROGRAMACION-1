#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main() {

    string nombre;
    double precio;
    int cantidad;
    double subtotal;
    double iva;
    double total;

    cout << "Ingrese el nombre completo del cliente: ";
    getline(cin, nombre);

    cout << "Ingrese el precio del producto: ";
    cin >> precio;

    cout << "Ingrese la cantidad comprada: ";
    cin >> cantidad;

    subtotal = precio * cantidad;
    iva = subtotal * 0.12;
    total = subtotal + iva;

    cout << fixed << setprecision(2);

    cout << "Cliente: " << nombre << endl;
    cout << "Subtotal: Q" << subtotal << endl;
    cout << "IVA (12%): Q" << iva << endl;
    cout << "Total a pagar: Q" << total << endl;

    return 0;
}