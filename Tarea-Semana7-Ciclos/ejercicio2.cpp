#include <iostream>    
using namespace std;

int main() {


    double monto = 0;            // Nombre del estudiante: Moisés Abinadí Farfan González
    double total = 0;
    int cantidadCompras = 0;
    int mayoresQ100 = 0;
    int menoresQ100 = 0;
    double promedio = 0;

    cout << "Ingrese monto (0 para terminar): ";
    cin >> monto;

    
    while (monto != 0) {

        if (monto < 0) {
            
            cout << "Monto invalido. Intente nuevamente." << endl;
        } else {
            total = total + monto;
            cantidadCompras++;

            if (monto >= 100) {
                mayoresQ100++;
            } else {
                menoresQ100++;
            }
        }
        cout << "Ingrese monto (0 para terminar): ";
        cin >> monto;
    }

    cout << "\n--- RESUMEN DE COMPRAS ---" << endl;
    cout << "Total acumulado: Q" << total << endl;
    cout << "Cantidad de compras: " << cantidadCompras << endl;

    if (cantidadCompras > 0) {
        promedio = total / cantidadCompras;
        cout << "Promedio de compra: Q" << promedio << endl;
    } else {
        cout << "No se registraron compras validas." << endl;
    }

    cout << "Compras mayores o iguales a Q100: " << mayoresQ100 << endl;
    cout << "Compras menores a Q100: " << menoresQ100 << endl;

    return 0;
}