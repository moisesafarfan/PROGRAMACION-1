#include <iostream>
using namespace std;

int main() {

    int meses = 0;
    double montoActual = 0;
    double totalAhorro = 0;
    double promedio = 0;
    int contador = 0;
    double montoMayor = 0;
    int mesMayor = 0;
    int contador500 = 0;

    cout << "Ingrese la cantidad de meses que desea ahorrar: ";
    cin >> meses;


    for (contador = 0; contador < meses; contador++) {

        cout << "Ingrese la cantidad de dinero que desea ahorrar en el mes " << (contador + 1) << ": ";
        cin >> montoActual;

        totalAhorro += montoActual;

    
        if (montoActual >= 500) {
            contador500++;
        }

        
        if (montoActual > montoMayor) {
            montoMayor = montoActual;
            mesMayor = contador + 1;
        }
    }

    promedio = totalAhorro / meses;

    cout << "\nTotal ahorrado: Q" << totalAhorro << endl;
    cout << "Promedio mensual: Q" << promedio << endl;
    cout << "Mayor ahorro realizado en el mes: " << mesMayor << endl;
    cout << "Meses con ahorro de Q500 o más: " << contador500 << endl;

    return 0;
}

