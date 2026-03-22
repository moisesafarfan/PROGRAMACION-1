#include <iostream>
using namespace std;

int main() {
    string contraseña;
    int intentos = 0;

    cout << "Ingrese la contraseña: ";
    cin >> contraseña;

    while (contraseña != "1234" && intentos < 2) {
        cout << "Contraseña incorrecta. Intente nuevamente: ";
        cin >> contraseña;
        intentos++;
    }

    if (contraseña == "1234") {
        cout << "Bienvenido" << endl;
    } else {
        cout << "Acceso denegado" << endl;
    }

    return 0;
}