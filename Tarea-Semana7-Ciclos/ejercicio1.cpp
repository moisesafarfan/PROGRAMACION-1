#include <iostream>          // Nombre del estudiante: Moisés Abinadí Farfan González
using namespace std;

int main() {

    string usuario = "";
    int contrasena = 0;
    int intentosFallidos = 0;

    while (usuario != "admin" or contrasena != 2026) {

        cout << "Ingrese usuario: ";
        cin >> usuario;

        cout << "Ingrese contraseña: ";
        cin >> contrasena;

        if (usuario != "admin" or contrasena != 2026) {
            cout << "Datos incorrectos." << endl;
            intentosFallidos++;
        }
    }

    cout << "Bienvenido al sistema." << endl;
    cout << "Acceso concedido." << endl;
    cout << "Intentos incorrectos: " << intentosFallidos << endl;

    return 0;
}                      
