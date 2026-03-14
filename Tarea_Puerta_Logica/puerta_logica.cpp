#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {

    string nombre;
    int edad;
    double promedio;
    int clubprogra;

    cout << "Ingrese su nombre completo: ";
    getline(cin, nombre);

    cout << "Ingrese su edad: ";
    cin >> edad;

    cout << "Ingrese su promedio academico: ";
    cin >> promedio;

    cout << "¿Pertenece al club de programacion? (1 = Si, 0 = No): ";
    cin >> clubprogra;

    cout << fixed << setprecision(2);

    if (nombre == "David Alvarez")
    {
        cout << "Acceso especial concedido." << endl;
    }
    else if ((edad >= 18 && promedio >= 85) || (clubprogra == 1 && promedio >= 75) || promedio >= 95)
    {
        cout << "Bienvenido " << nombre << "." << endl;
        cout << "Acceso autorizado." << endl;
    }
    else
    {
        cout << "Acceso denegado." << endl;
    }

    return 0;
}