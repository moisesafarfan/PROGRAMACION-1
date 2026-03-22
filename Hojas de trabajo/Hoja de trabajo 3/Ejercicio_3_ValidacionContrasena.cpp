#include <iostream>
using namespace std; 

main () { 
    int contraseña;

    cout << "Ingrese la contraseña: ";
    cin >> contraseña;

    while (contraseña != 1234){
        cout << "Contraseña Incorrecta, vuelva a intentar: ";
        cin >> contraseña;

    }

    cout << "Acceso concedido" << endl;

    return 0;

}