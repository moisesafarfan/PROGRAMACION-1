#include <iostream>
using namespace std;

int main() {
    
    string usuario = "admin";
    int contrasena = 2026;

    cout << "Ingrese su usuario: ";
    cin >> usuario;

    cout << "Ingrese su contraseña: ";
    cin >> contrasena;  


    while (usuario == "admin" && contrasena == 2026) {
        cout << "Bienvenido al sistema." << endl;
        cout << "Acceso concedido." << endl; }
        if (usuario != "admin" || contrasena != 2026) {
            cout << "Ingrese usuario:  << usuario << endl;
            cout << "Ingrese contraseña: " << contrasena << endl;
            
            cout << "Datos incorrectos. "; 
             
        }

}