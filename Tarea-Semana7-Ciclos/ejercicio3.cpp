#include <iostream>
using namespace std;

int main() {
    double saldo = 500;               
    int opcion = 0;
    double montoDeposito;                  // Nombre del estudiante: Moisés Abinadí Farfan González
    double montoRetiro;

    do {
        cout << "1. Consultar saldo" << endl;
        cout << "2. Depositar dinero" << endl;
        cout << "3. Retirar dinero" << endl;
        cout << "4. Salir" << endl;  // Nombre del estudiante: Moisés Abinadí Farfan González
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {

            case 1:
                cout << "Saldo actual: Q" << saldo << endl;
                break;

            case 2: 
                cout << "Ingrese monto a depositar: Q";
                cin >> montoDeposito;

                if (montoDeposito <= 0) {
                    cout << "Monto invalido." << endl;
                } else {
                    saldo = saldo + montoDeposito;
                    cout << "Deposito realizado correctamente." << endl;
                }
                break;

            case 3: 
                cout << "Ingrese monto a retirar: Q";
                cin >> montoRetiro;

                if (montoRetiro <= 0) {
                    cout << "Monto invalido." << endl;
                } else if (montoRetiro > saldo) {
                    cout << "Fondos insuficientes." << endl;
                } else {
                    saldo -= montoRetiro;
                    cout << "Retiro realizado correctamente." << endl;
                }
                break;

            case 4:
                cout << "Gracias por usar el sistema." << endl;
                break;

            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }

    } while (opcion != 4);

    return 0;
}